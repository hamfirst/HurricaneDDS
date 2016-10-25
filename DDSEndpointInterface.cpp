
#include "DDSEndpointInterface.h"
#include "DDSEndpointFactoryBase.h"
#include "DDSNodeState.h"

#include "DDSServerToServerMessages.refl.meta.h"

DDSEndpointInterface::DDSEndpointInterface(DDSNodeState & node_state, DDSEndpointFactoryBase & endpoint_factory,
  StormSockets::StormSocketConnectionId connection_id, uint32_t remote_ip, uint16_t remote_port) :
  DDSConnectionInterface(node_state, endpoint_factory, connection_id, remote_ip, remote_port),
  m_EndpointFactory(endpoint_factory)
{

}

bool DDSEndpointInterface::SendData(const std::string & data)
{
  return m_EndpointFactory.SendData(m_ConnectionId, data);
}
