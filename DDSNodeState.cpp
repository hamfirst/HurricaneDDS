
#include "DDSLog.h"
#include "DDSNodeState.h"
#include "DDSRoutingTable.h"

#include "DDSServerToServerMessages.refl.meta.h"

#include <StormRefl\StormReflJsonStd.h>

#include <StormSockets\StormSocketClientFrontendWebsocket.h>
#include <StormSockets\StormSocketServerFrontendWebsocket.h>

DDSNodeState::DDSNodeState(
  int num_data_object_types,
  const StormSockets::StormSocketInitSettings & backend_settings,
  const StormSockets::StormSocketServerFrontendWebsocketSettings & node_server_settings,
  const StormSockets::StormSocketClientFrontendWebsocketSettings & node_client_settings,
  const DDSCoordinatorClientSettings & coordinator_settings) :
  m_Backend(backend_settings),
  m_NodeNetwork(*this, node_server_settings, node_client_settings),
  m_CoordinatorConnection(*this, coordinator_settings),
  m_IncomingKeyspace(num_data_object_types),
  m_OutgoingKeyspace(*this, num_data_object_types)
{
  inet_pton(AF_INET, node_server_settings.ListenSettings.LocalInterface, &m_LocalInterface);
  m_LocalPort = node_server_settings.ListenSettings.Port;

  m_CoordinatorConnection.RequestConnect();
}

void DDSNodeState::ProcessEvents()
{
  m_CoordinatorConnection.ProcessEvents();
  m_NodeNetwork.ProcessEvents();
  m_OutgoingKeyspace.Update();
}

void DDSNodeState::GotInitialCoordinatorSync(DDSNodeId node_id, const DDSRoutingTable & routing_table, bool initial_node, uint64_t server_secret, uint64_t client_secret)
{
  m_LocalNodeId = node_id;
  m_RoutingTable = routing_table;
  GetKeyRanges(m_RoutingTable, m_RoutingKeyRanges);
  m_LocalKeyRange = GetKeyRange(node_id, m_RoutingTable);

  m_ServerSecret = server_secret;
  m_ClientSecret = client_secret;

  if (initial_node)
  {
    m_IncomingKeyspace.InitializeSingleNode();
  }
  else
  {
    m_IncomingKeyspace.InitializeUnsyncedKeyspace(routing_table.m_TableGeneration, m_LocalKeyRange);
  }
}

void DDSNodeState::GotNewRoutingTable(const DDSRoutingTable & routing_table)
{
  DDSKeyRange new_key_range = GetKeyRange(m_LocalNodeId, routing_table);
  m_IncomingKeyspace.ProcessNewRoutingTable(routing_table, m_RoutingTable, new_key_range, m_LocalNodeId);
  m_OutgoingKeyspace.ProcessNewRoutingTable(routing_table, m_LocalKeyRange, m_LocalNodeId);

  m_RoutingTable = routing_table;
  GetKeyRanges(m_RoutingTable, m_RoutingKeyRanges);
  m_LocalKeyRange = new_key_range;
}

void DDSNodeState::GotMessageFromServer(DDSNodeId node_id, DDSServerToServerMessageType type, const char * data)
{
  if (type == DDSServerToServerMessageType::kDataObjectListSync)
  {
    DDSDataObjectListSync obj_list;
    if (StormReflParseJson(obj_list, data) == false)
    {
      DDSLog::LogError("Invalid object list packet");
      return;
    }

    DDSLog::LogInfo("Got object sync id %d keys %d to %d node %d", obj_list.m_DataObjectType, obj_list.m_KeyRangeMin, obj_list.m_KeyRangeMax, node_id);
    DDSLog::LogInfo("Object list has %d elements", obj_list.m_Objects.size());

    auto & data_store = GetDataObjectStore(obj_list.m_DataObjectType);
    data_store.ProcessExportedObjects(obj_list.m_Objects);

    m_IncomingKeyspace.SetKeyRangeComplete(obj_list.m_RoutingTableGen, obj_list.m_DataObjectType, DDSKeyRange{ obj_list.m_KeyRangeMin, obj_list.m_KeyRangeMax });
  }
}

