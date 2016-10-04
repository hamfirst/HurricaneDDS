#pragma once

#include <StormSockets\StormSocketServerTypes.h>

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

  std::unique_ptr<StormSockets::StormSocketBackend> m_Backend;
};
