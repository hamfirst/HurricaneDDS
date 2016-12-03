#pragma once

#include "DDSNodeId.h"

#include <StormSockets/StormSocketConnectionId.h>

class DDSCoordinatorState;

class DDSCoordinatorServerProtocol
{
public:
  DDSCoordinatorServerProtocol(DDSCoordinatorState & coordinator_state, StormSockets::StormSocketConnectionId connection_id, uint32_t remote_ip);
  bool IsConnected() const;

  bool HandleMessage(const char * msg, int length);

  bool CheckNodeId(DDSNodeId node_id) const;
  DDSNodeId GetNodeId() const;

private:

  template <class T>
  void SendMessageToClient(const T & t);
  
  enum State
  {
    kHandshakeRequest,
    kHandshakeFinalize,
    kConnected,
  };

  DDSCoordinatorState & m_CoordinatorState;
  State m_State;

  StormSockets::StormSocketConnectionId m_ConnectionId;
  DDSNodeId m_NodeId;

  uint64_t m_ExpectedChallengeResponse;

  uint32_t m_RemoteIp;
};

