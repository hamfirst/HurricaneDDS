
#include "DDSLog.h"
#include "DDSRandom.h"
#include "DDSVersion.h"
#include "DDSChallenge.h"
#include "DDSNodeState.h"
#include "DDSServerMessage.h"
#include "DDSCoordinatorClientProtocol.h"
#include "DDSCoordinatorProtocolMessages.refl.meta.h"
#include "DDSRoutingTable.refl.meta.h"

#include <hash/Hash.h>
#include <StormRefl/StormReflJson.h>
#include <StormRefl/StormReflMetaEnum.h>

#include <StormSockets/StormSocketClientFrontendWebsocket.h>

template <class T>
void DDSCoordinatorClientProtocol::SendMessageToServer(const T & t)
{
  std::string send_buffer = DDSGetServerMessage(t);

  auto writer = m_ClientFrontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Text, true);
  writer.WriteByteBlock(send_buffer.data(), 0, send_buffer.size());
  m_ClientFrontend->FinalizeOutgoingPacket(writer);
  m_ClientFrontend->SendPacketToConnection(writer, m_ConnectionId);
  m_ClientFrontend->FreeOutgoingPacket(writer);
}

DDSCoordinatorClientProtocol::~DDSCoordinatorClientProtocol()
{

}

DDSCoordinatorClientProtocol::DDSCoordinatorClientProtocol(DDSNodeState & node_state, const DDSCoordinatorClientSettings & settings) :
  m_NodeState(node_state),
  m_State(kDisconnected),
  m_ExpectedChallengeResponse(0)
{
  StormSockets::StormSocketClientFrontendWebsocketSettings client_settings;
  client_settings.MaxConnections = 4;

  m_ClientFrontend = std::make_unique<StormSockets::StormSocketClientFrontendWebsocket>(client_settings, m_NodeState.GetBackend().m_Backend.get());

  m_CoordinatorIpAddr = settings.CoordinatorIpAddr;
  m_CoordinatorPort = settings.CoordinatorPort;
}

void DDSCoordinatorClientProtocol::ProcessEvents()
{
  StormSockets::StormSocketEventInfo event;
  while (m_ClientFrontend->GetEvent(event))
  {
    switch (event.Type)
    {
    case StormSockets::StormSocketEventType::ClientConnected:
      DDSLog::LogInfo("Coordinator websocket connected");
      break;
    case StormSockets::StormSocketEventType::ClientHandShakeCompleted:
      HandleConnectionEstablished();
      DDSLog::LogInfo("Connected to coordinator");
      break;
    case StormSockets::StormSocketEventType::Data:
      m_MessageBuffer.resize(event.GetWebsocketReader().GetDataLength() + 1);
      event.GetWebsocketReader().ReadByteBlock(m_MessageBuffer.data(), event.GetWebsocketReader().GetDataLength());
      m_MessageBuffer[event.GetWebsocketReader().GetDataLength()] = 0;

      if (HandleMessage(m_MessageBuffer.data(), event.GetWebsocketReader().GetDataLength()) == false)
      {
        DDSLog::LogError("Could not process message data from state %d: %s", m_State, m_MessageBuffer.data());
      }
      break;
    case StormSockets::StormSocketEventType::Disconnected:
      if (m_State == kConnecting)
      {
        m_ClientFrontend->FinalizeConnection(event.ConnectionId);
        RequestConnect();
      }
      else
      {
        DDSLog::LogError("Disconnected from coordinator...panic!");
      }
      break;
    }
  }
}

void DDSCoordinatorClientProtocol::RequestConnect()
{
  DDSLog::LogInfo("Requesting connect to coordinator");
  m_ConnectionId = m_ClientFrontend->RequestConnect(m_CoordinatorIpAddr.c_str(), m_CoordinatorPort, StormSockets::StormSocketClientFrontendWebsocketRequestData{});
  m_State = kConnecting;
}

bool DDSCoordinatorClientProtocol::HandleConnectionEstablished()
{
  DDSCoordinatorHandshakeRequest request;
  request.m_Version = DDS_VERSION;
  request.m_Challenge = DDSGetRandomNumber64();

  m_ExpectedChallengeResponse = DDSCalculateChallengeResponse(request.m_Challenge);
  SendMessageToServer(request);

  m_State = kHandshakeResponse;
  return true;
}

