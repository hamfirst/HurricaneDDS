
#include "DDSLog.h"
#include "DDSCoordinatorNetworkService.h"
#include "DDSCoordinatorServerProtocol.h"

#include <StormSockets\StormSocketServerFrontendWebsocket.h>

DDSCoordinatorNetworkService::DDSCoordinatorNetworkService(DDSCoordinatorState & coordinator_state,
  const StormSockets::StormSocketInitSettings & backend_settings,
  const StormSockets::StormSocketServerFrontendWebsocketSettings & server_settings) :
  m_CoordinatorState(coordinator_state),
  m_Backend(backend_settings),
  m_ServerFrontend(std::make_unique<StormSockets::StormSocketServerFrontendWebsocket>(server_settings, m_Backend.m_Backend.get()))
{

}

void DDSCoordinatorNetworkService::WaitForEvent()
{
  m_ServerFrontend->WaitForEvent(100);
}

void DDSCoordinatorNetworkService::ProcessEvents()
{
  StormSockets::StormSocketEventInfo event;
  while (m_ServerFrontend->GetEvent(event))
  {
    switch (event.Type)
    {
    case StormSockets::StormSocketEventType::ClientConnected:
      DDSLog::LogVerbose("Got client connect from %d", event.ConnectionId);
      HandleConnect(event.ConnectionId, event.RemoteIP, event.RemotePort);
      break;
    case StormSockets::StormSocketEventType::Data:
      HandleData(event.ConnectionId, event.GetWebsocketReader());
      break;
    case StormSockets::StormSocketEventType::Disconnected:
      DDSLog::LogVerbose("Got client disconnect from %d", event.ConnectionId);
      m_ServerFrontend->FinalizeConnection(event.ConnectionId);
      break;
    }
  }
}

void DDSCoordinatorNetworkService::SendMessageToClient(StormSockets::StormSocketConnectionId connection_id, const char * message, std::size_t length)
{
  auto packet = m_ServerFrontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Text, true);
  packet.WriteByteBlock(message, 0, length);
  m_ServerFrontend->FinalizeOutgoingPacket(packet);
  m_Backend.m_Backend->SendPacketToConnectionBlocking(packet, connection_id);
  m_ServerFrontend->FreeOutgoingPacket(packet);
}

void DDSCoordinatorNetworkService::SendMessageToAllConnectedClients(const char * message, std::size_t length)
{
  auto packet = m_ServerFrontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Text, true);
  packet.WriteByteBlock(message, 0, length);
  m_ServerFrontend->FinalizeOutgoingPacket(packet);

  for (auto & itr : m_ConnectionIdMap)
  {
    if (itr.second->IsConnected())
    {
      DDSLog::LogVerbose("Sending message to client %d", itr.first);
      m_Backend.m_Backend->SendPacketToConnectionBlocking(packet, itr.first);
    }
  }

  m_ServerFrontend->FreeOutgoingPacket(packet);
}

void DDSCoordinatorNetworkService::HandleConnect(StormSockets::StormSocketConnectionId connection_id, uint32_t addr, uint16_t port)
{
  auto emplace_val = 
    m_ConnectionIdMap.emplace(std::make_pair(connection_id, std::make_unique<DDSCoordinatorServerProtocol>(m_CoordinatorState, connection_id, addr)));
}

void DDSCoordinatorNetworkService::HandleData(StormSockets::StormSocketConnectionId connection_id, StormSockets::StormWebsocketMessageReader & reader)
{
  m_RecvBuffer.resize(reader.GetDataLength() + 1);
  reader.ReadByteBlock(m_RecvBuffer.data(), reader.GetDataLength());
  m_RecvBuffer[reader.GetDataLength()] = 0;

  std::unique_ptr<DDSCoordinatorServerProtocol> & protocol = m_ConnectionIdMap.at(connection_id);
  protocol->HandleMessage(m_RecvBuffer.data(), reader.GetDataLength());
}