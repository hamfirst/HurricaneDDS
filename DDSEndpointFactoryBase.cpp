
#include "DDSEndpointFactoryBase.h"
#include "DDSNetworkBackend.h"
#include "DDSNodeState.h"

#include <StormSockets\StormSocketServerFrontendWebsocket.h>

DDSEndpointFactoryBase::DDSEndpointFactoryBase(DDSNodeState & node_state, const StormSockets::StormSocketServerFrontendWebsocketSettings & settings) :
  m_NodeState(node_state),
  m_Frontend(std::make_unique<StormSockets::StormSocketServerFrontendWebsocket>(settings, node_state.GetBackend().m_Backend.get()))
{

}

DDSEndpointFactoryBase::~DDSEndpointFactoryBase()
{

}

void DDSEndpointFactoryBase::ProcessEvents()
{
  StormSockets::StormSocketEventInfo event;
  while (m_Frontend->GetEvent(event))
  {
    switch (event.Type)
    {
    case StormSockets::StormSocketEventType::ClientConnected:
      HandleConnect(event.ConnectionId);
      break;
    case StormSockets::StormSocketEventType::ClientHandShakeCompleted:
      HandleHandshakeComplete(event.ConnectionId, event.RemoteIP, event.RemotePort);
      break;
    case StormSockets::StormSocketEventType::Disconnected:
      HandleDisconnect(event.ConnectionId);
      m_Frontend->FinalizeConnection(event.ConnectionId);
      break;
    case StormSockets::StormSocketEventType::Data:
      HandleData(event.ConnectionId, event.GetWebsocketReader());
      break;
    }
  }
}

bool DDSEndpointFactoryBase::SendData(StormSockets::StormSocketConnectionId connection_id, const std::string & data)
{
  if (IsValidConnectionId(connection_id) == false)
  {
    return false;
  }

  auto packet = m_Frontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Text, true);
  packet.WriteByteBlock(data.data(), 0, data.length());
  m_Frontend->FinalizeOutgoingPacket(packet);
  m_Frontend->SendPacketToConnectionBlocking(packet, connection_id);
  m_Frontend->FreeOutgoingPacket(packet);
  return true;
}

void DDSEndpointFactoryBase::ForceDisconnect(StormSockets::StormSocketConnectionId connection_id)
{
  m_Frontend->ForceDisconnect(connection_id);
}
