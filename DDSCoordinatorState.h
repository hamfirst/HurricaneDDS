#pragma once

#include "DDSRoutingTable.h"
#include "DDSCoordinatorNetworkService.h"

class DDSCoordinatorState
{
public:
  DDSCoordinatorState(const StormSockets::StormSocketInitSettings & backend_settings,
    const StormSockets::StormSocketServerFrontendWebsocketSettings & server_settings);

  void ProcessEvents();
  void SyncRoutingTable();

  DDSCoordinatorNetworkService & GetNetworkService();
  const DDSRoutingTable & GetRoutingTable() const;

  DDSNodeId CreateNode(uint32_t addr, uint16_t port);
  void DestroyNode(DDSNodeId id);

  uint64_t GetClientSecret() const;
  uint64_t GetServerSecret() const;

private:

  DDSCoordinatorNetworkService m_NetworkService;

  DDSRoutingTable m_RoutingTable;
  DDSNodeId m_NextNodeId;

  uint64_t m_ClientSecret;
  uint64_t m_ServerSecret;
};
