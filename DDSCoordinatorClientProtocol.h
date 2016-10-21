#pragma once

#include "DDSNodeId.h"

#include <StormSockets\StormSocketConnectionId.h>

class DDSNodeState;

namespace StormSockets
{
  class StormSocketClientFrontendWebsocket;
}

struct DDSCoordinatorClientSettings
{
  const char * CoordinatorIpAddr = "localhost";
  int CoordinatorPort = 9001;
};

class DDSCoordinatorClientProtocol
{
public:
  DDSCoordinatorClientProtocol(DDSNodeState & node_state, const DDSCoordinatorClientSettings & settings);
  ~DDSCoordinatorClientProtocol();

  void ProcessEvents();
  void RequestConnect();

  bool HandleConnectionEstablished();
  bool HandleMessage(const char * msg, int length);

  void SendMessageToCoordinator(const std::string && data);

private:

  template <class T>
  void SendMessageToServer(const T & t);

  enum State
  {
    kDisconnected,
    kConnecting,
    kHandshakeResponse,
    kNodeInit,
    kRoutingTableInit,
    kConnected,
  };

  DDSNodeState & m_NodeState;
  std::unique_ptr<StormSockets::StormSocketClientFrontendWebsocket> m_ClientFrontend;

  State m_State;

  StormSockets::StormSocketConnectionId m_ConnectionId;
  uint64_t m_ExpectedChallengeResponse;

  std::string m_CoordinatorIpAddr;
  int m_CoordinatorPort;

  std::vector<char> m_MessageBuffer;

  DDSNodeId m_NodeId;
  bool m_InitialNode;

  uint64_t m_ClientSecret;
  uint64_t m_ServerSecret;
};

