#pragma once

#include "DDSConnectionInterface.h"

class DDSWebsiteFactoryBase;

namespace StormSockets
{
  class StormHttpResponseWriter;
}

class DDSWebsiteInterface : public DDSConnectionInterface
{
public:
  DDSWebsiteInterface(DDSNodeState & node_state, DDSWebsiteFactoryBase & website_factory,
    StormSockets::StormSocketConnectionId connection_id, uint32_t remote_ip, uint16_t remote_port);

  DDSWebsiteInterface(const DDSWebsiteInterface & rhs) = default;
  DDSWebsiteInterface(DDSWebsiteInterface && rhs) = default;

  void SendResponse(const char * body, int response_code = 200, const char * response_phrase = "OK");
  void SendResponse(const char * headers, const char * body, int response_code = 200, const char * response_phrase = "OK");

  void SendResponse(StormSockets::StormHttpResponseWriter & writer);

protected:
  DDSWebsiteFactoryBase & m_WebsiteFactory;
};

