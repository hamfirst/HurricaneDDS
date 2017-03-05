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

  std::string GetMemoryReport();

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
  friend class DDSLoadBalancer;
  friend class DDSLoadBalancerNetworkService;

  std::unique_ptr<StormSockets::StormSocketBackend> m_Backend;
};
