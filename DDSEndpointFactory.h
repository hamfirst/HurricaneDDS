#pragma once

#include <map>
#include <vector>

#include "DDSCall.h"
#include "DDSEndpointFactoryBase.h"
#include "DDSEndpointInterface.h"

DDS_DECLARE_CALL(HandleDisconnect);

template <class EndpointType>
class DDSEndpointFactory : public DDSEndpointFactoryBase
{
public:

  DDSEndpointFactory(DDSNodeState & node_state, const StormSockets::StormSocketServerFrontendWebsocketSettings & settings) :
    DDSEndpointFactoryBase(node_state, settings)
  {

  }

  bool IsValidConnectionId(StormSockets::StormSocketConnectionId connection_id) override
  {
    return m_Connections.find(connection_id) != m_Connections.end();
  }

private:
  void HandleConnect(StormSockets::StormSocketConnectionId connection_id) override
  {
    m_Connections.emplace(std::make_pair(connection_id, std::unique_ptr<EndpointType>()));
  }

  void HandleHandshakeComplete(StormSockets::StormSocketConnectionId connection_id, uint32_t remote_ip, uint16_t remote_port) override
  {
    auto & connection_data = m_Connections.at(connection_id);

    DDSEndpointInterface endpoint_interface(m_NodeState, *this, connection_id, remote_ip, remote_port);
    connection_data = std::make_unique<EndpointType>(endpoint_interface);
  }

  void HandleData(StormSockets::StormSocketConnectionId connection_id, StormSockets::StormWebsocketMessageReader & reader) override
  {
    auto & connection_data = m_Connections.at(connection_id);
    std::vector<char> buffer(reader.GetDataLength() + 1);
    reader.ReadByteBlock(buffer.data(), reader.GetDataLength());
    buffer[reader.GetDataLength()] = 0;

    connection_data->HandleData(buffer.data());
  }

  void HandleDisconnect(StormSockets::StormSocketConnectionId connection_id) override
  {
    auto itr = m_Connections.find(connection_id);
    if (itr == m_Connections.end())
    {
      return;
    }

    auto & ep = *itr->second.get();

    DDS_CALL_FUNC(HandleDisconnect, ep);
    m_Connections.erase(itr);
  }

private:

  std::map<StormSockets::StormSocketConnectionId, std::unique_ptr<EndpointType>> m_Connections;
};

