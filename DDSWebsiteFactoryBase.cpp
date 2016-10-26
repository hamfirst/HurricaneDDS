
#include "DDSWebsiteFactoryBase.h"
#include "DDSNetworkBackend.h"
#include "DDSNodeState.h"

#include <StormSockets/StormSocketServerFrontendHttp.h>

DDSWebsiteFactoryBase::DDSWebsiteFactoryBase(DDSNodeState & node_state, const StormSockets::StormSocketServerFrontendHttpSettings & settings) :
  m_NodeState(node_state),
  m_Frontend(std::make_unique<StormSockets::StormSocketServerFrontendHttp>(settings, node_state.GetBackend().m_Backend.get()))
{

}

DDSWebsiteFactoryBase::~DDSWebsiteFactoryBase()
{

}

void DDSWebsiteFactoryBase::ProcessEvents()
{
  StormSockets::StormSocketEventInfo event;
  while (m_Frontend->GetEvent(event))
  {
    switch (event.Type)
    {
    case StormSockets::StormSocketEventType::ClientConnected:
      HandleConnect(event.ConnectionId, event.RemoteIP, event.RemotePort);
      break;
    case StormSockets::StormSocketEventType::ClientHandShakeCompleted:
      break;
    case StormSockets::StormSocketEventType::Disconnected:
      HandleDisconnect(event.ConnectionId);
      m_Frontend->FinalizeConnection(event.ConnectionId);
      break;
    case StormSockets::StormSocketEventType::Data:
      HandleData(event.ConnectionId, event.GetHttpRequestReader());
      break;
    }
  }
}

bool DDSWebsiteFactoryBase::SendResponse(StormSockets::StormSocketConnectionId connection_id, int response_code, const char * response_phrase, 
  const void * header_data, int header_length, const void * body_data, unsigned int body_length)
{
  if (IsValidConnectionId(connection_id) == false)
  {
    return false;
  }

  auto packet = m_Frontend->CreateOutgoingResponse(response_code, response_phrase);
  packet.WriteHeaders(header_data, header_length);
  packet.WriteBody(body_data, body_length);
  packet.FinalizeHeaders(true);
  m_Frontend->SendResponse(connection_id, packet);
  m_Frontend->FreeOutgoingResponse(packet);
  return true;
}

bool DDSWebsiteFactoryBase::SendResponse(StormSockets::StormSocketConnectionId connection_id, StormSockets::StormHttpResponseWriter & writer)
{
  if (IsValidConnectionId(connection_id) == false)
  {
    return false;
  }

  m_Frontend->SendResponse(connection_id, writer);
  return true;
}

void DDSWebsiteFactoryBase::ForceDisconnect(StormSockets::StormSocketConnectionId connection_id)
{
  m_Frontend->ForceDisconnect(connection_id);
}
