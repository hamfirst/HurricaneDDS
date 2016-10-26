
#include "DDSVersion.h"
#include "DDSRandom.h"
#include "DDSChallenge.h"
#include "DDSServerToServerSender.h"
#include "DDSNodeState.h"
#include "DDSServerMessage.h"
#include "DDSNodeNetworkService.h"
#include "DDSNetworkBackend.h"
#include "DDSServerToServerMessages.refl.meta.h"

#include <StormSockets/StormSocketBackend.h>
#include <StormSockets/StormSocketClientFrontendWebsocket.h>

#include <StormRefl/StormReflJson.h>

DDSServerToServerSender::DDSServerToServerSender(DDSNodeState & node_state, 
                                                 StormSockets::StormSocketConnectionId connection_id, 
                                                 DDSNodeId target_node_id) :
  m_NodeState(node_state), 
  m_State(kHandshake),
  m_ConnectionId(connection_id), 
  m_TargetNodeId(target_node_id)
{

}

void DDSServerToServerSender::HandleConnectionEstablished()
{
  DDSServerToServerHandshakeRequest request;
  request.m_NodeId = m_NodeState.GetLocalNodeId();
  request.m_Version = DDS_VERSION;
  request.m_Challenge = DDSGetRandomNumber64();
  request.m_Secret = m_NodeState.GetClientSecret();
  std::string message = DDSGetServerMessage(request);

  SendMessageToServer(message);

  m_ExpectedChallengeResponse = DDSCalculateChallengeResponse(request.m_Challenge);
}

bool DDSServerToServerSender::HandleIncomingMessage(StormSockets::StormWebsocketMessageReader & message_reader)
{
  m_RecvBuffer.resize(message_reader.GetDataLength() + 1);
  message_reader.ReadByteBlock(m_RecvBuffer.data(), message_reader.GetDataLength());
  m_RecvBuffer[message_reader.GetDataLength()] = 0;

  std::size_t length = message_reader.GetDataLength();
  char * msg = m_RecvBuffer.data();

  Hash hash = crc32begin();
  while (length > 0)
  {
    if (*msg == ' ' || *msg == 0)
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

  DDSServerToServerMessageType type;
  if (StormReflGetEnumFromHash(type, hash) == false)
  {
    return false;
  }

  switch (m_State)
  {
  case kConnecting:
  break;
  case kHandshake:
  {
    DDSServerToServerHandshakeResponse response;
    if (StormReflParseJson(response, msg) == false)
    {
      return false;
    }

    if (response.m_ChallengeResponse != m_ExpectedChallengeResponse)
    {
      return false;
    }

    if (response.m_Secret != m_NodeState.GetServerSecret())
    {
      return false;
    }

    if (response.m_NodeId != m_TargetNodeId)
    {
      return false;
    }

    DDSServerToServerHandshakeFinalize finalize;
    finalize.m_Challenge = DDSCalculateChallengeResponse(response.m_Challenge);

    std::string message = DDSGetServerMessage(finalize);
    SendMessageToServer(message);

    m_State = kConnected;

    m_NodeState.GetNodeNetwork().NodeConnectionReady(m_TargetNodeId, *this);
    return true;
  }
  break;
  case kConnected:
  {
    return false;
  }
  break;
  }

  return false;
}

bool DDSServerToServerSender::IsConnected() const
{
  return m_State == kConnected;
}

DDSNodeId DDSServerToServerSender::GetTargetNodeId() const
{
  return m_TargetNodeId;
}

void DDSServerToServerSender::SendMessageToServer(const std::string & message)
{
  StormSockets::StormSocketBackend * backend = m_NodeState.GetBackend().m_Backend.get();
  StormSockets::StormSocketClientFrontendWebsocket * frontend = m_NodeState.GetNodeNetwork().m_ClientFrontend.get();

  auto writer = frontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Binary, true);
  writer.WriteByteBlock(message.c_str(), 0, message.length());
  frontend->FinalizeOutgoingPacket(writer);
  backend->SendPacketToConnectionBlocking(writer, m_ConnectionId);
  backend->FreeOutgoingPacket(writer);
}
