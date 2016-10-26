#pragma once

#include <map>
#include <vector>

#include <StormSockets/StormMessageReaderUtil.h>

#include "DDSWebsiteFactoryBase.h"
#include "DDSWebsiteInterface.h"

template <class WebsiteType>
class DDSWebsiteFactory : public DDSWebsiteFactoryBase
{
public:

  DDSWebsiteFactory(DDSNodeState & node_state, const StormSockets::StormSocketServerFrontendHttpSettings & settings) :
    DDSWebsiteFactoryBase(node_state, settings)
  {

  }

  bool IsValidConnectionId(StormSockets::StormSocketConnectionId connection_id)
  {
    return m_Connections.find(connection_id) != m_Connections.end();
  }

private:
  void HandleConnect(StormSockets::StormSocketConnectionId connection_id, uint32_t remote_ip, uint16_t remote_port) override
  {
    auto itr = m_Connections.emplace(std::make_pair(connection_id, std::unique_ptr<WebsiteType>()));
    auto & connection_data = itr.first->second;
    DDSWebsiteInterface website_interface(m_NodeState, *this, connection_id, remote_ip, remote_port);
    connection_data = std::make_unique<WebsiteType>(website_interface);
  }

  void HandleData(StormSockets::StormSocketConnectionId connection_id, StormSockets::StormHttpRequestReader & reader) override
  {
    auto & connection_data = m_Connections.at(connection_id);
    std::string method = StormSockets::ReadMessageAsString(reader.GetMethod());
    std::string uri = StormSockets::ReadMessageAsString(reader.GetURI());
    std::string headers = StormSockets::ReadMessageAsString(reader.GetHeaderReader());
    std::string body = StormSockets::ReadMessageAsString(reader.GetBodyReader());

    connection_data->HandleRequest(method, uri, headers, body);
  }

  void HandleDisconnect(StormSockets::StormSocketConnectionId connection_id) override
  {
    m_Connections.erase(connection_id);
  }

private:

  std::map<StormSockets::StormSocketConnectionId, std::unique_ptr<WebsiteType>> m_Connections;
};

