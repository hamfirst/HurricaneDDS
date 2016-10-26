#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <memory>

#include "DDSKey.h"
#include "DDSLog.h"
#include "DDSCall.h"
#include "DDSRandom.h"
#include "DDSNodeState.h"
#include "DDSDataObjectStoreBase.h"
#include "DDSDatabaseConnectionPool.h"
#include "DDSResponder.h"
#include "DDSResponderCall.h"
#include "DDSNodeInterface.h"
#include "DDSServerMessage.h"
#include "DDSDataObjectStoreHelpers.h"

#include <StormRefl/StormReflJsonStd.h>
#include <StormRefl/StormReflMetaCallJson.h>
#include <StormData/StormDataChangeNotifier.h>
#include <StormData/StormDataPath.h>
#include <StormData/StormDataJsonUtil.h>
#include <StormData/StormDataParent.h>

DDS_DECLARE_CALL(BeginLoad);
DDS_DECLARE_CALL(PreMoveObject);
DDS_DECLARE_CALL(MoveObject);
DDS_DECLARE_CALL(PreDestroy);

template <class DataType, class DatabaseBackedType>
class DDSDataObjectStore : public DDSDataObjectStoreBase
{
  enum ObjectState
  {
    kLoading,
    kDatabaseOnly,
    kCreating,
    kActive,
    kLocked,
    kDeleted,
  };


  struct ObjectData
  {
    ObjectState m_State;
    std::unique_ptr<DataType> m_ActiveObject;
    std::unique_ptr<DatabaseBackedType> m_DatabaseObject;
    std::vector<DDSExportedMessage> m_PendingMessages;
    std::vector<DDSExportedSubscription> m_Subscriptions;
    std::vector<DDSExportedRequestedSubscription> m_RequestedSubscriptions;
  };

public:
  DDSDataObjectStore(DDSNodeState & node_state, int object_type_id) :
    m_NodeState(node_state), m_Collection(DatabaseBackedType::Collection()), m_ObjectTypeId(object_type_id)
  {

  }

  uint32_t GetDataClassNameHash() const
  {
    return StormReflTypeInfo<DataType>::GetNameHash();
  }

  uint32_t GetDatabaseClassNameHash() const
  {
    return StormReflTypeInfo<DatabaseBackedType>::GetNameHash();
  }

  void SpawnNewNonDatabaseBackedType(DDSKey key)
  {
    throw std::runtime_error("Trying to create a non database backed type for a database backed data store");
  }

  bool DestroyNonDatabaseBackedType(DDSKey key)
  {
    throw std::runtime_error("Trying to destroy a non database backed type for a database backed data store");
  }

  virtual void * GetDataObjectForKey(DDSKey key)
  {
    auto itr = m_Objects.find(key);
    if (itr == m_Objects.end())
    {
      return nullptr;
    }

    return itr->second.m_ActiveObject.get();
  }

  DDSKey GetUnusedKeyInRange(DDSKeyRange range)
  {
    while (true)
    {
      DDSKey test_key = GetRandomKeyInRange(range);

      if (m_Objects.find(test_key) == m_Objects.end())
      {
        return test_key;
      }
    }
  }

  ObjectData & LoadObjectByKey(DDSKey key)
  {
    auto insert_data = m_Objects.emplace(std::make_pair(key, ObjectData{ kLoading }));
    m_NodeState.QueryObjectData(m_ObjectTypeId, key, m_Collection.c_str());

    return insert_data.first->second;
  }

  void ReloadObjectByKey(DDSKey key, ObjectData & obj_data)
  {
    if (obj_data.m_State != kDeleted)
    {
      DDSLog::LogError("Invalid object reloading state");
      return;
    }

    obj_data.m_State = kLoading;
    m_NodeState.QueryObjectData(m_ObjectTypeId, key, m_Collection.c_str());
  }

