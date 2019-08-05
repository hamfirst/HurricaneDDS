
#include "DDSLoadBalancer.h"
#include "DDSLoadBalancerMessages.refl.meta.h"

#include <StormRefl/StormReflJsonStd.h>

#include <StormSockets/StormSocketServerFrontendWebsocket.h>
#include <StormSockets/StormSocketClientFrontendWebsocket.h>

DDSLoadBalancer::DDSLoadBalancer(
  const StormSockets::StormSocketInitSettings & backend_settings,
  const StormSockets::StormSocketServerFrontendWebsocketSettings & server_settings,
  const DDSLoadBalancerSettings & lb_settings) :
  m_State(kReconnectWait),
  m_Backend(backend_settings),
  m_Frontend(std::make_unique<StormSockets::StormSocketServerFrontendWebsocket>(server_settings, m_Backend.m_Backend.get())),
  m_CoordinatorHost(lb_settings.CoordinatorIpAddr),
  m_CoordinatorProtocol(lb_settings.CoordinatorProtocol ? lb_settings.CoordinatorProtocol : ""),
  m_CoordinatorPort(lb_settings.CoordinatorPort),
  m_LastConnect(time(nullptr))
{
  StormSockets::StormSocketClientFrontendWebsocketSettings client_settings;
  client_settings.MaxConnections = 4;

  m_Client = std::make_unique<StormSockets::StormSocketClientFrontendWebsocket>(client_settings, m_Backend.m_Backend.get());
}

DDSLoadBalancer::~DDSLoadBalancer()
{

}

void DDSLoadBalancer::ProcessEvents()
{
  if (m_State == kReconnectWait)
  {
    if (time(nullptr) - m_LastConnect >= 5)
    {
      StormSockets::StormSocketClientFrontendWebsocketRequestData request;
      request.m_Protocol = m_CoordinatorProtocol.empty() ? nullptr : m_CoordinatorProtocol.c_str();

      m_Client->RequestConnect(m_CoordinatorHost.c_str(), m_CoordinatorPort, request);
      m_LastConnect = time(nullptr);
      m_State = kConnecting;
    }    
  }

  if (m_State == kConnecting || m_State == kWaitingForInitialSync)
  {
    StormSockets::StormSocketEventInfo event;
    while (m_Client->GetEvent(event))
    {
      if (event.Type == StormSockets::StormSocketEventType::ClientHandShakeCompleted)
      {
        m_State = kWaitingForInitialSync;
      }

      if (event.Type == StormSockets::StormSocketEventType::Data)
      {
        m_State = kReady;

        m_RecvBuffer.resize(event.GetWebsocketReader().GetDataLength() + 1);
        event.GetWebsocketReader().ReadByteBlock(m_RecvBuffer.data(), event.GetWebsocketReader().GetDataLength());
        m_RecvBuffer[event.GetWebsocketReader().GetDataLength()] = 0;

        StormReflParseJson(m_NodeList, m_RecvBuffer.data());
        m_Client->FreeIncomingPacket(event.GetWebsocketReader());
        break;
      }

      if (event.Type == StormSockets::StormSocketEventType::Disconnected)
      {
        m_State = kReconnectWait;
        m_Client->FinalizeConnection(event.ConnectionId);
      }
    }
  }

  if (m_State == kReady)
  {
    StormSockets::StormSocketEventInfo event;
    while (m_Client->GetEvent(event))
    {
      if (event.Type == StormSockets::StormSocketEventType::Data)
      {
        m_RecvBuffer.resize(event.GetWebsocketReader().GetDataLength() + 1);
        event.GetWebsocketReader().ReadByteBlock(m_RecvBuffer.data(), event.GetWebsocketReader().GetDataLength());
        m_RecvBuffer[event.GetWebsocketReader().GetDataLength()] = 0;

        StormReflParseJson(m_NodeList, m_RecvBuffer.data());
        m_Client->FreeIncomingPacket(event.GetWebsocketReader());
        break;
      }

      if (event.Type == StormSockets::StormSocketEventType::Disconnected)
      {
        m_State = kReconnectWait;
        m_Client->FinalizeConnection(event.ConnectionId);
      }
    }

    while (m_Frontend->GetEvent(event))
    {
      if (event.Type == StormSockets::StormSocketEventType::ClientHandShakeCompleted)
      {
        if (m_NodeList.m_Nodes.size() > 0)
        {
          auto search_func = [](auto & a, auto & b) { return a.m_Cpu < b.m_Cpu; };
          auto itr = std::min_element(m_NodeList.m_Nodes.begin(), m_NodeList.m_Nodes.end(), search_func);

          DDSLoadBalancerResponse resp;
          resp.host = itr->m_IpAddr;
          resp.port = itr->m_Port;

          auto writer = m_Frontend->CreateOutgoingPacket(StormSockets::StormSocketWebsocketDataType::Text, true);
          writer.WriteString(StormReflEncodeJson(resp).c_str());
          m_Frontend->FinalizeOutgoingPacket(writer);

          m_Frontend->SendPacketToConnection(writer, event.ConnectionId);
          m_Frontend->FreeOutgoingPacket(writer);

          itr->m_Cpu++;
        }

        m_Frontend->ForceDisconnect(event.ConnectionId);
      }

      if (event.Type == StormSockets::StormSocketEventType::Disconnected)
      {
        m_Frontend->FinalizeConnection(event.ConnectionId);
      }
    }
  }
  else
  {
    StormSockets::StormSocketEventInfo event;
    while (m_Frontend->GetEvent(event))
    {
      if (event.Type == StormSockets::StormSocketEventType::ClientHandShakeCompleted)
      {
        m_Frontend->ForceDisconnect(event.ConnectionId);
      }

      if (event.Type == StormSockets::StormSocketEventType::Disconnected)
      {
        m_Frontend->FinalizeConnection(event.ConnectionId);
      }
    }
  }
}

