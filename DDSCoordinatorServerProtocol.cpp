
#include <random>
#include <chrono>

#include "DDSRandom.h"
#include "DDSLog.h"
#include "DDSVersion.h"
#include "DDSChallenge.h"
#include "DDSServerMessage.h"
#include "DDSCoordinatorState.h"
#include "DDSCoordinatorServerProtocol.h"
#include "DDSCoordinatorProtocolMessages.refl.meta.h"

#include <hash/Hash.h>
#include <StormRefl/StormReflJson.h>
#include <StormRefl/StormReflMetaEnum.h>

#include <StormSockets/StormSocketServerFrontendWebsocket.h>

template <class T>
void DDSCoordinatorServerProtocol::SendMessageToClient(const T & t)
{
  std::string send_buffer = DDSGetServerMessage(t);

  m_CoordinatorState.GetNetworkService().SendMessageToClient(m_ConnectionId, send_buffer.c_str(), send_buffer.length());
}

DDSCoordinatorServerProtocol::DDSCoordinatorServerProtocol(DDSCoordinatorState & coordinator_state, StormSockets::StormSocketConnectionId connection_id, uint32_t remote_ip) :
  m_CoordinatorState(coordinator_state),
  m_State(kHandshakeRequest), 
  m_ConnectionId(connection_id), 
  m_NodeId(0),
  m_ExpectedChallengeResponse(0),
  m_RemoteIp(remote_ip)
{

}

bool DDSCoordinatorServerProtocol::IsConnected() const
{
  return m_State == kConnected;
}

bool DDSCoordinatorServerProtocol::HandleMessage(const char * msg, int length)
{
  Hash hash = crc32begin();
  while (length > 0)
  {
    if (*msg == ' ')
    {
      break;
    }

    hash = crc32additive(hash, *msg);
    msg++;
  }

  hash = crc32end(hash);
  msg++;

  if (length == 0)
  {
    return false;
  }

  DDSCoordinatorProtocolMessageType type = DDSCoordinatorProtocolMessageType::kUnknown;
  if (StormReflGetEnumFromHash(type, hash) == false)
  {
    return false;
  }

  switch (m_State)
  {
  case kHandshakeRequest:
    DDSLog::LogVerbose("Got handshake request from %d", m_ConnectionId.GetIndex());
    if (type == DDSCoordinatorProtocolMessageType::kHandshakeRequest)
    {
      DDSCoordinatorHandshakeRequest request;
      if (StormReflParseJson(request, msg) == false)
      {
        return false;
      }

      if (request.m_Version != DDS_VERSION)
      {
        return false;
      }

      DDSCoordinatorHandshakeResponse response;
      response.m_ChallengeResponse = DDSCalculateChallengeResponse(request.m_Challenge);
      response.m_ChallengeRequest = DDSGetRandomNumber64();

      m_ExpectedChallengeResponse = DDSCalculateChallengeResponse(response.m_ChallengeRequest);
      m_State = kHandshakeFinalize;

      SendMessageToClient(response);
      return true;
    }
    else
    {
      return false;
    }
    break;
  case kHandshakeFinalize:
    DDSLog::LogVerbose("Got handshake finalize from %d", m_ConnectionId.GetIndex());
    if (type == DDSCoordinatorProtocolMessageType::kHandshakeFinalize)
    {
      DDSCoordinatorHandshakeFinalize finalize;
      if (StormReflParseJson(finalize, msg) == false)
      {
        return false;
      }

      if (m_ExpectedChallengeResponse != finalize.m_ChallengeResponse)
      {
        return false;
      }

      if (finalize.m_PublicIp == 0)
      {
        finalize.m_PublicIp = m_RemoteIp;
      }

      m_NodeId = m_CoordinatorState.CreateNode(finalize.m_PublicIp, finalize.m_NodePort, finalize.m_EndpointPorts, finalize.m_WebsitePorts);

      DDSCoordinatorNodeInitialization response;
      response.m_NodeId = m_NodeId;
      response.m_InitialNode = m_CoordinatorState.GetRoutingTable().m_Table.size() == 1;
      response.m_ClientSecret = m_CoordinatorState.GetClientSecret();
      response.m_ServerSecret = m_CoordinatorState.GetServerSecret();
      m_State = kConnected;

      SendMessageToClient(response);
      m_CoordinatorState.SyncRoutingTable();
      return true;
    }
    else
    {
      return false;
    }
    break;
  case kConnected:
    {
      m_CoordinatorState.GotMessageFromServer(m_NodeId, type, msg);
    }
    break;
  }

  return true;
}

bool DDSCoordinatorServerProtocol::CheckNodeId(DDSNodeId node_id) const
{
  return (m_State == kConnected && node_id == m_NodeId);
}

DDSNodeId DDSCoordinatorServerProtocol::GetNodeId() const
{
  return m_NodeId;
}