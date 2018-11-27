#pragma once

#include "DDSConnectionFactoryBase.h"

class DDSNodeState;

namespace StormSockets
{
  class StormSocketServerFrontendHttp;
  class StormHttpResponseWriter;
}

class DDSWebsiteFactoryBase : public DDSConnectionFactoryBase
{
public:
  DDSWebsiteFactoryBase(DDSNodeState & node_state, const StormSockets::StormSocketServerFrontendHttpSettings & settings);
  ~DDSWebsiteFactoryBase();

  void ProcessEvents();

  bool SendResponse(StormSockets::StormSocketConnectionId connection_id, int response_code, const char * response_phrase, 
    const void * header_data, int header_length, const void * body_data, unsigned int body_length);

  bool SendResponse(StormSockets::StormSocketConnectionId connection_id, StormSockets::StormHttpResponseWriter & writer);

  void ForceDisconnect(StormSockets::StormSocketConnectionId connection_id) override;
  DDSNodePort GetListenPort() override;

protected:
  virtual void HandleConnect(StormSockets::StormSocketConnectionId connection_id, uint32_t remote_ip, uint16_t remote_port) = 0;
  virtual void HandleData(StormSockets::StormSocketConnectionId connection_id, StormSockets::StormHttpRequestReader & reader) = 0;
  virtual void HandleDisconnect(StormSockets::StormSocketConnectionId connection_id) = 0;

protected:

  std::unique_ptr<StormSockets::StormSocketServerFrontendHttp> m_Frontend;
  DDSNodeState & m_NodeState;
  DDSNodePort m_Port;
};
