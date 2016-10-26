#pragma once

#include <memory>

#include "DDSNodeState.h"
#include "DDSCoordinatorState.h"
#include "DDSDataObjectStoreHelpers.h"
#include "DDSSharedObjectBase.h"
#include "DDSSharedObjectInterface.h"

#include "DDSServerToServerMessages.refl.meta.h"
#include "DDSCoordinatorProtocolMessages.refl.meta.h"

#include <StormData/StormDataChangePacket.h>
#include <StormData/StormDataParent.h>

template <typename DataType>
class DDSSharedObject : public DDSSharedObjectBase
{
public:
  DDSSharedObject(DDSCoordinatorState & coordinator_state, int shared_object_type) :
    m_Coordinator(coordinator_state), 
    m_DataObject(std::make_unique<DataType>(DDSSharedObjectInterface(coordinator_state, this))), 
    m_SharedObjectType(shared_object_type)
  {
    InitializeParentInfo(*m_DataObject.get());
  }

  uint32_t GetObjectClassNameHash() override
  {
    return StormReflTypeInfo<DataType>::GetNameHash();
  }

  int GetObjectTypeId() override
  {
    return m_SharedObjectType;
  }

  virtual void BeginObjectModification()
  {
    ReflectionPushNotifyCallback([&](const ReflectionChangeNotification & change) { m_Changes.emplace_back(change); });
    m_Coordinator.BeginQueueingMessages();
  }

  virtual void EndObjectModification()
  {
    ReflectionPopNotifyCallback();

    std::vector<ReflectionChangeNotification> changes = std::move(m_Changes);

    if (changes.size() > 0)
    {
      DDSCoordinatorSharedObjectDelta delta;
      delta.m_SharedObjectType = m_SharedObjectType;

      for (auto & change_data : changes)
      {
        delta.m_Deltas.emplace_back(DDSCoordinatorSharedObjectDeltaMessage{ change_data.m_Type, change_data.m_Path, change_data.m_SubIndex, change_data.m_Data });
      }

      m_Coordinator.SendToAllConnectedClients(DDSGetServerMessage(delta));
    }

    m_Coordinator.EndQueueingMessages();
  }

