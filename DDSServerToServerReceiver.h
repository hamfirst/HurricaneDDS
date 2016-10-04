#pragma once

#include <vector>
#include <string>

#include <StormSockets\StormSocketConnectionId.h>

#include "DDSNodeId.h"

class DDSNodeState;
class DDSNodeNetworkService;

namespace StormSockets
{
  class StormWebsocketMessageReader;
}

class DDSServerToServerReceiver
{
public:
  DDSServerToServerReceiver(DDSNodeState & node_state, StormSockets::StormSocketConnectionId connection_id);

  bool HandleIncomingMessage(StormSockets::StormWebsocketMessageReader & message_reader);
  bool IsConnected() const;

private:

  void SendMessageToServer(const std::string & message);

  enum State
  {
    kHandshakeRequest,
    kHandshakeFinalize,
    kConnected,
  };

  State m_State;
  DDSNodeState & m_NodeState;

  StormSockets::StormSocketConnectionId m_ConnectionId;
  uint64_t m_ExpectedChallengeResponse;

  std::vector<char> m_RecvBuffer;
  DDSNodeId m_NodeId;
};


