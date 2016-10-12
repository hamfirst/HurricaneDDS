#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <memory>


#include "DDSKey.h"
#include "DDSLog.h"
#include "DDSRandom.h"
#include "DDSNodeState.h"
#include "DDSDataObjectStoreBase.h"
#include "DDSDatabaseConnectionPool.h"
#include "DDSResponder.h"
#include "DDSResponderCall.h"
#include "DDSNodeInterface.h"
#include "DDSServerMessage.h"
#include "DDSDataObjectStoreHelpers.h"

#include <StormRefl\StormReflJsonStd.h>
#include <StormRefl\StormReflMetaCallJson.h>
#include <StormData\StormDataChangeNotifier.h>
#include <StormData\StormDataPath.h>
#include <StormData\StormDataJsonUtil.h>

DDS_DECLARE_CALL(BeginLoad);
DDS_DECLARE_CALL(MoveObject);

template <class DataType, class DatabaseBackedType>
class DDSDataObjectStore : public DDSDataObjectStoreBase
{
  enum ObjectState
  {
    kLoading,
    kDatabaseOnly,
    kCreating,
    kActive,
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
      DDSKey size = GetKeyRangeSize(range);
      DDSKey test_key = (DDSGetRandomNumber64() % size) + range.m_Min;

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

      for (auto & sub : obj_data.m_Subscriptions)
      {
        DDSSubscriptionDeleted deleted_msg;
        DDSCreateDeletedSubscriptionResponse(sub, deleted_msg);

        m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ deleted_msg.m_ResponderObjectType, deleted_msg.m_ResponderKey },
          DDSServerToServerMessageType::kSubscriptionDeleted, DDSGetServerMessage(deleted_msg));
      }

      obj_data.m_Subscriptions.clear();
      return;
    }

    obj_data.m_State = kDatabaseOnly;
    obj_data.m_DatabaseObject = std::make_unique<DatabaseBackedType>();
    if (StormReflParseJson(*obj_data.m_DatabaseObject.get(), data) == false)
    {
      DDSLog::LogError("Invalid json coming from database");
    }

    if (DDSRequiresFullObject(obj_data.m_PendingMessages))
    {
      PromoteObject(key);
    }
    else
    {
      TryProcessAllMessage(key, obj_data);
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

    if (DDS_CALL_FUNC(BeginLoad, *obj_data.m_ActiveObject.get()) == false)
    {
      FinalizeObjectLoad(key);
    }
    else
    {
      TryProcessAllMessage(key, obj_data);
    }
  }

  void FinalizeObjectLoad(DDSKey key)
  {
    auto & obj_data = m_Objects.at(key);
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

    if (obj_data.m_State == kActive || (obj_data.m_State == kCreating && requires_active_object == false) || (obj_data.m_State != kLoading && requires_full_object == false))
    {
      ProcessMessage(key, obj_data, message_type, msg);
      return true;
    }

    return false;
  }

  void TryProcessAllMessage(DDSKey key, ObjectData & obj_data)
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
        if (DDSDataObjectHandleMessage(*obj_data.m_ActiveObject.get(), m_NodeState, targeted_msg) == false)
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
        if (DDSDataObjectHandleMessage(*obj_data.m_ActiveObject.get(), m_NodeState, targeted_msg) == false)
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
        if (DDSDataObjectHandleMessage(*obj_data.m_ActiveObject.get(), m_NodeState, responder_call) == false)
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
          DDSServerToServerMessageType::kResponderCall, DDSGetServerMessage(responder_call));
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
    m_ChangeQueueDepth++;
    ReflectionPushNotifyCallback([&](const ReflectionChangeNotification & change) { m_Changes.emplace_back(std::make_pair(key, change)); });
  }

  virtual void EndObjectModification()
  {
    ReflectionPopNotifyCallback();
    while (m_ChangeQueueDepth == 1)
    {
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
            if (change.m_BaseObject == obj_data.m_ActiveObject.get())
            {
              DDSResponderCallData call_data;
              if (DDSCreateSubscriptionResponse(*obj_data.m_ActiveObject.get(), change, sub, call_data))
              {
                DDSLog::LogError("Could not serialize subscription change");
              }

              m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ call_data.m_ObjectType, call_data.m_Key }, DDSResponderCallData::Type, DDSGetServerMessage(call_data));
            }
            else if (change.m_BaseObject == obj_data.m_DatabaseObject.get())
            {
              DDSResponderCallData call_data;
              if (DDSCreateSubscriptionResponse(*obj_data.m_DatabaseObject.get(), change, sub, call_data))
              {
                DDSLog::LogError("Could not serialize subscription change");
              }

              m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ call_data.m_ObjectType, call_data.m_Key }, DDSResponderCallData::Type, DDSGetServerMessage(call_data));
            }
          }
        }
      }

      for (auto & key : dead_keys)
      {
        m_Objects.erase(key);
      }
    }

    m_ChangeQueueDepth--;
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
        DDSExportedObject obj = { itr->first, itr->second.m_State == kActive };
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

  void ProcessExportedObjects(const std::vector<DDSExportedObject> & object_list)
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

          if (object.m_IsLoaded)
          {
            obj_data.m_State = kActive;
          }
          else
          {
            obj_data.m_State = kCreating;
          }

          DDS_CALL_FUNC(MoveObject, *obj_data.m_ActiveObject.get());
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
  }

