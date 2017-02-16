
#include <StormRefl/StormReflJsonStd.h>

#include "DDSLoadBalancerNetworkService.h"
#include "DDSLoadBalancerMessages.refl.meta.h"

#include <StormSockets/StormSocketServerFrontendWebsocket.h>

DDSLoadBalancerNetworkService::DDSLoadBalancerNetworkService(
  DDSNetworkBackend & backend,
  DDSCoordinatorState & coordinator_state,
  const StormSockets::StormSocketServerFrontendWebsocketSettings & server_settings,
  int endpoint_id) :
  m_Backend(backend),
  m_CoordinatorState(coordinator_state),
  m_ServerFrontend(std::make_unique<StormSockets::StormSocketServerFrontendWebsocket>(server_settings, m_Backend.m_Backend.get())),
  m_EndpointId(endpoint_id)
{

}

void DDSLoadBalancerNetworkService::ProcessEvents()
{
  StormSockets::StormSocketEventInfo event;
  while (m_ServerFrontend->GetEvent(event))
  {
    switch (event.Type)
    {
    case StormSockets::StormSocketEventType::ClientHandShakeCompleted:
      {
        std::string message = GetNodeListMessage();

        auto packet = m_ServerFrontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Text, true);
        packet.WriteByteBlock(message.c_str(), 0, message.length());
        m_ServerFrontend->FinalizeOutgoingPacket(packet);

        m_ServerFrontend->SendPacketToConnectionBlocking(packet, event.ConnectionId);
        m_ServerFrontend->FreeOutgoingPacket(packet);

        m_ConnectionIds.push_back(event.ConnectionId);
      }
      break;
    case StormSockets::StormSocketEventType::Data:
      m_ServerFrontend->ForceDisconnect(event.ConnectionId);
      m_ServerFrontend->FreeIncomingPacket(event.GetWebsocketReader());
      break;
    case StormSockets::StormSocketEventType::Disconnected:
      m_ServerFrontend->FinalizeConnection(event.ConnectionId);

      for (auto itr = m_ConnectionIds.begin(), end = m_ConnectionIds.end(); itr != end; ++itr)
      {
        if (*itr == event.ConnectionId)
        {
          m_ConnectionIds.erase(itr);
          break;
        }
      }
      break;
    }
  }
}

void DDSLoadBalancerNetworkService::UpdateRoutingTable(const DDSRoutingTable & routing_table)
{
  m_RoutingTable = routing_table;
}

void DDSLoadBalancerNetworkService::UpdateNode(DDSNodeId node_id, float cpu)
{
  m_CpuUsage[node_id] = cpu;
}

void DDSLoadBalancerNetworkService::SyncNodeList()
{
  std::string message = GetNodeListMessage();

  auto packet = m_ServerFrontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Text, true);
  packet.WriteByteBlock(message.c_str(), 0, message.length());
  m_ServerFrontend->FinalizeOutgoingPacket(packet);

  for (auto id : m_ConnectionIds)
  {
    m_ServerFrontend->SendPacketToConnectionBlocking(packet, id);
  }

  m_ServerFrontend->FreeOutgoingPacket(packet);
}

std::string DDSLoadBalancerNetworkService::GetNodeListMessage()
{
  DDSLoadBalancerInfo info;

  for (auto & node : m_RoutingTable.m_Table)
  {
    auto cpu = m_CpuUsage.find(node.m_Id);

    if (cpu != m_CpuUsage.end())
    {
      info.m_Nodes.emplace_back(DDSLoadBalancerNode{ GetNodeAddrAsString(node.m_Addr), node.m_EndpointPorts[m_EndpointId], (int)cpu->second });
    }
  }

  return StormReflEncodeJson(info);
}
