#pragma once

#include <memory>

#include "DDSNodeState.h"
#include "DDSCoordinatorState.h"
#include "DDSDataObjectStoreHelpers.h"
#include "DDSSharedObjectBase.h"
#include "DDSSharedObjectInterface.h"
#include "DDSServerMessage.h"

#include "DDSServerToServerMessages.refl.meta.h"
#include "DDSCoordinatorProtocolMessages.refl.meta.h"

#include <StormRefl/StormReflJsonStd.h>
#include <StormData/StormDataChangePacket.h>
#include <StormData/StormDataParent.h>

template <typename DataType>
class DDSSharedObject : public DDSSharedObjectBase
{
public:
  DDSSharedObject(DDSCoordinatorState & coordinator_state, int shared_object_type) :
    m_Interface(coordinator_state, this),
    m_Coordinator(coordinator_state), 
    m_DataObject(std::make_unique<DataType>(m_Interface)),
    m_SharedObjectType(shared_object_type)
  {
    InitializeParentInfo(*m_DataObject.get());

    auto data_obj_callback = [](void * user_ptr, const ReflectionChangeNotification & change)
    {
      DDSSharedObject<DataType> * store = (DDSSharedObject<DataType> *)user_ptr;
      store->HandleDataObjectChange(change);
    };

    SetNotifyCallback(*m_DataObject.get(), data_obj_callback, this);
  }

  uint32_t GetObjectClassNameHash() override
  {
    return StormReflTypeInfo<DataType>::GetNameHash();
  }

  int GetObjectTypeId() override
  {
    return m_SharedObjectType;
  }

  const void * GetSharedObjectPointer() override
  {
    return m_DataObject.get();
  }

  void HandleDataObjectChange(const ReflectionChangeNotification & change)
  {
    m_Changes.emplace_back(change);
  }

  virtual void BeginObjectModification()
  {
    m_Coordinator.BeginQueueingMessages();
  }

  virtual void EndObjectModification()
  {
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
        sub_data.m_ErrorMethodId = sub_msg.m_ErrorMethodId;
        sub_data.m_ResponderArgs = std::move(sub_msg.m_ReturnArg);
        sub_data.m_IsDataSubscription = sub_msg.m_DataSubscription;
        sub_data.m_ForceLoad = sub_msg.m_ForceLoad;
        sub_data.m_DeltaOnly = sub_msg.m_DeltaOnly;
        sub_data.m_State = kSubUnsent;
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
          DDSCoordinatorProtocolMessageType::kResponderCall, DDSGetServerMessage(responder_call));
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

  DDSSharedObjectInterface m_Interface;
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
    m_DataObject(std::make_unique<DataType>(m_Interface)),
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

  const void * GetSharedObjectPointer() override
  {
    return m_DataObject.get();
  }

  void ProcessDelta(const DDSCoordinatorSharedObjectDelta & delta) override
  {
    for (auto & elem : delta.m_Deltas)
    {
      ReflectionChangeNotification change_notification;
      change_notification.m_Type = elem.m_Type;
      change_notification.m_Data = elem.m_Data;
      change_notification.m_SubIndex = elem.m_Index;
      change_notification.m_Path = elem.m_Path;

      StormDataApplyChangePacket(*m_DataObject.get(), elem.m_Type, elem.m_Path.data(), elem.m_Index, elem.m_Data.data());

      for (auto & sub_data : m_Subscriptions)
      {
        ProcessDeltaElem(change_notification, sub_data.second, elem);
      }
    }
  }

  void ProcessDeltaElem(ReflectionChangeNotification & change_notification, std::vector<DDSExportedSubscription> & subs, const DDSCoordinatorSharedObjectDeltaMessage & elem)
  {
    for (auto & sub : subs)
    {
      if (StormDataMatchPathPartial(elem.m_Path.data(), sub.m_DataPath.data()))
      {
        DDSSendChangeSubscription(change_notification, sub, m_DataObject.get(), m_NodeState);
      }
    }
  }

  void CreateSubscription(DDSExportedSubscription && sub_data) override
  {
    DDSDataObjectAddress addr = { sub_data.m_ResponderObjectType, sub_data.m_ResponderKey };
    auto result = m_Subscriptions.emplace(std::make_pair(addr, std::vector<DDSExportedSubscription>{}));

    m_SubscriptionAddrMap.emplace(sub_data.m_SubscriptionId, addr);

    std::vector<DDSExportedSubscription> & sub_list = result.first->second;
    sub_list.emplace_back(std::move(sub_data));

    auto & sub = sub_list.back();

    DDSResponderCallData responder_call;
    if (sub_data.m_IsDataSubscription)
    {
      DDSLog::LogError("Could not create initial subscription response");
    }
    else
    {
      if (DDSCreateInitialSubscriptionResponse(*m_DataObject.get(), sub, responder_call) == false)
      {
        DDSLog::LogError("Could not create initial subscription response");
      }
    }

    m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ sub_data.m_ResponderObjectType, sub_data.m_ResponderKey },
      DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(responder_call));
  }

  void DestroySubscription(DDSDataObjectAddress addr, DDSKey subscription_id) override
  {
    auto addr_itr = m_SubscriptionAddrMap.find(subscription_id);
    if (addr_itr == m_SubscriptionAddrMap.end())
    {
      return;
    }

    auto itr = m_Subscriptions.find(addr_itr->second);
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

    for (auto sub_itr = itr->second.begin(); sub_itr != itr->second.end(); ++sub_itr)
    {
      m_SubscriptionAddrMap.erase(sub_itr->m_SubscriptionId);
    }

    exported_list.emplace_back(std::make_pair(m_SharedObjectType, std::move(itr->second)));
    m_Subscriptions.erase(itr);
  }

  void ImportSubscriptions(DDSDataObjectAddress addr, std::vector<DDSExportedSubscription> && subs, DDSNodeSharedObjectResolver & resolver, int table_gen) override
  {
    m_Subscriptions.emplace(std::make_pair(addr, std::move(subs)));

    for (auto & sub : subs)
    {
      m_SubscriptionAddrMap.emplace(sub.m_SubscriptionId, addr);
    }

    auto change_lists = resolver.GetChangeList(table_gen, addr.m_ObjectKey);

    for (auto change_list : change_lists)
    {
      for (auto delta_list : *change_list)
      {
        for (auto elem : delta_list.m_Deltas)
        {
          ReflectionChangeNotification change_notification;
          change_notification.m_Type = elem.m_Type;
          change_notification.m_Data = elem.m_Data;
          change_notification.m_SubIndex = elem.m_Index;
          change_notification.m_Path = elem.m_Path;

          ProcessDeltaElem(change_notification, subs, elem);
        }
      }
    }
  }

private:

  DDSSharedObjectCopyInterface m_Interface;
  DDSNodeState & m_NodeState;

  std::unique_ptr<DataType> m_DataObject;

  std::map<DDSDataObjectAddress, std::vector<DDSExportedSubscription>> m_Subscriptions;
  std::map<DDSKey, DDSDataObjectAddress> m_SubscriptionAddrMap;
  int m_SharedObjectType;
};