bool DDSCoordinatorClientProtocol::HandleMessage(const char * msg, int length)
{
  const char * start_msg = msg;

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

  DDSCoordinatorProtocolMessageType type = DDSCoordinatorProtocolMessageType::kUnknown;
  if (StormReflGetEnumFromHash(type, hash) == false)
  {
    return false;
  }

  switch (m_State)
  {
  case kConnecting:
    break;
  case kHandshakeResponse:
    if (type == DDSCoordinatorProtocolMessageType::kHandshakeResponse)
    {
      DDSCoordinatorHandshakeResponse response;
      if (StormReflParseJson(response, msg) == false)
      {
        return false;
      }

      if (response.m_ChallengeResponse != m_ExpectedChallengeResponse)
      {
        return false;
      }

      DDSCoordinatorHandshakeFinalize finalize;
      finalize.m_ChallengeResponse = DDSCalculateChallengeResponse(response.m_ChallengeRequest);
      finalize.m_PublicIp = m_NodeState.GetLocalInterface();
      finalize.m_NodePort = m_NodeState.GetLocalPort();
      m_NodeState.GetConnectionFactoryPorts(finalize.m_EndpointPorts, finalize.m_WebsitePorts);

      m_State = kNodeInit;

      SendMessageToServer(finalize);
      return true;
    }
    else
    {
      return false;
    }
    break;
  case kNodeInit:
    if (type == DDSCoordinatorProtocolMessageType::kNodeInit)
    {
      DDSCoordinatorNodeInitialization response;
      if (StormReflParseJson(response, msg) == false)
      {
        return false;
      }

      m_NodeId = response.m_NodeId;
      m_InitialNode = response.m_InitialNode;
      m_ClientSecret = response.m_ClientSecret;
      m_ServerSecret = response.m_ServerSecret;
      m_NetworkTime = response.m_NetworkTime - time(nullptr);
      m_State = kRoutingTableInit;
      return true;
    }
    else
    {
      return false;
    }
    break;
  case kRoutingTableInit:
    if (type == DDSCoordinatorProtocolMessageType::kRoutingTable)
    {
      DDSRoutingTable table;
      if (StormReflParseJson(table, msg) == false)
      {
        return false;
      }

      m_State = kConnected;
      m_NodeState.GotInitialCoordinatorSync(m_NodeId, table, m_InitialNode, m_ServerSecret, m_ClientSecret);
      return true;
    }
    else
    {
      return false;
    }
    break;
  case kConnected:
    if (type == DDSCoordinatorProtocolMessageType::kRoutingTable)
    {
      DDSRoutingTable table;
      if (StormReflParseJson(table, msg) == false)
      {
        return false;
      }

      m_NodeState.GotNewRoutingTable(table);
      return true;
    }
    else if (type == DDSCoordinatorProtocolMessageType::kSharedObjectDelta)
    {
      m_NodeState.HandleSharedObjectDelta(msg);
      return true;
    }
    else
    {
      msg = start_msg;
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

      DDSServerToServerMessageType server_type;
      if (StormReflGetEnumFromHash(server_type, hash) == false)
      {
        return false;
      }

      m_NodeState.GotMessageFromCoordinator(server_type, type, msg);
    }
    break;

  case kDisconnected:
    break;
  }

  return true;
}

void DDSCoordinatorClientProtocol::SendMessageToCoordinator(const std::string && data)
{
  if (m_State != kConnected)
  {
    DDSLog::LogError("Attempting to send data on an unconnected connection");
    return;
  }

  auto writer = m_ClientFrontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Text, true);
  writer.WriteByteBlock(data.data(), 0, data.size());
  m_ClientFrontend->FinalizeOutgoingPacket(writer);
  m_ClientFrontend->SendPacketToConnection(writer, m_ConnectionId);
  m_ClientFrontend->FreeOutgoingPacket(writer);
}

time_t DDSCoordinatorClientProtocol::GetNetworkTime()
{
  return m_NetworkTime + time(nullptr);
}

bool DDSCoordinatorClientProtocol::ShutDown()
{
  if (m_State >= kHandshakeResponse)
  {
    DDSLog::LogInfo("Beginning node shutdown");
    DDSCoordinatorNodeShutdown shutdown{};
    SendMessageToServer(shutdown);

    return false;
  }
  else
  {
    Disconnect();
    return true;
  }
}

void DDSCoordinatorClientProtocol::Disconnect()
{
  if (m_State != kDisconnected)
  {
    m_ClientFrontend->ForceDisconnect(m_ConnectionId);
    m_State = kDisconnected;
  }
}