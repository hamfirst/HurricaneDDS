#pragma once

#include "DDSWebsiteFactoryBase.h"
#include "DDSWebsiteFilesystem.h"
#include "DDSWebsiteInterface.h"

class DDSWebsiteFilesystemBuilder;

class DDSWebsiteFactoryStaticContent : public DDSWebsiteFactoryBase
{
public:
  DDSWebsiteFactoryStaticContent(DDSNodeState & node_state, const StormSockets::StormSocketServerFrontendHttpSettings & settings, const DDSWebsiteFilesystemBuilder & fs);

  bool IsValidConnectionId(StormSockets::StormSocketConnectionId connection_id);

private:

  void HandleConnect(StormSockets::StormSocketConnectionId connection_id, uint32_t remote_ip, uint16_t remote_port) override;
  void HandleData(StormSockets::StormSocketConnectionId connection_id, StormSockets::StormHttpRequestReader & reader) override;
  void HandleDisconnect(StormSockets::StormSocketConnectionId connection_id) override;

private:

  DDSWebsiteFilesystem m_Filesystem;
  std::map<StormSockets::StormSocketConnectionId, DDSWebsiteInterface> m_Connections;
};

