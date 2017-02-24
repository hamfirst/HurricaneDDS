
#include "DDSVersion.h"
#include "DDSLog.h"
#include "DDSRandom.h"
#include "DDSChallenge.h"
#include "DDSServerToServerReceiver.h"
#include "DDSNodeState.h"
#include "DDSServerMessage.h"
#include "DDSNodeNetworkService.h"
#include "DDSNetworkBackend.h"
#include "DDSServerToServerMessages.refl.meta.h"

#include <StormSockets/StormSocketBackend.h>
#include <StormSockets/StormSocketClientFrontendWebsocket.h>

#include <StormRefl/StormReflJson.h>

DDSServerToServerReceiver::DDSServerToServerReceiver(DDSNodeState & node_state,
                                                     StormSockets::StormSocketConnectionId connection_id) :
  m_NodeState(node_state),
  m_State(kHandshakeRequest),
  m_ConnectionId(connection_id),
  m_NodeId(0)
{

}

bool DDSServerToServerReceiver::HandleIncomingMessage(StormSockets::StormWebsocketMessageReader & message_reader)
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
  case kHandshakeRequest:
  {
    if (type != DDSServerToServerMessageType::kHandshakeRequest)
    {
      return false;
    }

    DDSServerToServerHandshakeRequest request;
    if (StormReflParseJson(request, msg) == false)
    {
      return false;
    }

    if (request.m_Version != DDS_VERSION)
    {
      return false;
    }

    if (request.m_Secret != m_NodeState.m_ClientSecret)
    {
      return false;
    }

    m_NodeId = request.m_NodeId;

    DDSServerToServerHandshakeResponse response;
    response.m_Challenge = DDSGetRandomNumber64();
    response.m_Secret = m_NodeState.m_ServerSecret;
    response.m_NodeId = m_NodeState.m_LocalNodeId.value();
    response.m_ChallengeResponse = DDSCalculateChallengeResponse(request.m_Challenge);

    m_ExpectedChallengeResponse = DDSCalculateChallengeResponse(response.m_Challenge);

    std::string message = DDSGetServerMessage(response);
    SendMessageToServer(message);

    m_State = kHandshakeFinalize;
  }
  break;
  case kHandshakeFinalize:
  {
    if (type != DDSServerToServerMessageType::kHandshakeFinalize)
    {
      return false;
    }

    DDSServerToServerHandshakeFinalize finalize;
    if (StormReflParseJson(finalize, msg) == false)
    {
      return false;
    }

    if (finalize.m_Challenge != m_ExpectedChallengeResponse)
    {
      return false;
    }

    m_State = kConnected;

    DDSLog::LogInfo("Receiver %d established connection to node %d", m_ConnectionId.GetIndex(), m_NodeId);
    return true;
  }
  break;
  case kConnected:
  {
    m_NodeState.GotMessageFromServer(m_NodeId, type, msg);
    return true;
  }
  break;
  }

  return false;
}

bool DDSServerToServerReceiver::IsConnected() const
{
  return m_State == kConnected;
}

void DDSServerToServerReceiver::SendMessageToServer(const std::string & message)
{
  StormSockets::StormSocketBackend * backend = m_NodeState.m_Backend.m_Backend.get();
  StormSockets::StormSocketClientFrontendWebsocket * frontend = m_NodeState.m_NodeNetwork.m_ClientFrontend.get();

  auto writer = frontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Binary, true);
  writer.WriteByteBlock(message.c_str(), 0, message.length());
  frontend->FinalizeOutgoingPacket(writer);
  backend->SendPacketToConnectionBlocking(writer, m_ConnectionId);
  backend->FreeOutgoingPacket(writer);
}
