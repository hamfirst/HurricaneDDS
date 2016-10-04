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

class DDSServerToServerSender
{
public:
  DDSServerToServerSender(DDSNodeState & node_state, StormSockets::StormSocketConnectionId connection_id, DDSNodeId target_node_id);

  void HandleConnectionEstablished();
  bool HandleIncomingMessage(StormSockets::StormWebsocketMessageReader & message_reader);

  bool IsConnected() const;
  DDSNodeId GetTargetNodeId() const;

  void SendMessageToServer(const std::string & message);

private:

  enum State
  {
    kConnecting,
    kHandshake,
    kConnected,
  };

  State m_State;
  DDSNodeState & m_NodeState;

  DDSNodeId m_TargetNodeId;

  StormSockets::StormSocketConnectionId m_ConnectionId;
  uint64_t m_ExpectedChallengeResponse;

  std::vector<char> m_RecvBuffer;
};


