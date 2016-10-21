#pragma once

#include <map>
#include <vector>

#include "DDSEndpointFactoryBase.h"
#include "DDSEndpointInterface.h"

template <class EndpointType>
class DDSEndpointFactory : public DDSEndpointFactoryBase
{
public:

  DDSEndpointFactory(DDSNodeState & node_state, const StormSockets::StormSocketServerFrontendWebsocketSettings & settings) :
    DDSEndpointFactoryBase(node_state, settings)
  {

  }

  bool IsValidConnectionId(StormSockets::StormSocketConnectionId connection_id)
  {
    return m_Connections.find(connection_id) != m_Connections.end();
  }

private:
  void HandleConnect(StormSockets::StormSocketConnectionId connection_id) override
  {
    m_Connections.emplace(std::make_pair(connection_id, std::unique_ptr<EndpointType>()));
  }

  void HandleHandshakeComplete(StormSockets::StormSocketConnectionId connection_id) override
  {
    auto & connection_data = m_Connections.at(connection_id);

    DDSEndpointInterface endpoint_interface(m_NodeState, *this, connection_id);
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
    m_Connections.erase(connection_id);
  }

private:

  std::map<StormSockets::StormSocketConnectionId, std::unique_ptr<EndpointType>> m_Connections;
};

