
#include <StormSockets/StormMessageReaderUtil.h>

#include "DDSWebsiteFactoryStaticContent.h"
#include "DDSNodeState.h"

DDSWebsiteFactoryStaticContent::DDSWebsiteFactoryStaticContent(DDSNodeState & node_state, 
  const StormSockets::StormSocketServerFrontendHttpSettings & settings, const DDSWebsiteFilesystemBuilder & fs) :
  DDSWebsiteFactoryBase(node_state, settings),
  m_Filesystem(node_state.m_Backend, fs)
{

}

bool DDSWebsiteFactoryStaticContent::IsValidConnectionId(StormSockets::StormSocketConnectionId connection_id)
{
  return m_Connections.find(connection_id) != m_Connections.end();
}

void DDSWebsiteFactoryStaticContent::HandleConnect(StormSockets::StormSocketConnectionId connection_id, uint32_t remote_ip, uint16_t remote_port)
{
  DDSWebsiteInterface website_interface(m_NodeState, *this, connection_id, remote_ip, remote_port);
  m_Connections.emplace(std::make_pair(connection_id, website_interface));
}

void DDSWebsiteFactoryStaticContent::HandleData(StormSockets::StormSocketConnectionId connection_id, StormSockets::StormHttpRequestReader & reader)
{
  auto connection = m_Connections.find(connection_id);
  if (connection == m_Connections.end())
  {
    ForceDisconnect(connection_id);
    return;
  }

  m_Filesystem.ServeFile(StormSockets::ReadMessageAsString(reader.GetURI()), connection->second);
}

void DDSWebsiteFactoryStaticContent::HandleDisconnect(StormSockets::StormSocketConnectionId connection_id)
{
  m_Connections.erase(connection_id);
}
