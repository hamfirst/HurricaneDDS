#pragma once

#include <memory>

#include "DDSConnectionFactoryBase.h"

class DDSNodeState;

namespace StormSockets
{
  class StormSocketServerFrontendWebsocket;
}

class DDSEndpointFactoryBase : public DDSConnectionFactoryBase
{
public:
  DDSEndpointFactoryBase(DDSNodeState & node_state, const StormSockets::StormSocketServerFrontendWebsocketSettings & settings);
  ~DDSEndpointFactoryBase();

  void ProcessEvents();
  bool SendData(StormSockets::StormSocketConnectionId connection_id, const std::string & data);

  void ForceDisconnect(StormSockets::StormSocketConnectionId connection_id) override;
  DDSNodePort GetListenPort() override;

protected:
  virtual void HandleConnect(StormSockets::StormSocketConnectionId connection_id) = 0;
  virtual void HandleHandshakeComplete(StormSockets::StormSocketConnectionId connection_id, uint32_t remote_ip, uint16_t remote_port) = 0;
  virtual void HandleData(StormSockets::StormSocketConnectionId connection_id, StormSockets::StormWebsocketMessageReader & reader) = 0;
  virtual void HandleDisconnect(StormSockets::StormSocketConnectionId connection_id) = 0;

protected:

  std::unique_ptr<StormSockets::StormSocketServerFrontendWebsocket> m_Frontend;
  DDSNodePort m_Port;
  DDSNodeState & m_NodeState;
};
