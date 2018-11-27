#pragma once


#include <map>
#include <memory>
#include <vector>

#include <StormSockets/StormSocketServerTypes.h>

#include "DDSNetworkBackend.h"
#include "DDSLoadBalancerMessages.refl.h"

namespace StormSockets
{
  class StormSocketServerFrontendWebsocket;
  class StormSocketClientFrontendWebsocket;
  class StormWebsocketMessageReader;
}

struct DDSLoadBalancerSettings
{
  const char * CoordinatorIpAddr = "localhost";
  int CoordinatorPort = 9001;
};

class DDSLoadBalancer
{
public:
  DDSLoadBalancer(
    const StormSockets::StormSocketInitSettings & backend_settings,
    const StormSockets::StormSocketServerFrontendWebsocketSettings & server_settings,
    const DDSLoadBalancerSettings & lb_settings);

  ~DDSLoadBalancer();

  void ProcessEvents();

private:

  enum State
  {
    kReconnectWait,
    kConnecting,
    kWaitingForInitialSync,
    kReady,
  };

  State m_State;
  DDSNetworkBackend m_Backend;

  std::string m_CoordinatorHost;
  int m_CoordinatorPort;
  time_t m_LastConnect;

  DDSLoadBalancerInfo m_NodeList;
  std::vector<char> m_RecvBuffer;

  std::unique_ptr<StormSockets::StormSocketServerFrontendWebsocket> m_Frontend;
  std::unique_ptr<StormSockets::StormSocketClientFrontendWebsocket> m_Client;
};
