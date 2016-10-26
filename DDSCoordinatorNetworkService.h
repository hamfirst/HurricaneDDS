#pragma once

#include <map>
#include <memory>
#include <vector>

#include <StormSockets/StormSocketServerTypes.h>

#include "DDSNodeId.h"
#include "DDSNetworkBackend.h"

class DDSCoordinatorState;

namespace StormSockets
{
  class StormSocketServerFrontendWebsocket;
  class StormWebsocketMessageReader;
}

class DDSNetworkBackend;
class DDSCoordinatorServerProtocol;

class DDSCoordinatorNetworkService
{
public:
  DDSCoordinatorNetworkService(
    DDSNetworkBackend & backend,
    DDSCoordinatorState & coordinator_state,
    const StormSockets::StormSocketServerFrontendWebsocketSettings & server_settings);

  void WaitForEvent();
  void ProcessEvents();

  void SendMessageToClient(StormSockets::StormSocketConnectionId connection_id, const char * message, std::size_t length);
  void SendMessageToAllConnectedClients(const char * message, std::size_t length);
  bool SendMessageToNode(DDSNodeId node_id, const char * message, std::size_t length);

protected:

  void HandleConnect(StormSockets::StormSocketConnectionId connection_id, uint32_t addr, uint16_t port);
  void HandleData(StormSockets::StormSocketConnectionId connection_id, StormSockets::StormWebsocketMessageReader & reader);

private:
  DDSCoordinatorState & m_CoordinatorState;
  DDSNetworkBackend & m_Backend;

  std::vector<char> m_RecvBuffer;

  std::unique_ptr<StormSockets::StormSocketServerFrontendWebsocket> m_ServerFrontend;
  std::map<StormSockets::StormSocketConnectionId, std::unique_ptr<DDSCoordinatorServerProtocol>> m_ConnectionIdMap;
};

