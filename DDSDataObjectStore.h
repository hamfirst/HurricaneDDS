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
#include "DDSAggregateSubscription.h"
#include "DDSSharedLocalCopy.h"
#include "DDSDataObjectStoreHelpers.h"

#include <StormRefl/StormReflJsonStd.h>
#include <StormRefl/StormReflMetaCallJson.h>
#include <StormData/StormDataChangeNotifier.h>
#include <StormData/StormDataPath.h>
#include <StormData/StormDataJsonUtil.h>
#include <StormData/StormDataParent.h>

#include <sb/vector.h>

DDS_DECLARE_CALL(BeginLoad);
DDS_DECLARE_CALL(PreMoveObject);
DDS_DECLARE_CALL(MoveObject);
DDS_DECLARE_CALL(PreDestroy);

template <class DataType, class DatabaseBackedType>
class DDSDataObjectStore : public DDSDataObjectStoreBase
{
  enum ObjectState
  {
    kUnloaded,
    kLoading,
    kDatabaseOnly,
    kCreating,
    kActive,
    kLocked,
    kDeleted,
  };

  struct CallbackData
  {
    DDSKey m_Key;
    DDSDataObjectStore<DataType, DatabaseBackedType> * m_DataStore;
  };

  struct ObjectData
  {
    ObjectState m_State;
    int m_ObjectDataGen;
    int m_DatabaseDataGen;
    std::unique_ptr<DataType> m_ActiveObject;
    std::unique_ptr<DatabaseBackedType> m_DatabaseObject;
    std::unique_ptr<CallbackData> m_CallbackData;
    std::vector<DDSExportedMessage> m_PendingMessages;
    std::vector<DDSExportedSubscription> m_Subscriptions;
    std::vector<DDSExportedRequestedSubscription> m_RequestedSubscriptions;
    std::vector<DDSAggregateSubscription> m_AggregateSubscriptions;
    std::vector<DDSExportedAggregateRequestedSubscription> m_RequestedAggregateSubscriptions;
  };

public:
  DDSDataObjectStore(DDSNodeState & node_state, int object_type_id) :
    m_NodeState(node_state), m_Collection(DatabaseBackedType::Collection()), m_ObjectTypeId(object_type_id), m_Modifying(false), m_Processing(false)
  {

  }

  int GetDataTypeId() const
  {
    return m_ObjectTypeId;
  }

  uint32_t GetDataClassNameHash() const
  {
    return StormReflTypeInfo<DataType>::GetNameHash();
  }

  uint32_t GetDatabaseClassNameHash() const
  {
    return StormReflTypeInfo<DatabaseBackedType>::GetNameHash();
  }

  DDSDataObjectPriority GetPriority()
  {
    return DataType::GetPriority();
  }

  static bool GetObjectDataAtPath(void * obj, const char * path, std::string & data)
  {
    auto visitor = [&](auto & f, const char * str)
    {
      data = StormReflEncodeJson(f);
      return true;
    };

    return StormDataVisitPath(*(DataType *)obj, visitor, path);
  };

  static bool GetDatabaseDataAtPath(void * obj, const char * path, std::string & data)
  {
    auto visitor = [&](auto & f, const char * str)
    {
      data = StormReflEncodeJson(f);
      return true;
    };

    return StormDataVisitPath(*(DataType *)obj, visitor, path);
  };

  void SpawnNewNonDatabaseBackedType(DDSKey key)
  {
    throw std::runtime_error("Trying to create a non database backed type for a database backed data store");
  }