  void HandleLoadResult(DDSKey key, const char * data, int ec)
  {
    auto itr = m_Objects.find(key);
    if (itr == m_Objects.end())
    {
      return;
    }

    auto & obj_data = itr->second;
    if (obj_data.m_State != kLoading)
    {
      DDSLog::LogError("Invalid object loading state");
      return;
    }

    if (ec)
    {
      obj_data.m_State = kDeleted;
      obj_data.m_PendingMessages.clear();

      std::vector<DDSExportedSubscription> new_subs;

      for (auto & sub : obj_data.m_Subscriptions)
      {
        if (sub.m_DataPath == "?")
        {
          new_subs.push_back(sub);

          DDSResponderCallData responder_call;
          DDSCreateSubscriptionExistResponse(false, sub, responder_call);

          m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ sub.m_ResponderObjectType, sub.m_ResponderKey }, 
            DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(responder_call));
        }
        else
        {
          DDSSubscriptionDeleted deleted_msg;
          DDSCreateDeletedSubscriptionResponse(sub, deleted_msg);

          m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ deleted_msg.m_ResponderObjectType, deleted_msg.m_ResponderKey },
            DDSServerToServerMessageType::kSubscriptionDeleted, StormReflEncodeJson(deleted_msg));
        }
      }

      obj_data.m_Subscriptions = new_subs;
      return;
    }

    obj_data.m_State = kDatabaseOnly;
    obj_data.m_DatabaseObject = std::make_unique<DatabaseBackedType>();
    if (StormReflParseJson(*obj_data.m_DatabaseObject.get(), data) == false)
    {
      DDSLog::LogError("Invalid json coming from database");
    }

    InitializeParentInfo(*obj_data.m_DatabaseObject.get());

    for (auto & sub : obj_data.m_Subscriptions)
    {
      if (sub.m_DataPath == "?" && sub.m_IsDataSubscription)
      {
        DDSResponderCallData responder_call;
        DDSCreateSubscriptionExistResponse(true, sub, responder_call);

        m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ sub.m_ResponderObjectType, sub.m_ResponderKey },
          DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(responder_call));
      }
    }

    if (DDSRequiresFullObject(obj_data.m_PendingMessages))
    {
      PromoteObject(key);
    }
    else
    {
      TryProcessAllMessages(key, obj_data);
    }
  }

  void PromoteObject(DDSKey key)
  {
    auto & obj_data = m_Objects.at(key);
    if (obj_data.m_State != kDatabaseOnly || obj_data.m_ActiveObject.get() != nullptr)
    {
      DDSLog::LogError("Incosistent object state");
      return;
    }

    DDSNodeInterface node_interface(m_NodeState, this, key);
    obj_data.m_State = kCreating;
    obj_data.m_ActiveObject = std::make_unique<DataType>(node_interface, *obj_data.m_DatabaseObject.get());

    bool called = 
      DDSCallFuncBeginLoad<DDSHasFuncBeginLoad<std::decay_t<decltype(*obj_data.m_ActiveObject.get())>>::value>::Call(*obj_data.m_ActiveObject.get());

    if (DDS_CALL_FUNC(BeginLoad, *obj_data.m_ActiveObject.get()) == false)
    {
      FinalizeObjectLoad(key);
    }
    else
    {
      TryProcessAllMessages(key, obj_data);
    }
  }

  void FinalizeObjectLoad(DDSKey key)
  {
    auto & obj_data = m_Objects.at(key);
    InitializeParentInfo(*obj_data.m_ActiveObject.get());

    if (obj_data.m_State != kCreating)
    {
      DDSLog::LogError("Incosistent object state");
      return;
    }

    obj_data.m_State = kActive;

    for (auto & msg : obj_data.m_PendingMessages)
    {
      ProcessMessage(key, obj_data, msg.m_Type, msg.m_Message.c_str());
    }

    for (auto & sub : obj_data.m_Subscriptions)
    {
      if (sub.m_DataPath == "?" && sub.m_IsDataSubscription == false)
      {
        DDSResponderCallData responder_call;
        DDSCreateSubscriptionExistResponse(true, sub, responder_call);

        m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ sub.m_ResponderObjectType, sub.m_ResponderKey },
          DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(responder_call));
      }
    }

    obj_data.m_PendingMessages.clear();
  }

  bool TryProcessMessage(DDSKey key, ObjectData & obj_data, DDSServerToServerMessageType message_type, const char * msg)
  {
    bool requires_full_object = DDSRequiresFullObject(message_type);
    bool requires_active_object = DDSRequiresActiveObject(message_type);

    if (obj_data.m_State == kDatabaseOnly && requires_full_object)
    {
      PromoteObject(key);
    }
    else if (obj_data.m_State == kDeleted)
    {
      ReloadObjectByKey(key, obj_data);
    }

    if (obj_data.m_State == kActive || 
      (obj_data.m_State == kCreating && requires_active_object == false) || 
      (obj_data.m_State != kLoading && requires_full_object == false) ||
      (message_type == DDSServerToServerMessageType::kUnlockObject) ||
      (message_type == DDSServerToServerMessageType::kCreateExistSubscription) ||
      (message_type == DDSServerToServerMessageType::kCreateDataExistSubscription))
    {
      ProcessMessage(key, obj_data, message_type, msg);
      return true;
    }

    return false;
  }

  void TryProcessAllMessages(DDSKey key, ObjectData & obj_data)
  {
    std::vector<DDSExportedMessage> remaining_messages;
    for (auto & msg : obj_data.m_PendingMessages)
    {
      if (TryProcessMessage(key, obj_data, msg.m_Type, msg.m_Message.c_str()) == false)
      {
        remaining_messages.emplace_back(std::move(msg));
      }
    }

    obj_data.m_PendingMessages = remaining_messages;
  }

  void HandleMessage(DDSKey key, DDSServerToServerMessageType message_type, const char * msg)
  {
    auto itr = m_Objects.find(key);
    auto & obj_data = itr == m_Objects.end() ? LoadObjectByKey(key) : itr->second;

    if (TryProcessMessage(key, obj_data, message_type, msg) == false)
    {
      obj_data.m_PendingMessages.emplace_back(DDSExportedMessage{ message_type, msg });
    }
  }

  void ProcessMessage(DDSKey key, ObjectData & obj_data, DDSServerToServerMessageType message_type, const char * message)
  {
    switch (message_type)
    {
      case DDSServerToServerMessageType::kTargetedMessage:
      {
        BeginObjectModification(key);
        DDSTargetedMessage targeted_msg;
        StormReflParseJson(targeted_msg, message);

        DDSNodeInterface node_interface(m_NodeState, this, key);
        if (DDSDataObjectHandleMessage(*obj_data.m_ActiveObject.get(), node_interface, targeted_msg) == false)
        {
          DDSLog::LogError("Failed to process message for object");
        }
        EndObjectModification();
      }
      break;
      case DDSServerToServerMessageType::kTargetedMessageResponder:
      {
        BeginObjectModification(key);
        DDSTargetedMessageWithResponder targeted_msg;
        StormReflParseJson(targeted_msg, message);

        DDSNodeInterface node_interface(m_NodeState, this, key);
        if (DDSDataObjectHandleMessage(*obj_data.m_ActiveObject.get(), node_interface, targeted_msg) == false)
        {
          DDSLog::LogError("Failed to process message for object");
        }
        EndObjectModification();
      }
      break;
      case DDSServerToServerMessageType::kResponderCall:
      {
        BeginObjectModification(key);
        DDSResponderCallData responder_call;
        StormReflParseJson(responder_call, message);

        DDSNodeInterface node_interface(m_NodeState, this, key);
        if (DDSDataObjectHandleMessage(*obj_data.m_ActiveObject.get(), node_interface, responder_call) == false)
        {
          DDSLog::LogError("Failed to process message for object");
        }
        EndObjectModification();
      }
      break;
      case DDSServerToServerMessageType::kCreateSubscription:
      case DDSServerToServerMessageType::kCreateDataSubscription:
      {
        DDSCreateSubscription sub_msg;
        StormReflParseJson(sub_msg, message);

        auto & obj_data = m_Objects.at(sub_msg.m_Key);

        DDSExportedSubscription sub_data;
        sub_data.m_DataPath = std::move(sub_msg.m_DataPath);
        sub_data.m_SubscriptionId = sub_msg.m_SubscriptionId;
        sub_data.m_ResponderKey = sub_msg.m_ResponderKey;
        sub_data.m_ResponderObjectType = sub_msg.m_ResponderObjectType;
        sub_data.m_ResponderMethodId = sub_msg.m_ResponderMethodId;
        sub_data.m_ResponderArgs = std::move(sub_msg.m_ReturnArg);
        sub_data.m_IsDataSubscription = (message_type == DDSServerToServerMessageType::kCreateDataSubscription);
        sub_data.m_DeltaOnly = sub_msg.m_DeltaOnly;
        obj_data.m_Subscriptions.emplace_back(std::move(sub_data));

        DDSResponderCallData responder_call;
        if (sub_data.m_IsDataSubscription)
        {
          if (DDSCreateInitialSubscriptionResponse(*obj_data.m_DatabaseObject.get(), sub_data, responder_call) == false)
          {
            DDSLog::LogError("Could not create initial subscription response");
          }
        }
        else
        {
          if (DDSCreateInitialSubscriptionResponse(*obj_data.m_ActiveObject.get(), sub_data, responder_call) == false)
          {
            DDSLog::LogError("Could not create initial subscription response");
          }
        }

        m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ sub_msg.m_ResponderObjectType, sub_msg.m_ResponderKey },
          DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(responder_call));
      }
      break;
      case DDSServerToServerMessageType::kCreateExistSubscription:
      case DDSServerToServerMessageType::kCreateDataExistSubscription:
      {
        DDSCreateExistSubscription sub_msg;
        StormReflParseJson(sub_msg, message);

        auto & obj_data = m_Objects.at(sub_msg.m_Key);

        DDSExportedSubscription sub_data;
        sub_data.m_DataPath = "?";
        sub_data.m_SubscriptionId = sub_msg.m_SubscriptionId;
        sub_data.m_ResponderKey = sub_msg.m_ResponderKey;
        sub_data.m_ResponderObjectType = sub_msg.m_ResponderObjectType;
        sub_data.m_ResponderMethodId = sub_msg.m_ResponderMethodId;
        sub_data.m_ResponderArgs = std::move(sub_msg.m_ReturnArg);
        sub_data.m_IsDataSubscription = (message_type == DDSServerToServerMessageType::kCreateDataExistSubscription);
        sub_data.m_DeltaOnly = false;
        obj_data.m_Subscriptions.emplace_back(std::move(sub_data));

        if (obj_data.m_State == kDeleted)
        {
          DDSResponderCallData responder_call;
          DDSCreateSubscriptionExistResponse(false, sub_data, responder_call);

          m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ sub_msg.m_ResponderObjectType, sub_msg.m_ResponderKey },
            DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(responder_call));
        }
        else if(sub_data.m_IsDataSubscription)
        {
          if (obj_data.m_DatabaseObject.get())
          {
            DDSResponderCallData responder_call;
            DDSCreateSubscriptionExistResponse(true, sub_data, responder_call);

            m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ sub_msg.m_ResponderObjectType, sub_msg.m_ResponderKey },
              DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(responder_call));
          }
        }
        else
        {
          if (obj_data.m_ActiveObject.get())
          {
            DDSResponderCallData responder_call;
            DDSCreateSubscriptionExistResponse(true, sub_data, responder_call);

            m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ sub_msg.m_ResponderObjectType, sub_msg.m_ResponderKey },
              DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(responder_call));
          }
          else
          {
            DDSResponderCallData responder_call;
            DDSCreateSubscriptionExistResponse(false, sub_data, responder_call);

            m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ sub_msg.m_ResponderObjectType, sub_msg.m_ResponderKey },
              DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(responder_call));
          }
        }
      }
      break;
      case DDSServerToServerMessageType::kDestroySubscription:
      {
        DDSDestroySubscription sub_msg;
        StormReflParseJson(sub_msg, message);

        auto & obj_data = m_Objects.at(sub_msg.m_Key);
        for (auto sub_itr = obj_data.m_RequestedSubscriptions.begin(); sub_itr != obj_data.m_RequestedSubscriptions.end(); ++sub_itr)
        {
          if (sub_itr->m_SubscriptionId == sub_msg.m_SubscriptionId)
          {
            obj_data.m_RequestedSubscriptions.erase(sub_itr);
            break;
          }
        }
      }
      break;
      case DDSServerToServerMessageType::kUnlockObject:
      {
        DDSUnlockObject unlock;
        StormReflParseJson(unlock, message);

        auto & obj_data = m_Objects.at(unlock.m_Key);

        if (obj_data.m_State != kLocked)
        {
          DDSLog::LogError("Attempted to unlock and object that wasn't locked");
        }

        if (unlock.m_Data.size() > 0)
        {
          StormReflParseJson(*obj_data.m_DatabaseObject.get(), unlock.m_Data.c_str());
        }

        obj_data.m_State = kActive;
        TryProcessAllMessages(key, obj_data);
      }
      break;
      default:
      {
        DDSLog::LogError("Invalid message type");
      }
    }
  }

  virtual void BeginObjectModification(DDSKey key)
  {
    m_NodeState.BeginQueueingMessages();
    ReflectionPushNotifyCallback([&](const ReflectionChangeNotification & change) { m_Changes.emplace_back(std::make_pair(key, change)); });
  }

  virtual void EndObjectModification()
  {
    ReflectionPopNotifyCallback();

    std::vector<std::pair<DDSKey, ReflectionChangeNotification>> changes = std::move(m_Changes);
    std::vector<DDSKey> dead_keys = std::move(m_DeadObjects);

    for (auto & change_data : changes)
    {
      DDSKey key = change_data.first;
      auto & change = change_data.second;

      auto itr = m_Objects.find(key);
      if (itr == m_Objects.end())
      {
        DDSLog::LogError("Could not find object");
      }

      auto & obj_data = itr->second;
      bool database_changed = false;

      for (auto & sub : obj_data.m_Subscriptions)
      {
        if (DDSCheckChangeSubscription(change, sub))
        {
          if (change.m_BaseObject == obj_data.m_ActiveObject.get())
          {
            DDSResponderCallData call_data;
            if (DDSCreateSubscriptionResponse(*obj_data.m_ActiveObject.get(), change, sub, call_data))
            {
              DDSLog::LogError("Could not serialize subscription change");
            }

            m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ call_data.m_ObjectType, call_data.m_Key }, DDSResponderCallData::Type, StormReflEncodeJson(call_data));
          }
          else if (change.m_BaseObject == obj_data.m_DatabaseObject.get())
          {
            database_changed = true;

            DDSResponderCallData call_data;
            if (DDSCreateSubscriptionResponse(*obj_data.m_DatabaseObject.get(), change, sub, call_data))
            {
              DDSLog::LogError("Could not serialize subscription change");
            }

            m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ call_data.m_ObjectType, call_data.m_Key }, DDSResponderCallData::Type, StormReflEncodeJson(call_data));
          }
        }
      }

      if (database_changed)
      {
        std::string database_obj = StormReflEncodeJson(*obj_data.m_DatabaseObject.get());
        m_NodeState.UpdateObjectData(m_ObjectTypeId, key, DatabaseBackedType::Collection(), database_obj.data(), nullptr);
      }
    }

    for (auto & key : dead_keys)
    {
      m_Objects.erase(key);
    }

    m_NodeState.EndQueueingMessages();
  }

  virtual void LockObject(DDSKey key)
  {
    auto itr = m_Objects.find(key);
    if (itr == m_Objects.end())
    {
      DDSLog::LogError("Could not find object to lock");
      return;
    }

    if (itr->second.m_State != kActive)
    {
      DDSLog::LogError("Could not lock an object in invalide state");
      return;
    }

    itr->second.m_State = kLocked;
  }

  void AssignRequestedSubscription(DDSKey key, const DDSExportedRequestedSubscription & requested_sub)
  {
    auto itr = m_Objects.find(key);
    if (itr == m_Objects.end())
    {
      DDSLog::LogError("Could not find object to add subscription to");
      return;
    }

    itr->second.m_RequestedSubscriptions.emplace_back(requested_sub);
  }

  void RemoveRequestedSubscription(DDSKey key, DDSKey subscription_id)
  {
    auto itr = m_Objects.find(key);
    if (itr == m_Objects.end())
    {
      return;
    }

    for (auto sub_itr = itr->second.m_RequestedSubscriptions.begin(); sub_itr != itr->second.m_RequestedSubscriptions.end(); ++sub_itr)
    {
      if (sub_itr->m_SubscriptionId == subscription_id)
      {
        itr->second.m_RequestedSubscriptions.erase(sub_itr);
        return;
      }
    }
  }

  void PrepareObjectsForMove(DDSKeyRange requested_range)
  {
    if (m_Objects.size() == 0)
    {
      return;
    }

    auto start_itr = m_Objects.lower_bound(requested_range.m_Min);
    auto itr = start_itr;

    while (true)
    {
      if (KeyInKeyRange(itr->first, requested_range) == false)
      {
        break;
      }

      auto & obj_data = itr->second;

      BeginObjectModification(itr->first);
      DDS_CALL_FUNC(PreMoveObject, *obj_data.m_ActiveObject.get());
      EndObjectModification();

      itr++;
      if (itr == m_Objects.end())
      {
        itr = m_Objects.begin();
      }

      if (itr == start_itr)
      {
        break;
      }
    }
  }

  bool ExportObjectsInRange(DDSKeyRange requested_range, DDSKeyRange & output_range, DDSKeyRange & remainder_range, int max_objects, std::vector<DDSExportedObject> & output)
  {
    int num_objects = 0;
    bool complete = true;

    output_range = requested_range;

    if (m_Objects.size() == 0)
    {
      return true;
    }

    auto start_itr = m_Objects.lower_bound(requested_range.m_Min);
    auto itr = start_itr;

    if (itr == m_Objects.end())
    {
      itr = m_Objects.begin();
    }

    std::vector<decltype(itr)> saved_itrs;

    while(true)
    {
      if (num_objects >= max_objects)
      {
        complete = false;
        output_range = DDSKeyRange{ requested_range.m_Min, itr->first - 1 };
        remainder_range = DDSKeyRange{ itr->first, requested_range.m_Max };
        break;
      }

      if (KeyInKeyRange(itr->first, requested_range) == false)
      {
        break;
      }

      if (itr->second.m_State == kActive || itr->second.m_State == kCreating || itr->second.m_PendingMessages.size() > 0)
      {
        DDSExportedObjectState state;
        if (itr->second.m_State == kActive)
        {
          state = DDSExportedObjectState::kLoaded;
        }
        else if (itr->second.m_State == kLocked)
        {
          state = DDSExportedObjectState::kLocked;
        }
        else
        {
          state = DDSExportedObjectState::kNotLoaded;
        }

        DDSExportedObject obj = { itr->first, state };
        if (itr->second.m_ActiveObject)
        {
          StormReflEncodeJson(*itr->second.m_ActiveObject.get(), obj.m_ActiveObject);
          num_objects++;
        }

        if (itr->second.m_DatabaseObject)
        {
          StormReflEncodeJson(*itr->second.m_DatabaseObject.get(), obj.m_DatabaseObject);
          num_objects++;
        }

        for (auto & message : itr->second.m_PendingMessages)
        {
          obj.m_PendingMessages.emplace_back(message);
          num_objects++;
        }

        for (auto & sub : itr->second.m_Subscriptions)
        {
          obj.m_Subscriptions.emplace_back(sub);
        }

        for (auto & req_sub : itr->second.m_RequestedSubscriptions)
        {
          obj.m_RequestedSubscriptions.emplace_back(req_sub);
        }

        m_NodeState.ExportSharedSubscriptions(DDSDataObjectAddress{ m_ObjectTypeId, itr->first }, obj.m_SharedSubscriptions);

        output.emplace_back(std::move(obj));
        num_objects++;

        saved_itrs.push_back(itr);
      }

      itr++;
      if (itr == m_Objects.end())
      {
        itr = m_Objects.begin();
      }

      if (itr == start_itr)
      {
        break;
      }
    }

    for (auto itr : saved_itrs)
    {
      m_Objects.erase(itr);
    }

    return complete;
  }

  void ProcessExportedObjects(std::vector<DDSExportedObject> & object_list)
  {
    for (auto & object : object_list)
    {
      ObjectData obj_data = { };

      obj_data.m_PendingMessages = std::move(object.m_PendingMessages);
      obj_data.m_Subscriptions = std::move(object.m_Subscriptions);
      obj_data.m_RequestedSubscriptions = std::move(object.m_RequestedSubscriptions);

      if (object.m_DatabaseObject.size() > 0)
      {
        obj_data.m_DatabaseObject = std::make_unique<DatabaseBackedType>();
        if (StormReflParseJson(*obj_data.m_DatabaseObject.get(), object.m_DatabaseObject.c_str()) == false)
        {
          DDSLog::LogError("Could not properly parse external sync message");
          continue;
        }

        if (object.m_ActiveObject.size() > 0)
        {
          DDSNodeInterface node_interface(m_NodeState, this, object.m_Key);
          obj_data.m_ActiveObject = std::make_unique<DataType>(node_interface, *obj_data.m_DatabaseObject.get());
          if (StormReflParseJson(*obj_data.m_ActiveObject.get(), object.m_ActiveObject.c_str()) == false)
          {
            DDSLog::LogError("Could not properly parse external sync message");
            return;
          }

          if (object.m_State == DDSExportedObjectState::kLoaded)
          {
            obj_data.m_State = kActive;
          }
          else if (object.m_State == DDSExportedObjectState::kLocked)
          {
            obj_data.m_State = kLocked;
          }
          else
          {
            obj_data.m_State = kCreating;
          }

          m_NodeState.ImportSharedSubscriptions(DDSDataObjectAddress{ m_ObjectTypeId, object.m_Key }, object.m_SharedSubscriptions);
          m_Objects.emplace(std::make_pair(object.m_Key, std::move(obj_data)));
        }
        else
        {
          obj_data.m_State = kDatabaseOnly;
          m_Objects.emplace(std::make_pair(object.m_Key, std::move(obj_data)));
        }
      }
      {
        obj_data.m_State = kDeleted;
        auto result = m_Objects.emplace(std::make_pair(object.m_Key, std::move(obj_data)));
        ReloadObjectByKey(object.m_Key, result.first->second);
      }
    }

    for (auto & object : object_list)
    {

    }
  }