private:

  DDSNodeState & m_NodeState;
  std::string m_Collection;
  int m_ObjectTypeId;

  std::unordered_map<DDSKey, ObjectData> m_Objects;
  std::vector<std::pair<DDSKey, ReflectionChangeNotification>> m_Changes;
  std::vector<DDSKey> m_DeadObjects;
  int m_ChangeQueueDepth;
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
      DDSKey size = GetKeyRangeSize(range);
      DDSKey test_key = (DDSGetRandomNumber64() % size) + range.m_Min;

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
      m_Objects.erase(key);
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
        if (DDSDataObjectHandleMessage(*obj_data.m_ActiveObject.get(), m_NodeState, targeted_msg) == false)
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
        if (DDSDataObjectHandleMessage(*obj_data.m_ActiveObject.get(), m_NodeState, targeted_msg) == false)
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
        if (DDSDataObjectHandleMessage(*obj_data.m_ActiveObject.get(), m_NodeState, responder_call) == false)
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
        if (DDSCreateInitialSubscriptionResponse(*obj_data.m_ActiveObject.get(), sub_data, responder_call) == false)
        {
          DDSLog::LogError("Could not create initial subscription response");
        }
      
        m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ sub_msg.m_ResponderObjectType, sub_msg.m_ResponderKey },
          DDSServerToServerMessageType::kResponderCall, DDSGetServerMessage(responder_call));
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
    m_ChangeQueueDepth++;
    ReflectionPushNotifyCallback([&](const ReflectionChangeNotification & change) { m_Changes.emplace_back(std::make_pair(key, change)); });
  }

  virtual void EndObjectModification()
  {
    ReflectionPopNotifyCallback();
    while (m_ChangeQueueDepth == 1)
    {
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

            m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ call_data.m_ObjectType, call_data.m_Key }, DDSResponderCallData::Type, DDSGetServerMessage(call_data));
          }
        }
      }

      for (auto & key : dead_keys)
      {
        m_Objects.erase(key);
      }
    }

    m_ChangeQueueDepth--;
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

      DDSExportedObject obj = { itr->first, itr->second.m_Active };
      StormReflEncodeJson(*itr->second.m_ActiveObject.get(), obj.m_ActiveObject);

      obj.m_PendingMessages = std::move(itr->second.m_PendingMessages);
      obj.m_Subscriptions = std::move(itr->second.m_Subscriptions);
      obj.m_RequestedSubscriptions = std::move(itr->second.m_RequestedSubscriptions);

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

  void ProcessExportedObjects(const std::vector<DDSExportedObject> & object_list)
  {
    for (auto & object : object_list)
    {
      DDSNodeInterface node_interface(m_NodeState, this, object.m_Key);
      ObjectData obj_data = { object.m_IsLoaded, std::make_unique<DataType>(node_interface) };

      if (StormReflParseJson(*obj_data.m_ActiveObject.get(), object.m_ActiveObject.c_str()) == false)
      {
        DDSLog::LogError("Could not properly parse external sync message");
        return;
      }

      obj_data.m_PendingMessages = std::move(object.m_PendingMessages);
      obj_data.m_Subscriptions = std::move(object.m_Subscriptions);
      obj_data.m_RequestedSubscriptions = std::move(object.m_RequestedSubscriptions);

      DDS_CALL_FUNC(MoveObject, *obj_data.m_ActiveObject.get());

      m_Objects.emplace(std::make_pair(object.m_Key, std::move(obj_data)));
    }
  }

private:

  DDSNodeState & m_NodeState;
  std::string m_Collection;
  int m_ObjectTypeId;

  std::unordered_map<DDSKey, ObjectData> m_Objects;
  std::vector<std::pair<DDSKey, ReflectionChangeNotification>> m_Changes;
  int m_ChangeQueueDepth;

  std::vector<DDSKey> m_DeadObjects;
};
