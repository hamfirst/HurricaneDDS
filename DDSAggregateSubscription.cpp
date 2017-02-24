
#include "DDSAggregateSubscription.h"
#include "DDSNodeState.h"
#include "DDSServerMessage.h"
#include "DDSLog.h"

#include "DDSServerToServerMessages.refl.meta.h"

#include <sb/vector.h>


DDSAggregateSubscription::DDSAggregateSubscription(
  DDSNodeState & node_state, const std::string & data_path, DDSKey shared_local_object_key, bool data_subscription, 
  void * object, bool(*GetDataAtPath)(void * obj, const char * path, std::string & data)) :
  m_NodeState(&node_state),
  m_Object(object),
  m_GetDataAtPath(GetDataAtPath),
  m_SharedLocalCopyKey(shared_local_object_key),
  m_DataGen(0),
  m_DataSubcription(data_subscription),
  m_DataPath(data_path)
{
  std::string data;
  m_Active = object && m_GetDataAtPath(object, data_path.c_str(), data);
}

DDSAggregateSubscription::DDSAggregateSubscription(
  DDSNodeState & node_state, DDSExportedAggregateSubscription & msg,
  void * object, bool(*GetDataAtPath)(void * obj, const char * path, std::string & data)) :
  m_NodeState(&node_state),
  m_Object(object),
  m_GetDataAtPath(GetDataAtPath)
{
  Import(msg);
}

void DDSAggregateSubscription::CreateSubscription(DDSNodeId node_id, DDSKey server_request_id, int data_gen)
{
  m_SubscribedNodes.push_back(std::make_pair(node_id, server_request_id));

  if (m_Active == false)
  {
    DDSSharedLocalCopyHostDestroyed msg;
    msg.m_SharedLocalCopy = m_SharedLocalCopyKey;
    msg.m_SubscriptionId = server_request_id;

    m_NodeState->m_NodeNetwork.SendMessageToServer(node_id,
      DDSServerToServerMessageType::kSharedLocalCopyHostDestroyed, StormReflEncodeJson(msg));
  }
  else
  {
    if (data_gen != 0)
    {
      DDSSharedLocalCopyFastForward msg;
      msg.m_DataGen = m_DataGen;
      msg.m_SharedLocalCopy = m_SharedLocalCopyKey;
      msg.m_SubscriptionId = server_request_id;

      for (auto & change : m_Changes)
      {
        if (change.m_DataGen > data_gen)
        {
          msg.m_Changes.emplace_back(std::make_pair(change.m_DataGen, change.m_Change));
        }
      }

      m_NodeState->m_NodeNetwork.SendMessageToServer(node_id,
        DDSServerToServerMessageType::kSharedLocalCopyFastForward, StormReflEncodeJson(msg));
    }
    else
    {
      DDSSharedLocalCopyInit msg;
      msg.m_SharedLocalCopyKey = m_SharedLocalCopyKey;
      msg.m_SubscriptionId = server_request_id;
      msg.m_DataGen = m_DataGen;
      m_GetDataAtPath(m_Object, m_DataPath.c_str(), msg.m_Data);

      m_NodeState->m_NodeNetwork.SendMessageToServer(node_id,
        DDSServerToServerMessageType::kSharedLocalCopyInit, StormReflEncodeJson(msg));
    }
  }
}

void DDSAggregateSubscription::DestroySubscription(DDSKey server_request_id)
{
  for (auto itr = m_SubscribedNodes.begin(), end = m_SubscribedNodes.end(); itr != end; ++itr)
  {
    if (itr->second == server_request_id)
    {
      m_SubscribedNodes.erase(itr);
      return;
    }
  }
}

bool DDSAggregateSubscription::HasSubscriptions() const
{
  return m_SubscribedNodes.size() > 0;
}

bool DDSAggregateSubscription::IsDataSubscription() const
{
  return m_DataSubcription;
}

DDSKey DDSAggregateSubscription::GetSharedLocalCopyKey() const
{
  return m_SharedLocalCopyKey;
}

const std::string & DDSAggregateSubscription::GetDataPath() const
{
  return m_DataPath;
}

