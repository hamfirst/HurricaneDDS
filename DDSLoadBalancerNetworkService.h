#pragma once

#include <map>
#include <memory>
#include <vector>

#include <StormSockets/StormSocketServerTypes.h>

#include "DDSNodeId.h"
#include "DDSNetworkBackend.h"
#include "DDSRoutingTable.h"

class DDSCoordinatorState;

namespace StormSockets
{
  class StormSocketServerFrontendWebsocket;
  class StormWebsocketMessageReader;
}

class DDSNetworkBackend;
class DDSCoordinatorServerProtocol;

class DDSLoadBalancerNetworkService
{
public:
  DDSLoadBalancerNetworkService(
    DDSNetworkBackend & backend,
    DDSCoordinatorState & coordinator_state,
    const StormSockets::StormSocketServerFrontendWebsocketSettings & server_settings,
    int endpoint_id);

  void ProcessEvents();

  void UpdateRoutingTable(const DDSRoutingTable & routing_table);
  void UpdateNode(DDSNodeId node_id, float cpu);
  void SyncNodeList();

protected:

  std::string GetNodeListMessage();

private:

  StormSockets::StormSemaphore m_Semaphore;


  DDSCoordinatorState & m_CoordinatorState;
  DDSNetworkBackend & m_Backend;
  DDSRoutingTable m_RoutingTable;
  int m_EndpointId;

  std::map<DDSNodeId, float> m_CpuUsage;

  std::unique_ptr<StormSockets::StormSocketServerFrontendWebsocket> m_ServerFrontend;
  std::vector<StormSockets::StormSocketConnectionId> m_ConnectionIds;
};

