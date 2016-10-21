#pragma once

#include <memory>
#include <string>

#include <StormSockets\StormSocketServerTypes.h>
#include <StormSockets\StormWebsocketMessageReader.h>

class DDSNodeState;

namespace StormSockets
{
  class StormSocketServerFrontendWebsocket;
}

class DDSEndpointFactoryBase
{
public:
  DDSEndpointFactoryBase(DDSNodeState & node_state, const StormSockets::StormSocketServerFrontendWebsocketSettings & settings);
  ~DDSEndpointFactoryBase();

  void ProcessEvents();
  bool SendData(StormSockets::StormSocketConnectionId connection_id, const std::string & data);

  virtual bool IsValidConnectionId(StormSockets::StormSocketConnectionId connection_id) = 0;

protected:
  virtual void HandleConnect(StormSockets::StormSocketConnectionId connection_id) = 0;
  virtual void HandleHandshakeComplete(StormSockets::StormSocketConnectionId connection_id) = 0;
  virtual void HandleData(StormSockets::StormSocketConnectionId connection_id, StormSockets::StormWebsocketMessageReader & reader) = 0;
  virtual void HandleDisconnect(StormSockets::StormSocketConnectionId connection_id) = 0;


protected:

  std::unique_ptr<StormSockets::StormSocketServerFrontendWebsocket> m_Frontend;
  DDSNodeState & m_NodeState;
};