void DDSAggregateSubscription::HandleChangePacket(const ReflectionChangeNotification & change_notification)
{
  m_DataGen++;
  
  if (m_Active == false)
  {
    for (auto & elem : m_SubscribedNodes)
    {
      DDSSharedLocalCopyInit msg;
      msg.m_SharedLocalCopyKey = m_SharedLocalCopyKey;
      msg.m_SubscriptionId = elem.second;
      msg.m_DataGen = m_DataGen;
      m_GetDataAtPath(m_Object, m_DataPath.c_str(), msg.m_Data);

      m_NodeState->m_NodeNetwork.SendMessageToServer(elem.first,
        DDSServerToServerMessageType::kSharedLocalCopyInit, StormReflEncodeJson(msg));
    }

    m_Active = true;
  }
  else
  {
    ReflectionChangeNotification notification_copy = change_notification;
    notification_copy.m_Path = notification_copy.m_Path.substr(m_DataPath.size());

    auto change_packet = StormDataCreateChangePacket(notification_copy);

    DDSSharedLocalCopyChange msg;
    msg.m_Change = change_packet;
    msg.m_DataGen = m_DataGen;
    msg.m_SharedLocalCopy = m_SharedLocalCopyKey;

    DDSExportedAggregateSubscriptionChange change_record;
    change_record.m_Change = change_packet;
    change_record.m_DataGen = m_DataGen;
    change_record.m_WaitForAllClearGen = 0;

    for (auto & elem : m_SubscribedNodes)
    {
      msg.m_SubscriptionId = elem.second;
      m_NodeState->m_NodeNetwork.SendMessageToServer(elem.first, DDSServerToServerMessageType::kSharedLocalCopyChange, StormReflEncodeJson(msg));

      change_record.m_PendingAckNodes.push_back(elem);
    }

    m_Changes.emplace_back(std::move(change_record));
  }
}

void DDSAggregateSubscription::HandleAck(DDSNodeId node_id, DDSKey server_request_id, int data_gen, int routing_table_gen)
{
  auto check_addr = std::make_pair(node_id, server_request_id);

  for (auto & elem : m_Changes)
  {
    if (elem.m_DataGen == data_gen)
    {
      for(std::size_t index = 0; index < elem.m_PendingAckNodes.size(); index++)
      {
        if (elem.m_PendingAckNodes[index] == check_addr)
        {
          if (m_NodeState->m_RoutingTable->m_TableGeneration < routing_table_gen)
          {
            elem.m_WaitForAllClearGen = routing_table_gen;
            m_HasChangesWaiting = true;
          }

          vremove_index_quick(elem.m_PendingAckNodes, index);
          ClearExpiredChanges();
          return;
        }
      }

      DDSLog::LogError("Invalid aggregate subscription ack (invalid server)");
      return;
    }
  }

  DDSLog::LogError("Invalid aggregate subscription ack (invalid change)");
}

void DDSAggregateSubscription::HandleObjectDestroyed()
{
  for (auto & elem : m_SubscribedNodes)
  {
    DDSSharedLocalCopyHostDestroyed msg;
    msg.m_SharedLocalCopy = m_SharedLocalCopyKey;
    msg.m_SubscriptionId = elem.second;

    m_NodeState->m_NodeNetwork.SendMessageToServer(elem.first,
      DDSServerToServerMessageType::kSharedLocalCopyHostDestroyed, StormReflEncodeJson(msg));
  }

  m_Active = false;
}

void DDSAggregateSubscription::GotAllClear(int table_gen)
{
  if (m_HasChangesWaiting == false)
  {
    return;
  }

  for (auto & elem : m_Changes)
  {
    if (elem.m_WaitForAllClearGen < table_gen)
    {
      elem.m_WaitForAllClearGen = 0;
    }
  }

  ClearExpiredChanges();
}

void DDSAggregateSubscription::ClearExpiredChanges()
{
  while (true)
  {
    auto & oldest_change = *m_Changes.begin();
    if (oldest_change.m_PendingAckNodes.size() > 0 || oldest_change.m_WaitForAllClearGen != 0)
    {
      break;
    }

    m_Changes.erase(m_Changes.begin());
    if (m_Changes.size() == 0)
    {
      break;
    }
  }
}

void DDSAggregateSubscription::Export(DDSExportedAggregateSubscription & msg)
{
  msg.m_SharedLocalCopyKey = m_SharedLocalCopyKey;
  msg.m_Changes = std::move(m_Changes);
  msg.m_SubscribedNodes = std::move(m_SubscribedNodes);
  msg.m_HasChangesWaiting = m_HasChangesWaiting;
  msg.m_DataSubscription = m_DataSubcription;
  msg.m_DataPath = m_DataPath;
  msg.m_DataGen = m_DataGen;
}

void DDSAggregateSubscription::Import(DDSExportedAggregateSubscription & msg)
{
  m_SharedLocalCopyKey = msg.m_SharedLocalCopyKey;
  m_Changes = std::move(msg.m_Changes);
  m_SubscribedNodes = std::move(msg.m_SubscribedNodes);
  m_HasChangesWaiting = msg.m_HasChangesWaiting;
  m_DataSubcription = msg.m_DataSubscription;
  m_DataPath = msg.m_DataPath;
  m_DataGen = msg.m_DataGen;
}
