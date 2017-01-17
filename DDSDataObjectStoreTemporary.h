#pragma once

#include "DDSDataObjectStore.h"

template <class DataType>
class DDSDataObjectStore<DataType, void> : public DDSDataObjectStoreBase
{
  struct CallbackData
  {
    DDSKey m_Key;
    DDSDataObjectStore<DataType, void> * m_DataStore;
  };

  struct ObjectData
  {
    bool m_Active;
    std::unique_ptr<DataType> m_ActiveObject;
    std::unique_ptr<CallbackData> m_CallbackData;
    std::vector<DDSExportedMessage> m_PendingMessages;
    std::vector<DDSExportedSubscription> m_Subscriptions;
    std::vector<DDSExportedRequestedSubscription> m_RequestedSubscriptions;
  };

public:

  DDSDataObjectStore(DDSNodeState & node_state, int object_type_id) :
    m_NodeState(node_state), m_ObjectTypeId(object_type_id), m_Modifying(false)
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

  int GetDataTypeId() const
  {
    return m_ObjectTypeId;
  }

  ObjectData & CreateObject(DDSKey key)
  {
    DDSNodeInterface node_interface(m_NodeState, this, key);
    auto itr = m_Objects.emplace(std::make_pair(key, ObjectData{ false, std::make_unique<DataType>(node_interface) }));
    auto & obj_data = itr.first->second;

    obj_data.m_ActiveObject = std::make_unique<DataType>(node_interface);
    InitializeParentInfo(*obj_data.m_ActiveObject.get());

    obj_data.m_CallbackData = std::make_unique<CallbackData>();
    obj_data.m_CallbackData->m_Key = key;
    obj_data.m_CallbackData->m_DataStore = this;

    auto data_obj_callback = [](void * user_ptr, const ReflectionChangeNotification & change)
    {
      CallbackData * cb = (CallbackData *)user_ptr;
      cb->m_DataStore->HandleDataObjectChange(cb->m_Key, change);
    };

    SetNotifyCallback(*obj_data.m_ActiveObject.get(), data_obj_callback, obj_data.m_CallbackData.get());


    if (DDS_CALL_FUNC(BeginLoad, *obj_data.m_ActiveObject.get()) == false)
    {
      FinalizeObjectLoad(key);
    }

    return obj_data;
  }

  void SpawnNewNonDatabaseBackedType(DDSKey key)
  {
    CreateObject(key);
  }

  void FinalizeObjectLoad(DDSKey key)
  {
    if (m_Modifying)
    {
      m_FinalizedObjects.push_back(key);
      return;
    }

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

  bool Destroy(DDSKey key)
  {
    DestroyObject(key);
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

  void DestroyObject(DDSKey key)
  {
    if (m_Modifying == false)
    {
      auto itr = m_Objects.find(key);

      if (itr != m_Objects.end())
      {
        BeginObjectModification(key);
        auto & obj_data = itr->second;

        DDS_CALL_FUNC(PreDestroy, *obj_data.m_ActiveObject.get());

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

          DDSSubscriptionDeleted deleted_msg;
          DDSCreateDeletedSubscriptionResponse(sub, deleted_msg);

          m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ deleted_msg.m_ObjectType, deleted_msg.m_Key },
            DDSServerToServerMessageType::kSubscriptionDeleted, StormReflEncodeJson(deleted_msg));
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

        m_Objects.erase(itr);
        EndObjectModification();
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
      if (DataType::AllowsImplicitCreate() == false)
      {
        if (message_type == DDSServerToServerMessageType::kTargetedMessageResponder)
        {
          DDSTargetedMessageWithResponder targeted_msg;
          StormReflParseJson(targeted_msg, msg);

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
        return;
      }

      auto & obj_data = CreateObject(key);
      TryProcessMessage(key, obj_data, message_type, msg);
    }
    else
    {
      auto & obj_data = itr->second;
      TryProcessMessage(key, obj_data, message_type, msg);
    }
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
    case DDSServerToServerMessageType::kCreateSubscription:
    {

      DDSCreateSubscription sub_msg;
      StormReflParseJson(sub_msg, message);

      auto itr = m_Objects.find(sub_msg.m_Key);
      if (itr == m_Objects.end())
      {
        return;
      }

      if (sub_msg.m_DataSubscription)
      {
        DDSLog::LogError("Can't subscript to data object for non database type");
      }

      m_NodeState.BeginQueueingMessages();
      auto & obj_data = itr->second;

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
      if (obj_data.m_Active)
      {
        if (DDSCreateInitialSubscriptionResponse(*obj_data.m_ActiveObject.get(), sub, responder_call) == false)
        {
          DDSLog::LogError("Could not create initial subscription response");
        }
      }
      else if (sub_data.m_ForceLoad == false)
      {
        if (DDSCreateErrorSubscriptionResponse(sub, responder_call) == false)
        {
          send_responder = false;
        }
      }

      if (send_responder)
      {
        m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ sub_msg.m_ResponderObjectType, sub_msg.m_ResponderKey },
          DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(responder_call));
      }

      m_NodeState.EndQueueingMessages();
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

      bool found_sub = false;

      auto & obj_data = itr->second;
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

    m_Changes.emplace_back(std::make_pair(key, change));
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
    std::vector<std::pair<DDSKey, ReflectionChangeNotification>> changes = std::move(m_Changes);
    std::vector<DDSKey> dead_keys = std::move(m_DeadObjects);
    std::vector<DDSKey> finalized_objects = std::move(m_FinalizedObjects);

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
        if (sub.m_State == kSubSentValid && StormDataMatchPathPartial(change.m_Path.data(), sub.m_DataPath.data()))
        {
          DDSSendChangeSubscription(change, sub, obj_data.m_ActiveObject.get(), m_NodeState);
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

    m_NodeState.EndQueueingMessages();

    for (auto & key : dead_keys)
    {
      Destroy(key);
    }
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
    if (start_itr == m_Objects.end())
    {
      start_itr = m_Objects.begin();
    }

    auto itr = start_itr;

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

  void ProcessExportedObjects(std::vector<DDSExportedObject> & object_list, int routing_table_gen)
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

      DDSLog::LogVerbose("Processing incoming temporary objtect:\n%s", StormReflEncodePrettyJson(*obj_data.m_ActiveObject.get()).data());

      obj_data.m_PendingMessages = std::move(object.m_PendingMessages);
      obj_data.m_Subscriptions = std::move(object.m_Subscriptions);
      obj_data.m_RequestedSubscriptions = std::move(object.m_RequestedSubscriptions);

      m_NodeState.ImportSharedSubscriptions(DDSDataObjectAddress{ m_ObjectTypeId, object.m_Key }, object.m_SharedSubscriptions, routing_table_gen);

      DDS_CALL_FUNC(MoveObject, *obj_data.m_ActiveObject.get());

      m_Objects.emplace(std::make_pair(object.m_Key, std::move(obj_data)));
    }
  }

private:

  DDSNodeState & m_NodeState;
  std::string m_Collection;
  int m_ObjectTypeId;

  bool m_Modifying;

  std::map<DDSKey, ObjectData> m_Objects;
  std::vector<std::pair<DDSKey, ReflectionChangeNotification>> m_Changes;
  int m_ChangeQueueDepth;

  std::vector<DDSKey> m_DeadObjects;
  std::vector<DDSKey> m_FinalizedObjects;
};


