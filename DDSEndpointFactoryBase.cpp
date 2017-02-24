
#include "DDSEndpointFactoryBase.h"
#include "DDSNetworkBackend.h"
#include "DDSNodeState.h"

#include <StormSockets/StormSocketServerFrontendWebsocket.h>

DDSEndpointFactoryBase::DDSEndpointFactoryBase(DDSNodeState & node_state, const StormSockets::StormSocketServerFrontendWebsocketSettings & settings) :
  m_NodeState(node_state),
  m_Frontend(std::make_unique<StormSockets::StormSocketServerFrontendWebsocket>(settings, node_state.m_Backend.m_Backend.get())),
  m_Port(settings.ListenSettings.Port)
{

}

DDSEndpointFactoryBase::~DDSEndpointFactoryBase()
{

}

void DDSEndpointFactoryBase::ProcessEvents()
{
  StormSockets::StormSocketEventInfo event;
  bool got_connection = false;

  while (m_Frontend->GetEvent(event))
  {
    switch (event.Type)
    {
    case StormSockets::StormSocketEventType::ClientConnected:
      HandleConnect(event.ConnectionId);

      if (got_connection == false)
      {
        got_connection = true;
      }
      else
      {
        break;
      }
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
      m_Frontend->FreeIncomingPacket(event.GetWebsocketReader());
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

DDSNodePort DDSEndpointFactoryBase::GetListenPort()
{
  return m_Port;
}