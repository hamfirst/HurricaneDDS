
#include "DDSWebsiteInterface.h"
#include "DDSWebsiteFactoryBase.h"
#include "DDSNodeState.h"

#include "DDSServerToServerMessages.refl.meta.h"

DDSWebsiteInterface::DDSWebsiteInterface(DDSNodeState & node_state, DDSWebsiteFactoryBase & Website_factory,
  StormSockets::StormSocketConnectionId connection_id, uint32_t remote_ip, uint16_t remote_port) :
  DDSConnectionInterface(node_state, Website_factory, connection_id, remote_ip, remote_port),
  m_WebsiteFactory(Website_factory)
{

}

void DDSWebsiteInterface::SendResponse(const char * body, int response_code, const char * response_phrase)
{
  m_WebsiteFactory.SendResponse(m_ConnectionId, response_code, response_phrase, nullptr, 0, body, strlen(body));
}

void DDSWebsiteInterface::SendResponse(const char * headers, const char * body, int response_code, const char * response_phrase)
{
  m_WebsiteFactory.SendResponse(m_ConnectionId, response_code, response_phrase, headers, strlen(headers), body, strlen(body));
}

void DDSWebsiteInterface::SendResponse(StormSockets::StormHttpResponseWriter & writer)
{
  m_WebsiteFactory.SendResponse(m_ConnectionId, writer);
}
