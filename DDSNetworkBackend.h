#pragma once

#include <StormSockets/StormSocketServerTypes.h>

#include <memory>

namespace StormSockets
{
  class StormSocketBackend;
}

class DDSNetworkBackend
{
public:
  DDSNetworkBackend(const StormSockets::StormSocketInitSettings & settings);
  ~DDSNetworkBackend();

private:
  friend class DDSCoordinatorNetworkService;
  friend class DDSCoordinatorClientProtocol;
  friend class DDSNodeNetworkService;
  friend class DDSServerToServerSender;
  friend class DDSServerToServerReceiver;
  friend class DDSEndpointFactoryBase;
  friend class DDSWebsiteFactoryBase;
  friend class DDSWebsiteFilesystem;
  friend class DDSHttpClient;

  std::unique_ptr<StormSockets::StormSocketBackend> m_Backend;
};