  void ProcessMessage(DDSCoordinatorProtocolMessageType message_type, const char * message) override
  {
    switch (message_type)
    {
      case DDSCoordinatorProtocolMessageType::kTargetedMessage:
      {
        BeginObjectModification();
        DDSTargetedMessage targeted_msg;
        StormReflParseJson(targeted_msg, message);

        DDSSharedObjectInterface obj_interface(m_Coordinator, this);
        if (DDSDataObjectHandleMessage(*m_DataObject.get(), obj_interface, targeted_msg) == false)
        {
          DDSLog::LogError("Failed to process message for object");
        }
        EndObjectModification();
      }
      break;
      case DDSCoordinatorProtocolMessageType::kTargetedMessageResponder:
      {
        BeginObjectModification();
        DDSTargetedMessageWithResponder targeted_msg;
        StormReflParseJson(targeted_msg, message);

        DDSSharedObjectInterface obj_interface(m_Coordinator, this);
        if (DDSDataObjectHandleMessage(*m_DataObject.get(), obj_interface, targeted_msg) == false)
        {
          DDSLog::LogError("Failed to process message for object");
        }
        EndObjectModification();
      }
      break;
      case DDSCoordinatorProtocolMessageType::kResponderCall:
      {
        BeginObjectModification();
        DDSResponderCallData responder_call;
        StormReflParseJson(responder_call, message);

        DDSSharedObjectInterface obj_interface(m_Coordinator, this);
        if (DDSDataObjectHandleMessage(*m_DataObject.get(), obj_interface, responder_call) == false)
        {
          DDSLog::LogError("Failed to process message for object");
        }
        EndObjectModification();
      }
      break;
      case DDSCoordinatorProtocolMessageType::kCreateSubscription:
      {
        DDSCoordinatorCreateSubscription sub_msg;
        StormReflParseJson(sub_msg, message);

        DDSExportedSubscription sub_data;
        sub_data.m_DataPath = std::move(sub_msg.m_DataPath);
        sub_data.m_SubscriptionId = sub_msg.m_SubscriptionId;
        sub_data.m_ResponderKey = sub_msg.m_ResponderKey;
        sub_data.m_ResponderObjectType = sub_msg.m_ResponderObjectType;
        sub_data.m_ResponderMethodId = sub_msg.m_ResponderMethodId;
        sub_data.m_ResponderArgs = std::move(sub_msg.m_ReturnArg);
        sub_data.m_IsDataSubscription = (message_type == DDSCoordinatorProtocolMessageType::kCreateDataSubscription);
        sub_data.m_DeltaOnly = sub_msg.m_DeltaOnly;
        m_Subscriptions.emplace_back(std::move(sub_data));

        DDSResponderCallData responder_call;
        if (sub_data.m_IsDataSubscription)
        {
          DDSLog::LogError("Could not create data subscription on shared object");
        }
        else
        {
          if (DDSCreateInitialSubscriptionResponse(*m_DataObject.get(), sub_data, responder_call) == false)
          {
            DDSLog::LogError("Could not create initial subscription response");
          }
        }

        m_Coordinator.SendTargetedMessage(DDSDataObjectAddress{ sub_msg.m_ResponderObjectType, sub_msg.m_ResponderKey },
          DDSCoordinatorProtocolMessageType::kResponderCall, StormReflEncodeJson(responder_call));
      }
      break;
      case DDSCoordinatorProtocolMessageType::kDestroySubscription:
      {
        DDSDestroySubscription sub_msg;
        StormReflParseJson(sub_msg, message);

        for (auto sub_itr = m_RequestedSubscriptions.begin(); sub_itr != m_RequestedSubscriptions.end(); ++sub_itr)
        {
          if (sub_itr->m_SubscriptionId == sub_msg.m_SubscriptionId)
          {
            m_RequestedSubscriptions.erase(sub_itr);
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

  void AssignRequestedSubscription(const DDSExportedRequestedSubscription & requested_sub) override
  {
    m_RequestedSubscriptions.emplace_back(requested_sub);
  }

  void RemoveRequestedSubscription(DDSKey subscription_id) override
  {
    for (auto sub_itr = m_RequestedSubscriptions.begin(); sub_itr != m_RequestedSubscriptions.end(); ++sub_itr)
    {
      if (sub_itr->m_SubscriptionId == subscription_id)
      {
        m_RequestedSubscriptions.erase(sub_itr);
        return;
      }
    }
  }

private:

  DDSCoordinatorState & m_Coordinator;

  std::unique_ptr<DataType> m_DataObject;

  std::vector<DDSExportedSubscription> m_Subscriptions;
  std::vector<DDSExportedRequestedSubscription> m_RequestedSubscriptions;

  std::vector<ReflectionChangeNotification> m_Changes;

  int m_SharedObjectType;
};

template <typename DataType>
class DDSSharedObjectCopy : public DDSSharedObjectCopyBase
{
public:
  DDSSharedObjectCopy(DDSNodeState & node_state, int shared_object_type_id) :
    m_NodeState(node_state), 
    m_SharedObjectType(shared_object_type_id)
  {

  }

  uint32_t GetObjectClassNameHash() override
  {
    return StormReflTypeInfo<DataType>::GetNameHash();
  }

  int GetObjectTypeId() override
  {
    return m_SharedObjectType;
  }

  void ProcessDelta(const DDSCoordinatorSharedObjectDelta & delta) override
  {
    for (auto & change : delta.m_Deltas)
    {
      ReflectionChangeNotification change_notification;
      change_notification.m_Type = change.m_Type;
      change_notification.m_BaseObject = m_DataObject.get();
      change_notification.m_Data = change.m_Data;
      change_notification.m_SubIndex = change.m_Index;
      change_notification.m_Path = change.m_Path;

      StormDataApplyChangePacket(*m_DataObject.get(), change.m_Type, change.m_Path.data(), change.m_Index, change.m_Data.data());

      for (auto & sub_data : m_Subscriptions)
      {
        for (auto & sub : sub_data.second)
        {
          if (DDSCheckChangeSubscription(change_notification, sub))
          {
            DDSResponderCallData call_data;
            if (DDSCreateSubscriptionResponse(*m_DataObject.get(), change_notification, sub, call_data))
            {
              DDSLog::LogError("Could not serialize subscription change");
            }

            m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ call_data.m_ObjectType, call_data.m_Key }, DDSResponderCallData::Type, StormReflEncodeJson(call_data));
          }
        }
      }
    }
  }

  void CreateSubscription(DDSExportedSubscription && sub_data) override
  {
    DDSDataObjectAddress addr = { sub_data.m_ResponderObjectType, sub_data.m_ResponderKey };
    auto result = m_Subscriptions.emplace(std::make_pair(addr, std::vector<DDSExportedSubscription>{}));

    std::vector<DDSExportedSubscription> & sub_list = result.first->second;
    sub_list.emplace_back(std::move(sub_data));

    DDSResponderCallData responder_call;
    if (sub_data.m_IsDataSubscription)
    {
      DDSLog::LogError("Could not create initial subscription response");
    }
    else
    {
      if (DDSCreateInitialSubscriptionResponse(*m_DataObject.get(), sub_data, responder_call) == false)
      {
        DDSLog::LogError("Could not create initial subscription response");
      }
    }

    m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ sub_data.m_ResponderObjectType, sub_data.m_ResponderKey },
      DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(responder_call));
  }

  void DestroySubscription(DDSDataObjectAddress addr, DDSKey subscription_id) override
  {
    auto itr = m_Subscriptions.find(addr);
    if (itr == m_Subscriptions.end())
    {
      return;
    }

    for (auto sub_itr = itr->second.begin(); sub_itr != itr->second.end(); ++sub_itr)
    {
      if (sub_itr->m_SubscriptionId == subscription_id)
      {
        itr->second.erase(sub_itr);
        return;
      }
    }
  }

  void ExportSubscriptions(DDSDataObjectAddress addr, std::vector<std::pair<int, std::vector<DDSExportedSubscription>>> & exported_list) override
  {
    auto itr = m_Subscriptions.find(addr);
    if (itr == m_Subscriptions.end())
    {
      return;
    }

    exported_list.emplace_back(std::make_pair(m_SharedObjectType, std::move(itr->second)));
    m_Subscriptions.erase(itr);
  }

  void ImportSubscriptions(DDSDataObjectAddress addr, std::vector<DDSExportedSubscription> && subs) override
  {
    m_Subscriptions.emplace(std::make_pair(addr, subs));
  }

private:

  DDSNodeState & m_NodeState;

  std::unique_ptr<DataType> m_DataObject;

  std::map<DDSDataObjectAddress, std::vector<DDSExportedSubscription>> m_Subscriptions;
  int m_SharedObjectType;
};
