
#include "DDSLog.h"
#include "DDSNodeNetworkService.h"
#include "DDSNodeState.h"

#include <StormSockets/StormSocketClientFrontendWebsocket.h>
#include <StormSockets/StormSocketServerFrontendWebsocket.h>


DDSNodeNetworkService::DDSNodeNetworkService(DDSNodeState & node_state,
                                             const StormSockets::StormSocketServerFrontendWebsocketSettings & server_settings,
                                             const StormSockets::StormSocketClientFrontendWebsocketSettings & client_settings) :
  m_NodeState(node_state),
  m_ClientFrontend(std::make_unique<StormSockets::StormSocketClientFrontendWebsocket>(client_settings, node_state.GetBackend().m_Backend.get())),
  m_ServerFrontend(std::make_unique<StormSockets::StormSocketServerFrontendWebsocket>(server_settings, node_state.GetBackend().m_Backend.get()))
{

}

DDSNodeNetworkService::~DDSNodeNetworkService()
{

}

void DDSNodeNetworkService::SendMessageToServer(DDSNodeId node_id, std::string && data)
{
  bool sent = false;

  auto itr = m_NodeConnectionMap.find(node_id);
  if (itr == m_NodeConnectionMap.end())
  {
    CreateNodeConnection(node_id);
  }
  else
  {
    auto & sender = m_Senders.at(itr->second);
    if (sender.IsConnected())
    {
      sender.SendMessageToServer(data);
      sent = true;
    }
  }

  if (sent == false)
  {
    auto pending_itr = m_PendingMessages.find(node_id);
    if (pending_itr == m_PendingMessages.end())
    {
      m_PendingMessages.emplace(node_id, std::vector<std::string>{data});
    }
    else
    {
      pending_itr->second.emplace_back(data);
    }
  }
}

bool DDSNodeNetworkService::RequestNodeConnection(DDSNodeId node_id)
{
  auto itr = m_NodeConnectionMap.find(node_id);
  if (itr == m_NodeConnectionMap.end())
  {
    CreateNodeConnection(node_id);
  }
  else
  {
    auto & sender = m_Senders.at(itr->second);
    if (sender.IsConnected())
    {
      return true;
    }
  }

  return false;
}

void DDSNodeNetworkService::NodeConnectionReady(DDSNodeId id, DDSServerToServerSender & sender)
{
  auto pending_itr = m_PendingMessages.find(id);
  if (pending_itr != m_PendingMessages.end())
  {
    for (auto & str : pending_itr->second)
    {
      sender.SendMessageToServer(str);
    }
  }
}

void DDSNodeNetworkService::CreateNodeConnection(DDSNodeId id)
{
  for (auto & node_data : m_NodeState.GetRoutingTable().m_Table)
  {
    if (node_data.m_Id == id)
    {
      char ip_addr[128];
      snprintf(ip_addr, sizeof(ip_addr), "%d.%d.%d.%d",
        (node_data.m_Addr >> 24) & 0xFF,
        (node_data.m_Addr >> 16) & 0xFF,
        (node_data.m_Addr >> 8) & 0xFF,
        (node_data.m_Addr >> 0) & 0xFF);

      DDSLog::LogInfo("Creating connection to %s:%d", ip_addr, node_data.m_Port);

      auto connection_id = m_ClientFrontend->RequestConnect(ip_addr, node_data.m_Port, StormSockets::StormSocketClientFrontendWebsocketRequestData{});
      if (connection_id == StormSockets::StormSocketConnectionId::InvalidConnectionId)
      {
        return;
      }

      m_NodeConnectionMap.emplace(std::make_pair(id, connection_id));
      m_Senders.emplace(std::make_pair(connection_id, DDSServerToServerSender(m_NodeState, connection_id, id)));
    }
  }
}

void DDSNodeNetworkService::ProcessEvents()
{
  StormSockets::StormSocketEventInfo event;
  while (m_ClientFrontend->GetEvent(event))
  {
    switch (event.Type)
    {
      case StormSockets::StormSocketEventType::ClientConnected:
      {
        auto & sender = m_Senders.at(event.ConnectionId);
        DDSLog::LogVerbose("Sender %d connected", event.ConnectionId.GetIndex());
      }
      break;
      case StormSockets::StormSocketEventType::ClientHandShakeCompleted:
      {
        auto & sender = m_Senders.at(event.ConnectionId);
        sender.HandleConnectionEstablished();
        DDSLog::LogVerbose("Sender %d established", event.ConnectionId.GetIndex());
      }
      break;
      case StormSockets::StormSocketEventType::Data:
      {
        auto & sender = m_Senders.at(event.ConnectionId);
        sender.HandleIncomingMessage(event.GetWebsocketReader());
      }
      break;
      case StormSockets::StormSocketEventType::Disconnected:
      {
        auto & sender = m_Senders.at(event.ConnectionId);
        m_NodeConnectionMap.erase(sender.GetTargetNodeId());
        m_PendingMessages.erase(sender.GetTargetNodeId());
        m_Senders.erase(event.ConnectionId);
        DDSLog::LogVerbose("Sender %d disconnected", event.ConnectionId.GetIndex());
        m_ClientFrontend->FinalizeConnection(event.ConnectionId);
      }
      break;
    }
  }

  while (m_ServerFrontend->GetEvent(event))
  {
    switch (event.Type)
    {
      case StormSockets::StormSocketEventType::ClientConnected:
      {
        DDSLog::LogVerbose("Receiver %d connected", event.ConnectionId.GetIndex());
        m_Receievers.emplace(std::make_pair(event.ConnectionId, DDSServerToServerReceiver(m_NodeState, event.ConnectionId)));
      }
      break;
      case StormSockets::StormSocketEventType::ClientHandShakeCompleted:
      break;
      case StormSockets::StormSocketEventType::Data:
      {
        auto & receiver = m_Receievers.at(event.ConnectionId);
        receiver.HandleIncomingMessage(event.GetWebsocketReader());
      }
      break;
      case StormSockets::StormSocketEventType::Disconnected:
      {
        DDSLog::LogVerbose("Receiver %d disconnected", event.ConnectionId.GetIndex());
        m_Receievers.erase(event.ConnectionId);
        m_ServerFrontend->FinalizeConnection(event.ConnectionId);
      }
      break;
    }
  }
}