void DDSNodeState::SendTargetedMessage(DDSDataObjectAddress addr, std::string && message)
{
  if (KeyInKeyRange(addr.m_ObjectKey, m_LocalKeyRange))
  {
    if (m_IncomingKeyspace.IsCompleteForKey(addr))
    {
      HandleIncomingTargetedMessage(addr, message);
      return;
    }
  }
  else
  {
    DDSNodeId node_id = GetNodeIdForKey(addr.m_ObjectKey);
    if (m_NodeNetwork.RequestNodeConnection(node_id))
    {
      m_NodeNetwork.SendMessageToServer(node_id, std::move(message));
      return;
    }
  }

  auto result = m_PendingTargetedMessages.emplace(std::make_pair(addr, std::vector<std::string>{}));
  result.first->second.emplace_back(message);
}

DDSNodeId DDSNodeState::GetNodeIdForKey(DDSKey key) const
{
  for (auto & key_range : m_RoutingKeyRanges)
  {
    if (KeyInKeyRange(key, key_range.second))
    {
      return key_range.first;
    }
  }

  throw std::runtime_error("Invalid routing table");
}

DDSDataObjectStoreBase & DDSNodeState::GetDataObjectStore(int object_type_id)
{
  return *m_DataObjectList[object_type_id].get();
}

DDSNetworkBackend & DDSNodeState::GetBackend()
{
  return m_Backend;
}

DDSNodeNetworkService & DDSNodeState::GetNodeNetwork()
{
  return m_NodeNetwork;
}

DDSCoordinatorClientProtocol & DDSNodeState::GetCoordinatorConnection()
{
  return m_CoordinatorConnection;
}

DDSIncomingKeyspaceTransferManager & DDSNodeState::GetIncomingKeyspace()
{
  return m_IncomingKeyspace;
}

DDSOutgoingKeyspaceTransferManager & DDSNodeState::GetOutgoingKeyspace()
{
  return m_OutgoingKeyspace;
}

DDSNodeId DDSNodeState::GetLocalNodeId() const
{
  return m_LocalNodeId;
}

const DDSRoutingTable & DDSNodeState::GetRoutingTable() const
{
  return m_RoutingTable;
}

DDSKeyRange DDSNodeState::GetLocalKeyRange() const
{
  return m_LocalKeyRange;
}

uint64_t DDSNodeState::GetClientSecret() const
{
  return m_ClientSecret;
}

uint64_t DDSNodeState::GetServerSecret() const
{
  return m_ServerSecret;
}

uint32_t DDSNodeState::GetLocalInterface() const
{
  return m_LocalInterface;
}

int DDSNodeState::GetLocalPort() const
{
  return m_LocalPort;
}

void DDSNodeState::RecheckOutgoingTargetedMessages()
{
  auto itr = m_PendingTargetedMessages.begin();
  while(itr != m_PendingTargetedMessages.end())
  {
    auto itr_copy = itr;
    itr++;

    for (auto & msg : itr_copy->second)
    {
      if (KeyInKeyRange(itr_copy->first.m_ObjectKey, m_LocalKeyRange))
      {
        if (m_IncomingKeyspace.IsCompleteForKey(itr_copy->first))
        {
          for (auto & message : itr_copy->second)
          {
            HandleIncomingTargetedMessage(itr_copy->first, message);
          }

          m_PendingTargetedMessages.erase(itr_copy);
        }
      }
      else
      {
        DDSNodeId node_id = GetNodeIdForKey(itr_copy->first.m_ObjectKey);
        if (m_NodeNetwork.RequestNodeConnection(node_id))
        {
          for (auto & message : itr_copy->second)
          {
            m_NodeNetwork.SendMessageToServer(node_id, std::move(message));
          }

          m_PendingTargetedMessages.erase(itr_copy);
        }
      }
    }
  }
}

void DDSNodeState::HandleIncomingTargetedMessage(DDSDataObjectAddress addr, std::string & message)
{

}