private:

  DDSNodeState & m_NodeState;
  std::string m_Collection;
  int m_ObjectTypeId;

  std::map<DDSKey, ObjectData> m_Objects;
  std::vector<std::pair<DDSKey, ReflectionChangeNotification>> m_Changes;
  std::vector<DDSKey> m_DeadObjects;
};


template <class DataType>
class DDSDataObjectStore<DataType, void> : public DDSDataObjectStoreBase
{
  struct ObjectData
  {
    bool m_Active;
    std::unique_ptr<DataType> m_ActiveObject;
    std::vector<DDSExportedMessage> m_PendingMessages;
    std::vector<DDSExportedSubscription> m_Subscriptions;
    std::vector<DDSExportedRequestedSubscription> m_RequestedSubscriptions;
  };

public:

  DDSDataObjectStore(DDSNodeState & node_state, int object_type_id) :
    m_NodeState(node_state), m_ObjectTypeId(object_type_id)
  {

  }

  uint32_t GetDataClassNameHash() const
  {
    return StormReflTypeInfo<DataType>::GetNameHash();
  }

  uint32_t GetDatabaseClassNameHash() const
  {
    return 0;
  }

  void SpawnNewNonDatabaseBackedType(DDSKey key)
  {
    DDSNodeInterface node_interface(m_NodeState, this, key);
    auto itr = m_Objects.emplace(std::make_pair(key, ObjectData{ false, std::make_unique<DataType>(node_interface) }));
    auto & obj_data = itr.first->second;

    obj_data.m_ActiveObject = std::make_unique<DataType>(node_interface);
    InitializeParentInfo(*obj_data.m_ActiveObject.get());

    if (DDS_CALL_FUNC(BeginLoad, *obj_data.m_ActiveObject.get()) == false)
    {
      FinalizeObjectLoad(key);
    }
  }