  bool Destroy(DDSKey key)
  {
    if (m_Modifying == false)
    {
      auto itr = m_Objects.find(key);

      if (itr != m_Objects.end())
      {
        BeginObjectModification(key);
        auto & obj_data = itr->second;

        if (obj_data.m_ActiveObject.get() != nullptr)
        {
          DDS_CALL_FUNC(PreDestroy, *obj_data.m_ActiveObject.get());
        }

        for (auto & sub : obj_data.m_Subscriptions)
        {
          if (sub.m_State != kSubSentInvalid)
          {
            DDSResponderCallData error_msg;
            if (DDSCreateErrorSubscriptionResponse(sub, error_msg))
            {
              m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ error_msg.m_ObjectType, error_msg.m_Key },
                DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(error_msg));
            }
          }
        }

        for (auto & sub : obj_data.m_RequestedSubscriptions)
        {
          DDSDestroySubscription sub_data;
          sub_data.m_Key = sub.m_Key;
          sub_data.m_ObjectType = sub.m_ObjectType;
          sub_data.m_SubscriptionId = sub.m_SubscriptionId;

          m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ sub.m_ObjectType, sub.m_Key },
            DDSServerToServerMessageType::kDestroySubscription, StormReflEncodeJson(sub_data));
        }

        m_NodeState.DeleteObjectData(m_ObjectTypeId, key, m_Collection.data(), nullptr);
        obj_data.m_ActiveObject.reset();
        obj_data.m_DatabaseObject.reset();
        obj_data.m_RequestedSubscriptions.clear();
        obj_data.m_PendingMessages.clear();
        obj_data.m_State = kDeleted;

        for (auto & sub : obj_data.m_RequestedAggregateSubscriptions)
        {
          m_NodeState.m_SharedLocalCopyDatabase.DestroySharedLocalCopySubscription(sub.m_SharedLocalCopyKey, sub.m_SubscriptionId);
        }

        for (auto & sub : obj_data.m_AggregateSubscriptions)
        {
          sub.HandleObjectDestroyed();
        }
       
        EndObjectModification();
      }
    }
    else
    {
      m_DeadObjects.push_back(key);
    }

    return true;
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
    DDSLog::LogInfo("- Loading Object");

    auto insert_data = m_Objects.emplace(std::make_pair(key, ObjectData{ kLoading, 1, 1 }));
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
      DDSLog::LogInfo("- Object loading complete (failure)");
      obj_data.m_State = kDeleted;

      for (auto & msg : obj_data.m_PendingMessages)
      {
        ProcessMessage(key, obj_data, msg.m_Type, msg.m_Message.c_str());
      }

      obj_data.m_PendingMessages.clear();

      for (auto & sub : obj_data.m_Subscriptions)
      {
        if (sub.m_State != kSubSentInvalid)
        {
          DDSResponderCallData responder_call;
          if (DDSCreateErrorSubscriptionResponse(sub, responder_call))
          {
            m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ sub.m_ResponderObjectType, sub.m_ResponderKey },
              DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(responder_call));
          }
        }
      }

      return;
    }

    DDSLog::LogInfo("- Object loading complete");

    obj_data.m_State = kDatabaseOnly;
    obj_data.m_DatabaseObject = std::make_unique<DatabaseBackedType>();
    if (StormReflParseJson(*obj_data.m_DatabaseObject.get(), data) == false)
    {
      DDSLog::LogError("Invalid json coming from database");
    }

    InitializeParentInfo(*obj_data.m_DatabaseObject.get());

    obj_data.m_CallbackData = std::make_unique<CallbackData>();
    obj_data.m_CallbackData->m_Key = key;
    obj_data.m_CallbackData->m_DataStore = this;

    auto database_callback = [](void * user_ptr, const ReflectionChangeNotification & change)
    {
      CallbackData * cb = (CallbackData *)user_ptr;
      cb->m_DataStore->HandleDatabaseObjectChange(cb->m_Key, change);
    };

    SetNotifyCallback(*obj_data.m_DatabaseObject.get(), database_callback, obj_data.m_CallbackData.get());

    for (auto & sub : obj_data.m_Subscriptions)
    {
      if (sub.m_IsDataSubscription)
      {
        DDSResponderCallData responder_call;
        DDSCreateInitialSubscriptionResponse(*obj_data.m_DatabaseObject.get(), sub, responder_call);

        m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ sub.m_ResponderObjectType, sub.m_ResponderKey },
          DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(responder_call));
      }
    }

    if (DDSRequiresFullObject(obj_data.m_PendingMessages, obj_data.m_Subscriptions))
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
    if (m_Modifying)
    {
      m_PromotedObjects.push_back(key);
      return;
    }

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
      TryProcessAllMessages(key, obj_data);
    }
  }

  void FinalizeObjectLoad(DDSKey key)
  {
    if (m_Modifying)
    {
      m_FinalizedObjects.push_back(key);
      return;
    }

    auto & obj_data = m_Objects.at(key);
    InitializeParentInfo(*obj_data.m_ActiveObject.get());

    auto data_obj_callback = [](void * user_ptr, const ReflectionChangeNotification & change)
    {
      CallbackData * cb = (CallbackData *)user_ptr;
      cb->m_DataStore->HandleDataObjectChange(cb->m_Key, change);
    };

    SetNotifyCallback(*obj_data.m_ActiveObject.get(), data_obj_callback, obj_data.m_CallbackData.get());

    if (obj_data.m_State == kLocked || obj_data.m_State == kActive)
    {
      return;
    }

    if (obj_data.m_State != kCreating)
    {
      DDSLog::LogError("Incosistent object state");
      return;
    }

    obj_data.m_State = kActive;

    TryProcessAllMessages(key, obj_data);

    for (auto & sub : obj_data.m_Subscriptions)
    {
      if (sub.m_IsDataSubscription == false)
      {
        DDSResponderCallData responder_call;
        DDSCreateInitialSubscriptionResponse(*obj_data.m_ActiveObject.get(), sub, responder_call);

        m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ sub.m_ResponderObjectType, sub.m_ResponderKey },
          DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(responder_call));
      }
    }
  }

  bool TryProcessMessage(DDSKey key, ObjectData & obj_data, DDSServerToServerMessageType message_type, const char * msg)
  {
    bool requires_full_object = DDSRequiresFullObject(message_type);
    bool requires_active_object = DDSRequiresActiveObject(message_type);

    if (obj_data.m_State == kDatabaseOnly && requires_full_object)
    {
      DDSLog::LogInfo("- Promoting Object");
      PromoteObject(key);
    }
    else if (obj_data.m_State == kDeleted)
    {
      DDSLog::LogInfo("- Reloading Object");
      ReloadObjectByKey(key, obj_data);
    }

    if (obj_data.m_State == kActive || 
      (obj_data.m_State == kCreating && requires_active_object == false) || 
      (obj_data.m_State != kLoading && requires_full_object == false) ||
      (message_type == DDSServerToServerMessageType::kUnlockObject))
    {
      DDSLog::LogVerbose("- Message processed - (obj_state: %d) %s", (int)obj_data.m_State, msg);

      ProcessMessage(key, obj_data, message_type, msg);
      return true;
    }

    DDSLog::LogVerbose("- Queueing message (obj_state: %d) %s", (int)obj_data.m_State, msg);
    return false;
  }

  void TryProcessAllMessages(DDSKey key, ObjectData & obj_data)
  {
    if (m_Processing)
    {
      return;
    }

    m_Processing = true;
    m_NodeState.BeginQueueingMessages();

    std::vector<DDSExportedMessage> remaining_messages;
    for (auto & msg : obj_data.m_PendingMessages)
    {
      if (TryProcessMessage(key, obj_data, msg.m_Type, msg.m_Message.c_str()) == false)
      {
        remaining_messages.emplace_back(std::move(msg));
      }
    }

    obj_data.m_PendingMessages = remaining_messages;
    m_Processing = false;
    m_NodeState.EndQueueingMessages();
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

        if (obj_data.m_ActiveObject)
        {
          DDSNodeInterface node_interface(m_NodeState, this, key);
          if (DDSDataObjectHandleMessage(*obj_data.m_ActiveObject.get(), node_interface, targeted_msg) == false)
          {
            DDSLog::LogError("Failed to process message for object");
          }
        }
        EndObjectModification();
      }
      break;
      case DDSServerToServerMessageType::kTargetedMessageResponder:
      {
        BeginObjectModification(key);
        DDSTargetedMessageWithResponder targeted_msg;
        StormReflParseJson(targeted_msg, message);

        if (obj_data.m_ActiveObject)
        {
          DDSNodeInterface node_interface(m_NodeState, this, key);
          if (DDSDataObjectHandleMessage(*obj_data.m_ActiveObject.get(), node_interface, targeted_msg) == false)
          {
            DDSLog::LogError("Failed to process message for object");
          }
        }
        else
        {
          if (targeted_msg.m_ErrorMethodId != -1)
          {
            DDSResponderCallData responder_call;
            responder_call.m_Key = targeted_msg.m_ResponderKey;
            responder_call.m_MethodArgs = "[]";
            responder_call.m_MethodId = targeted_msg.m_ErrorMethodId;
            responder_call.m_ObjectType = targeted_msg.m_ResponderObjectType;
            responder_call.m_ResponderArgs = targeted_msg.m_ReturnArg;

            m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ targeted_msg.m_ResponderObjectType, targeted_msg.m_ResponderKey },
              DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(responder_call));
          }
        }
        EndObjectModification();
      }
      break;
      case DDSServerToServerMessageType::kResponderCall:
      {
        BeginObjectModification(key);
        DDSResponderCallData responder_call;
        if (StormReflParseJson(responder_call, message) == false)
        {
          DDSLog::LogError("Invalid responder call data");
        }

        if (obj_data.m_ActiveObject)
        {
          DDSNodeInterface node_interface(m_NodeState, this, key);
          if (DDSDataObjectHandleMessage(*obj_data.m_ActiveObject.get(), node_interface, responder_call) == false)
          {
            DDSLog::LogError("Failed to process message for object");
          }
        }

        EndObjectModification();
      }
      break;
      case DDSServerToServerMessageType::kCreateSubscription:
      {
        DDSCreateSubscription sub_msg;
        StormReflParseJson(sub_msg, message);

        auto & obj_data = m_Objects.at(sub_msg.m_Key);

        BeginObjectModification(key);

        DDSExportedSubscription sub_data;
        sub_data.m_DataPath = std::move(sub_msg.m_DataPath);
        sub_data.m_SubscriptionId = sub_msg.m_SubscriptionId;
        sub_data.m_ResponderKey = sub_msg.m_ResponderKey;
        sub_data.m_ResponderObjectType = sub_msg.m_ResponderObjectType;
        sub_data.m_ResponderMethodId = sub_msg.m_ResponderMethodId;
        sub_data.m_ErrorMethodId = sub_msg.m_ErrorMethodId;
        sub_data.m_ResponderArgs = std::move(sub_msg.m_ReturnArg);
        sub_data.m_IsDataSubscription = sub_msg.m_DataSubscription;
        sub_data.m_ForceLoad = sub_msg.m_ForceLoad;
        sub_data.m_DeltaOnly = sub_msg.m_DeltaOnly;
        sub_data.m_State = kSubUnsent;
        obj_data.m_Subscriptions.emplace_back(std::move(sub_data));

        auto & sub = obj_data.m_Subscriptions.back();

        bool send_responder = true;

        DDSResponderCallData responder_call;
        if (obj_data.m_State == kDeleted)
        {
          if (DDSCreateErrorSubscriptionResponse(sub, responder_call) == false)
          {
            send_responder = false;
          }
        }
        else if (sub.m_IsDataSubscription)
        {
          if (obj_data.m_DatabaseObject.get() == nullptr)
          {
            if (sub_data.m_ForceLoad == false)
            {
              if (DDSCreateErrorSubscriptionResponse(sub, responder_call) == false)
              {
                send_responder = false;
              }
            }
          }
          else if (DDSCreateInitialSubscriptionResponse(*obj_data.m_DatabaseObject.get(), sub, responder_call) == false)
          {
            DDSLog::LogError("Could not create initial subscription response");
          }
        }
        else
        {
          if (obj_data.m_State != kActive)
          {
            if (obj_data.m_State == kDatabaseOnly)
            {
              if (sub.m_ForceLoad == false)
              {
                if (DDSCreateErrorSubscriptionResponse(sub, responder_call) == false)
                {
                  send_responder = false;
                }
              }
              else
              {
                PromoteObject(sub_msg.m_Key);
                send_responder = false;
              }
            }
            else
            {
              send_responder = false;
            }
          }
          else if (DDSCreateInitialSubscriptionResponse(*obj_data.m_ActiveObject.get(), sub, responder_call) == false)
          {
            DDSLog::LogError("Could not create initial subscription response");
          }
        }

        if (send_responder)
        {
          m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ sub_msg.m_ResponderObjectType, sub_msg.m_ResponderKey },
            DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(responder_call));
        }

        EndObjectModification();
      }
      break;
      case DDSServerToServerMessageType::kDestroySubscription:
      {
        DDSDestroySubscription sub_msg;
        StormReflParseJson(sub_msg, message);

        bool found_sub = false;

        auto & obj_data = m_Objects.at(sub_msg.m_Key);
        for (auto sub_itr = obj_data.m_Subscriptions.begin(); sub_itr != obj_data.m_Subscriptions.end(); ++sub_itr)
        {
          if (sub_itr->m_SubscriptionId == sub_msg.m_SubscriptionId)
          {
            DDSLog::LogVerbose("Destroying subscription");
            obj_data.m_Subscriptions.erase(sub_itr);
            found_sub = true;
            break;
          }
        }

        if (found_sub == false)
        {
          DDSLog::LogError("Could not find subscription to destroy");
        }
      }
      break;
      case DDSServerToServerMessageType::kSubscriptionDeleted:
      {
        DDSSubscriptionDeleted sub_msg;
        StormReflParseJson(sub_msg, message);

        auto & obj_data = m_Objects.at(sub_msg.m_Key);
        for (auto sub_itr = obj_data.m_RequestedSubscriptions.begin(); sub_itr != obj_data.m_RequestedSubscriptions.end(); ++sub_itr)
        {
          if (sub_itr->m_SubscriptionId == sub_msg.m_SubscriptionId)
          {
            DDSLog::LogVerbose("Destroying requested subscription");
            obj_data.m_RequestedSubscriptions.erase(sub_itr);
            break;
          }
        }
      }
      break;
      case DDSServerToServerMessageType::kCreateSharedLocalCopySubscription:
      {
        DDSCreateSharedLocalCopySubscription sub_msg;
        StormReflParseJson(sub_msg, message);

        DDSAggregateSubscription * agg_sub = nullptr;

        auto & obj_data = m_Objects.at(sub_msg.m_Key);
        for (auto & sub : obj_data.m_AggregateSubscriptions)
        {
          if (sub.GetSharedLocalCopyKey() == sub_msg.m_SharedLocalCopyKey)
          {
            agg_sub = &sub;
            break;
          }
        }

        if (agg_sub == nullptr)
        {
          if (sub_msg.m_DataSubscription)
          {
            obj_data.m_AggregateSubscriptions.emplace_back(m_NodeState, sub_msg.m_DataPath, sub_msg.m_SharedLocalCopyKey,
              obj_data.m_DatabaseDataGen, sub_msg.m_DataSubscription, obj_data.m_DatabaseObject.get(), 
              &DDSDataObjectStore<DataType, DatabaseBackedType>::GetDatabaseDataAtPath);
          }
          else
          {
            obj_data.m_AggregateSubscriptions.emplace_back(m_NodeState, sub_msg.m_DataPath, sub_msg.m_SharedLocalCopyKey,
              obj_data.m_ObjectDataGen, sub_msg.m_DataSubscription, obj_data.m_ActiveObject.get(), 
              &DDSDataObjectStore<DataType, DatabaseBackedType>::GetObjectDataAtPath);
          }

          agg_sub = &obj_data.m_AggregateSubscriptions.back();
        }

        agg_sub->CreateSubscription(sub_msg.m_ReturnNode, sub_msg.m_SubscriptionId, sub_msg.m_DataGen);
      }
      break;
      case DDSServerToServerMessageType::kDestroySharedLocalCopySubscription:
      {
        DDSDestroySharedLocalCopySubscription sub_msg;
        StormReflParseJson(sub_msg, message);

        auto & obj_data = m_Objects.at(sub_msg.m_Key);

        for (std::size_t index = 0; index < obj_data.m_AggregateSubscriptions.size(); index++)
        {
          if (obj_data.m_AggregateSubscriptions[index].GetSharedLocalCopyKey() == sub_msg.m_SharedLocalCopyKey)
          {
            obj_data.m_AggregateSubscriptions[index].DestroySubscription(sub_msg.m_SubscriptionId);

            if (obj_data.m_AggregateSubscriptions[index].HasSubscriptions() == false)
            {
              vremove_index_quick(obj_data.m_AggregateSubscriptions, index);
            }
            break;
          }
        }
      }
      break;
      case DDSServerToServerMessageType::kSharedLocalCopyAck:
      {
        DDSSharedLocalCopyAck sub_msg;
        StormReflParseJson(sub_msg, message);

        auto & obj_data = m_Objects.at(sub_msg.m_Key);

        for (std::size_t index = 0; index < obj_data.m_AggregateSubscriptions.size(); index++)
        {
          if (obj_data.m_AggregateSubscriptions[index].GetSharedLocalCopyKey() == sub_msg.m_SharedLocalCopy)
          {
            obj_data.m_AggregateSubscriptions[index].HandleAck(sub_msg.m_NodeId, sub_msg.m_SubscriptionId, sub_msg.m_DataGen, sub_msg.m_RoutingTableGen);
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

  void HandleDataObjectChange(DDSKey key, const ReflectionChangeNotification & change)
  {   
    if (m_Modifying == false)
    {
      DDSLog::LogError("Invalid modification");
    }

    m_Changes.emplace_back(std::make_tuple(key, false, change));
  }

  void HandleDatabaseObjectChange(DDSKey key, const ReflectionChangeNotification & change)
  {
    if (m_Modifying == false)
    {
      DDSLog::LogError("Invalid modification");
    }

    m_Changes.emplace_back(std::make_tuple(key, true, change));
  }

  virtual void BeginObjectModification(DDSKey key)
  {
    if (m_Modifying)
    {
      DDSLog::LogError("Double modifying in data object store");
    }

    m_Modifying = true;
    m_NodeState.BeginQueueingMessages();
  }

  virtual void EndObjectModification()
  {
    auto changes = std::move(m_Changes);
    auto dead_keys = std::move(m_DeadObjects);
    auto promoted_objects = std::move(m_PromotedObjects);
    auto finalized_objects = std::move(m_FinalizedObjects);

    for (auto & change_data : changes)
    {
      DDSKey key = std::get<DDSKey>(change_data);
      bool database_changed = std::get<bool>(change_data);
      auto & change = std::get<ReflectionChangeNotification>(change_data);

      auto itr = m_Objects.find(key);
      if (itr == m_Objects.end())
      {
        DDSLog::LogError("Could not find object");
      }

      auto & obj_data = itr->second;

      if (database_changed)
      {
        obj_data.m_DatabaseDataGen++;
        for (auto & sub : obj_data.m_Subscriptions)
        {
          if (sub.m_IsDataSubscription && StormDataMatchPathPartial(change.m_Path.data(), sub.m_DataPath.data()))
          {
            DDSSendChangeSubscription(change, sub, obj_data.m_DatabaseObject.get(), m_NodeState);
          }
        }

        for (auto & sub : obj_data.m_AggregateSubscriptions)
        {
          if (sub.IsDataSubscription() && StormDataMatchPathPartial(change.m_Path.data(), sub.GetDataPath().data()))
          {
            sub.HandleChangePacket(change, obj_data.m_DatabaseDataGen);
          }
        }

        std::string database_obj = StormReflEncodeJson(*obj_data.m_DatabaseObject.get());
        m_NodeState.UpdateObjectData(m_ObjectTypeId, key, DatabaseBackedType::Collection(), database_obj.data(), nullptr);
      }
      else
      {
        obj_data.m_ObjectDataGen++;
        for (auto & sub : obj_data.m_Subscriptions)
        {
          if (sub.m_IsDataSubscription == false && sub.m_State == kSubSentValid && StormDataMatchPathPartial(change.m_Path.data(), sub.m_DataPath.data()))
          {
            DDSSendChangeSubscription(change, sub, obj_data.m_ActiveObject.get(), m_NodeState);
          }
        }

        for (auto & sub : obj_data.m_AggregateSubscriptions)
        {
          if (sub.IsDataSubscription() == false && StormDataMatchPathPartial(change.m_Path.data(), sub.GetDataPath().data()))
          {
            sub.HandleChangePacket(change, obj_data.m_ObjectDataGen);
          }
        }
      }
    }

    m_Modifying = false;

    for (auto & key : finalized_objects)
    {
      auto itr = m_Objects.find(key);
      if (itr == m_Objects.end())
      {
        continue;
      }

      FinalizeObjectLoad(key);
    }

    for (auto & key : promoted_objects)
    {
      auto itr = m_Objects.find(key);
      if (itr == m_Objects.end())
      {
        continue;
      }

      PromoteObject(key);
    }

    m_NodeState.EndQueueingMessages();

    for (auto & key : dead_keys)
    {
      Destroy(key);
    }
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

  void AssignRequestedAggregateSubscription(DDSKey key, const DDSExportedAggregateRequestedSubscription & requested_sub)
  {
    auto itr = m_Objects.find(key);
    if (itr == m_Objects.end())
    {
      return;
    }

    itr->second.m_RequestedAggregateSubscriptions.emplace_back(requested_sub);
  }

  void RemoveRequestedAggregateSubscription(DDSKey key, DDSKey shared_local_copy_key, DDSKey subscription_id)
  {
    auto itr = m_Objects.find(key);
    if (itr == m_Objects.end())
    {
      return;
    }

    for (auto sub_itr = itr->second.m_RequestedAggregateSubscriptions.begin(); sub_itr != itr->second.m_RequestedAggregateSubscriptions.end(); ++sub_itr)
    {
      if (sub_itr->m_SubscriptionId == subscription_id && sub_itr->m_SharedLocalCopyKey == shared_local_copy_key)
      {
        itr->second.m_RequestedAggregateSubscriptions.erase(sub_itr);
        return;
      }
    }
  }

  void HandleAllClear(int routing_table_gen)
  {
    for (auto & obj : m_Objects)
    {
      for (auto & sub : obj.second.m_AggregateSubscriptions)
      {
        sub.GotAllClear(routing_table_gen);
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
    if (start_itr == m_Objects.end())
    {
      start_itr = m_Objects.begin();
    }

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
    if (start_itr == m_Objects.end())
    {
      start_itr = m_Objects.begin();
    }

    auto itr = start_itr;

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
        obj.m_ObjectDataGen = itr->second.m_ObjectDataGen;
        obj.m_DatabaseDataGen = itr->second.m_DatabaseDataGen;

        g_ExportObjectsAsFull = false;

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

        g_ExportObjectsAsFull = true;

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

        for (auto & sub : itr->second.m_AggregateSubscriptions)
        {
          DDSExportedAggregateSubscription sub_info;
          sub.Export(sub_info);
          
          obj.m_AggregateSubscriptions.emplace_back(std::move(sub_info));
        }

        for (auto & req_sub : itr->second.m_RequestedAggregateSubscriptions)
        {
          m_NodeState.m_SharedLocalCopyDatabase.GetSubscriptionInfo(req_sub);
          obj.m_RequestedAggregateSubscriptions.emplace_back(std::move(req_sub));

          m_NodeState.m_SharedLocalCopyDatabase.DestroySharedLocalCopySubscription(req_sub.m_SharedLocalCopyKey, req_sub.m_SubscriptionId);
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

  void ProcessExportedObjects(std::vector<DDSExportedObject> & object_list, int routing_table_gen)
  {
    for (auto & object : object_list)
    {
      ObjectData obj_data = { };

      obj_data.m_PendingMessages = std::move(object.m_PendingMessages);
      obj_data.m_Subscriptions = std::move(object.m_Subscriptions);
      obj_data.m_RequestedSubscriptions = std::move(object.m_RequestedSubscriptions);
      obj_data.m_RequestedAggregateSubscriptions = std::move(object.m_RequestedAggregateSubscriptions);

      DDSDataObjectAddress obj_addr = { m_ObjectTypeId, object.m_Key };

      for (auto & req_sub : obj_data.m_RequestedAggregateSubscriptions)
      {
        m_NodeState.m_SharedLocalCopyDatabase.CreateExistingSharedLocalCopySubscription(req_sub, obj_addr);
      }

      obj_data.m_ObjectDataGen = object.m_ObjectDataGen;
      obj_data.m_DatabaseDataGen = object.m_DatabaseDataGen;

      if (object.m_DatabaseObject.size() > 0)
      {
        obj_data.m_DatabaseObject = std::make_unique<DatabaseBackedType>();
        if (StormReflParseJson(*obj_data.m_DatabaseObject.get(), object.m_DatabaseObject.c_str()) == false)
        {
          DDSLog::LogError("Could not properly parse external sync message");
          continue;
        }

        DDSLog::LogVerbose("Processing incoming db object:\n%s", StormReflEncodePrettyJson(*obj_data.m_DatabaseObject.get()).data());

        if (object.m_ActiveObject.size() > 0)
        {
          DDSNodeInterface node_interface(m_NodeState, this, object.m_Key);
          obj_data.m_ActiveObject = std::make_unique<DataType>(node_interface, *obj_data.m_DatabaseObject.get());
          if (StormReflParseJson(*obj_data.m_ActiveObject.get(), object.m_ActiveObject.c_str()) == false)
          {
            DDSLog::LogError("Could not properly parse external sync message");
            return;
          }

          DDSLog::LogVerbose("Processing incoming data objtect:\n%s", StormReflEncodePrettyJson(*obj_data.m_ActiveObject.get()).data());

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

          m_NodeState.ImportSharedSubscriptions(DDSDataObjectAddress{ m_ObjectTypeId, object.m_Key }, object.m_SharedSubscriptions, routing_table_gen);
          m_Objects.emplace(std::make_pair(object.m_Key, std::move(obj_data)));
        }
        else
        {
          obj_data.m_State = kDatabaseOnly;
          m_Objects.emplace(std::make_pair(object.m_Key, std::move(obj_data)));
        }
      }
      else
      {
        obj_data.m_State = kDeleted;
        auto result = m_Objects.emplace(std::make_pair(object.m_Key, std::move(obj_data)));
      }

      for (auto & sub : object.m_AggregateSubscriptions)
      {
        if (sub.m_DataSubscription)
        {
          obj_data.m_AggregateSubscriptions.emplace_back(m_NodeState, sub, obj_data.m_DatabaseDataGen, obj_data.m_DatabaseObject.get(),
            &DDSDataObjectStore<DataType, DatabaseBackedType>::GetDatabaseDataAtPath);
        }
        else
        {
          obj_data.m_AggregateSubscriptions.emplace_back(m_NodeState, sub, obj_data.m_ObjectDataGen, obj_data.m_ActiveObject.get(),
            &DDSDataObjectStore<DataType, DatabaseBackedType>::GetObjectDataAtPath);
        }
      }
    }
  }

private:

  DDSNodeState & m_NodeState;
  std::string m_Collection;
  int m_ObjectTypeId;

  bool m_Modifying;
  bool m_Processing;

  std::map<DDSKey, ObjectData> m_Objects;
  std::vector<std::tuple<DDSKey, bool, ReflectionChangeNotification>> m_Changes;
  std::vector<DDSKey> m_DeadObjects;
  std::vector<DDSKey> m_PromotedObjects;
  std::vector<DDSKey> m_FinalizedObjects;
};
