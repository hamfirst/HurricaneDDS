#pragma once

#include <map>
#include <vector>
#include <memory>

#include <StormSockets\StormSocketServerTypes.h>

#include "DDSNodeId.h"
#include "DDSServerToServerSender.h"
#include "DDSServerToServerReceiver.h"

namespace StormSockets
{
  class StormSocketServerFrontendWebsocket;
  class StormSocketClientFrontendWebsocket;
}

class DDSNodeState;

class DDSNodeNetworkService
{
public:
  DDSNodeNetworkService(DDSNodeState & node_state,
                        const StormSockets::StormSocketServerFrontendWebsocketSettings & server_settings,
                        const StormSockets::StormSocketClientFrontendWebsocketSettings & client_settings);

  void ProcessEvents();
  void SendMessageToServer(DDSNodeId node_id, std::string && data);

  bool RequestNodeConnection(DDSNodeId node_id); // Returns true if the node is already connected

protected:

  void NodeConnectionReady(DDSNodeId id, DDSServerToServerSender & sender);
  void CreateNodeConnection(DDSNodeId id);

private:
  friend class DDSServerToServerSender;
  friend class DDSServerToServerReceiver;

  DDSNodeState & m_NodeState;

  std::unique_ptr<StormSockets::StormSocketClientFrontendWebsocket> m_ClientFrontend;
  std::unique_ptr<StormSockets::StormSocketServerFrontendWebsocket> m_ServerFrontend;

  std::map<StormSockets::StormSocketConnectionId, DDSServerToServerSender> m_Senders;
  std::map<StormSockets::StormSocketConnectionId, DDSServerToServerReceiver> m_Receievers;

  std::map<DDSNodeId, StormSockets::StormSocketConnectionId> m_NodeConnectionMap;
  std::map<DDSNodeId, std::vector<std::string>> m_PendingMessages;
};