  void FinalizeObjectLoad(DDSKey key)
  {
    auto & obj_data = m_Objects.at(key);
    if (obj_data.m_Active)
    {
      DDSLog::LogError("Incosistent object state");
      return;
    }

    obj_data.m_Active = true;

    for (auto & msg : obj_data.m_PendingMessages)
    {
      ProcessMessage(key, obj_data, msg.m_Type, msg.m_Message.c_str());
    }

    obj_data.m_PendingMessages.clear();
  }

  bool DestroyNonDatabaseBackedType(DDSKey key)
  {
    return m_Objects.erase(key) > 0;
  }

  virtual void * GetDataObjectForKey(DDSKey key)
  {
    auto itr = m_Objects.find(key);
    if (itr == m_Objects.end())
    {
      return nullptr;
    }

    return itr->second.m_ActiveObject.get();
  }

  DDSKey GetUnusedKeyInRange(DDSKeyRange range)
  {
    while (true)
    {
      DDSKey test_key = GetRandomKeyInRange(range);

      if (m_Objects.find(test_key) == m_Objects.end())
      {
        return test_key;
      }
    }
  }

  void DestroyObject(DDSKey key)
  {
    if (m_Changes.size() == 0)
    {
      auto itr = m_Objects.find(key);

      if (itr != m_Objects.end())
      {
        DDS_CALL_FUNC(PreDestroy, *itr);
        m_Objects.erase(itr);
      }
    }
    else
    {
      m_DeadObjects.push_back(key);
    }
  }

  void HandleMessage(DDSKey key, DDSServerToServerMessageType message_type, const char * msg)
  {
    auto itr = m_Objects.find(key);
    if (itr == m_Objects.end())
    {
      return;
    }

    auto & obj_data = itr->second;

    TryProcessMessage(key, obj_data, message_type, msg);
  }

  virtual void HandleLoadResult(DDSKey key, const char * data, int ec)
  {
    DDSLog::LogError("Got query result for non database backed type");
  }

  bool TryProcessMessage(DDSKey key, ObjectData & obj_data, DDSServerToServerMessageType message_type, const char * message)
  {
    if (obj_data.m_Active == false && DDSRequiresActiveObject(message_type))
    {
      obj_data.m_PendingMessages.emplace_back(DDSExportedMessage{ message_type, message });
      return false;
    }

    ProcessMessage(key, obj_data, message_type, message);
    return true;
  }

  void ProcessMessage(DDSKey key, ObjectData & obj_data, DDSServerToServerMessageType message_type, const char * message)
  {
    switch (message_type)
    {
      case DDSServerToServerMessageType::kTargetedMessage:
      {
        BeginObjectModification(key);
        DDSTargetedMessage targeted_msg;
        StormReflParseJson(targeted_msg, message);

        DDSNodeInterface node_interface(m_NodeState, this, key);
        if (DDSDataObjectHandleMessage(*obj_data.m_ActiveObject.get(), node_interface, targeted_msg) == false)
        {
          DDSLog::LogError("Failed to process message for object");
        }

        EndObjectModification();
      }
      break;
      case DDSServerToServerMessageType::kTargetedMessageResponder:
      {
        BeginObjectModification(key);
        DDSTargetedMessageWithResponder targeted_msg;
        StormReflParseJson(targeted_msg, message);

        DDSNodeInterface node_interface(m_NodeState, this, key);
        if (DDSDataObjectHandleMessage(*obj_data.m_ActiveObject.get(), node_interface, targeted_msg) == false)
        {
          DDSLog::LogError("Failed to process message for object");
        }

        EndObjectModification();
      }
      break;
      case DDSServerToServerMessageType::kResponderCall:
      {
        BeginObjectModification(key);
        DDSResponderCallData responder_call;
        StormReflParseJson(responder_call, message);

        DDSNodeInterface node_interface(m_NodeState, this, key);
        if (DDSDataObjectHandleMessage(*obj_data.m_ActiveObject.get(), node_interface, responder_call) == false)
        {
          DDSLog::LogError("Failed to process message for object");
        }
        EndObjectModification();
      }
      break;
      case DDSServerToServerMessageType::kCreateDataSubscription:
      {
        DDSLog::LogError("Can't subscript to data object for non database type");
      }
      break;
      case DDSServerToServerMessageType::kCreateSubscription:
      {
        DDSCreateSubscription sub_msg;
        StormReflParseJson(sub_msg, message);

        auto itr = m_Objects.find(sub_msg.m_Key);
        if (itr == m_Objects.end())
        {
          return;
        }

        auto & obj_data = itr->second;

        DDSExportedSubscription sub_data;
        sub_data.m_DataPath = std::move(sub_msg.m_DataPath);
        sub_data.m_SubscriptionId = sub_msg.m_SubscriptionId;
        sub_data.m_ResponderKey = sub_msg.m_ResponderKey;
        sub_data.m_ResponderObjectType = sub_msg.m_ResponderObjectType;
        sub_data.m_ResponderMethodId = sub_msg.m_ResponderMethodId;
        sub_data.m_ResponderArgs = std::move(sub_msg.m_ReturnArg);
        sub_data.m_IsDataSubscription = (message_type == DDSServerToServerMessageType::kCreateDataSubscription);
        sub_data.m_DeltaOnly = sub_msg.m_DeltaOnly;
        obj_data.m_Subscriptions.emplace_back(std::move(sub_data));

        DDSResponderCallData responder_call;
        if (DDSCreateInitialSubscriptionResponse(*obj_data.m_ActiveObject.get(), sub_data, responder_call) == false)
        {
          DDSLog::LogError("Could not create initial subscription response");
        }
      
        m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ sub_msg.m_ResponderObjectType, sub_msg.m_ResponderKey },
          DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(responder_call));
      }
      break;
      case DDSServerToServerMessageType::kDestroySubscription:
      {
        DDSDestroySubscription sub_msg;
        StormReflParseJson(sub_msg, message);

        auto itr = m_Objects.find(sub_msg.m_Key);
        if (itr == m_Objects.end())
        {
          return;
        }

        auto & obj_data = itr->second;
        for (auto sub_itr = obj_data.m_RequestedSubscriptions.begin(); sub_itr != obj_data.m_RequestedSubscriptions.end(); ++sub_itr)
        {
          if (sub_itr->m_SubscriptionId == sub_msg.m_SubscriptionId)
          {
            obj_data.m_RequestedSubscriptions.erase(sub_itr);
            break;
          }
        }
      }
      break;
      default:
      {
        DDSLog::LogError("Invalid message type");
      }
    }
  }

  virtual void BeginObjectModification(DDSKey key)
  {
    m_NodeState.BeginQueueingMessages();
    ReflectionPushNotifyCallback([this, key](const ReflectionChangeNotification & change) { m_Changes.emplace_back(std::make_pair(key, change)); });
  }

  virtual void EndObjectModification()
  {
    ReflectionPopNotifyCallback();

    std::vector<std::pair<DDSKey, ReflectionChangeNotification>> changes = std::move(m_Changes);
    std::vector<DDSKey> dead_keys = std::move(m_DeadObjects);

    for (auto & change_data : changes)
    {
      DDSKey key = change_data.first;
      auto & change = change_data.second;

      auto itr = m_Objects.find(key);
      if (itr == m_Objects.end())
      {
        DDSLog::LogError("Could not find object");
      }

      auto & obj_data = itr->second;

      for (auto & sub : obj_data.m_Subscriptions)
      {
        if (DDSCheckChangeSubscription(change, sub))
        {
          DDSResponderCallData call_data;
          if (DDSCreateSubscriptionResponse(*obj_data.m_ActiveObject.get(), change, sub, call_data))
          {
            DDSLog::LogError("Could not serialize subscription change");
          }

          m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ call_data.m_ObjectType, call_data.m_Key }, DDSResponderCallData::Type, StormReflEncodeJson(call_data));
        }
      }
    }

    for (auto & key : dead_keys)
    {
      auto itr = m_Objects.find(key);

      if (itr != m_Objects.end())
      {
        DDS_CALL_FUNC(PreDestroy, *itr);
        m_Objects.erase(itr);
      }
    }

    m_NodeState.EndQueueingMessages();
  }

  void LockObject(DDSKey key)
  {
    DDSLog::LogError("Attempting to lock an unlockable object");
  }

  void AssignRequestedSubscription(DDSKey key, const DDSExportedRequestedSubscription & requested_sub)
  {
    auto itr = m_Objects.find(key);
    if (itr == m_Objects.end())
    {
      DDSLog::LogError("Could not find object to add subscription to");
      return;
    }

    itr->second.m_RequestedSubscriptions.emplace_back(requested_sub);
  }

  void RemoveRequestedSubscription(DDSKey key, DDSKey subscription_id)
  {
    auto itr = m_Objects.find(key);
    if (itr == m_Objects.end())
    {
      return;
    }

    for (auto sub_itr = itr->second.m_RequestedSubscriptions.begin(); sub_itr != itr->second.m_RequestedSubscriptions.end(); ++sub_itr)
    {
      if (sub_itr->m_SubscriptionId == subscription_id)
      {
        itr->second.m_RequestedSubscriptions.erase(sub_itr);
        return;
      }
    }
  }

  void PrepareObjectsForMove(DDSKeyRange requested_range)
  {
    if (m_Objects.size() == 0)
    {
      return;
    }

    auto start_itr = m_Objects.lower_bound(requested_range.m_Min);
    auto itr = start_itr;

    while (true)
    {
      if (KeyInKeyRange(itr->first, requested_range) == false)
      {
        break;
      }

      auto & obj_data = itr->second;

      BeginObjectModification(itr->first);
      DDS_CALL_FUNC(PreMoveObject, *obj_data.m_ActiveObject.get());
      EndObjectModification();

      itr++;
      if (itr == m_Objects.end())
      {
        itr = m_Objects.begin();
      }

      if (itr == start_itr)
      {
        break;
      }
    }
  }

  bool ExportObjectsInRange(DDSKeyRange requested_range, DDSKeyRange & output_range, DDSKeyRange & remainder_range, 
                            int max_objects, std::vector<DDSExportedObject> & output)
  {
    int num_objects = 0;
    bool complete = true;

    output_range = requested_range;

    if (m_Objects.size() == 0)
    {
      return true;
    }

    auto start_itr = m_Objects.lower_bound(requested_range.m_Min);
    auto itr = start_itr;

    if (itr == m_Objects.end())
    {
      itr = m_Objects.begin();
    }

    std::vector<decltype(itr)> saved_itrs;

    while (true)
    {
      if (num_objects >= max_objects)
      {
        complete = false;
        output_range = DDSKeyRange{ requested_range.m_Min, itr->first - 1 };
        remainder_range = DDSKeyRange{ itr->first, requested_range.m_Max };
        break;
      }

      if (KeyInKeyRange(itr->first, requested_range) == false)
      {
        break;
      }

      DDSExportedObjectState state = itr->second.m_Active ? DDSExportedObjectState::kLoaded : DDSExportedObjectState::kNotLoaded;

      DDSExportedObject obj = { itr->first, state };
      StormReflEncodeJson(*itr->second.m_ActiveObject.get(), obj.m_ActiveObject);

      obj.m_PendingMessages = std::move(itr->second.m_PendingMessages);
      obj.m_Subscriptions = std::move(itr->second.m_Subscriptions);
      obj.m_RequestedSubscriptions = std::move(itr->second.m_RequestedSubscriptions);

      m_NodeState.ExportSharedSubscriptions(DDSDataObjectAddress{ m_ObjectTypeId, itr->first }, obj.m_SharedSubscriptions);

      output.emplace_back(std::move(obj));
      num_objects++;

      saved_itrs.push_back(itr);

      itr++;
      if (itr == m_Objects.end())
      {
        itr = m_Objects.begin();
      }

      if (itr == start_itr)
      {
        break;
      }
    }

    for (auto itr : saved_itrs)
    {
      m_Objects.erase(itr);
    }

    return complete;
  }

  void ProcessExportedObjects(std::vector<DDSExportedObject> & object_list)
  {
    for (auto & object : object_list)
    {
      DDSNodeInterface node_interface(m_NodeState, this, object.m_Key);
      ObjectData obj_data = { object.m_State == DDSExportedObjectState::kLoaded, std::make_unique<DataType>(node_interface) };

      if (StormReflParseJson(*obj_data.m_ActiveObject.get(), object.m_ActiveObject.c_str()) == false)
      {
        DDSLog::LogError("Could not properly parse external sync message");
        return;
      }

      obj_data.m_PendingMessages = std::move(object.m_PendingMessages);
      obj_data.m_Subscriptions = std::move(object.m_Subscriptions);
      obj_data.m_RequestedSubscriptions = std::move(object.m_RequestedSubscriptions);

      m_NodeState.ImportSharedSubscriptions(DDSDataObjectAddress{ m_ObjectTypeId, object.m_Key }, object.m_SharedSubscriptions);

      DDS_CALL_FUNC(MoveObject, *obj_data.m_ActiveObject.get());

      m_Objects.emplace(std::make_pair(object.m_Key, std::move(obj_data)));
    }
  }

private:

  DDSNodeState & m_NodeState;
  std::string m_Collection;
  int m_ObjectTypeId;

  std::map<DDSKey, ObjectData> m_Objects;
  std::vector<std::pair<DDSKey, ReflectionChangeNotification>> m_Changes;
  int m_ChangeQueueDepth;

  std::vector<DDSKey> m_DeadObjects;
};
