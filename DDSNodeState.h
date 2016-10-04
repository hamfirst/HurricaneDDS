#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>

#include "DDSNodeId.h"
#include "DDSDataObjectAddress.h"
#include "DDSDataObjectStoreBase.h"
#include "DDSRoutingTable.h"
#include "DDSNetworkBackend.h"
#include "DDSNodeNetworkService.h"
#include "DDSCoordinatorClientProtocol.h"
#include "DDSDatabaseConnectionPool.h"
#include "DDSIncomingKeyspaceTransferManager.h"
#include "DDSOutgoingKeyspaceTransferManager.h"
#include "DDSServerToServerMessages.refl.h"

class DDSNodeState
{
public:

  template <class TypeList>
  DDSNodeState(
    const TypeList & type_list,
    const StormSockets::StormSocketInitSettings & backend_settings,
    const StormSockets::StormSocketServerFrontendWebsocketSettings & node_server_settings,
    const StormSockets::StormSocketClientFrontendWebsocketSettings & node_client_settings,
    const DDSCoordinatorClientSettings & coordinator_settings) :
    DDSNodeState(TypeList::NumTypes, backend_settings, node_server_settings, node_client_settings, coordinator_settings)
  {
    auto func = type_list();
    func(*this, m_DataObjectList);
  }

  void ProcessEvents();
  void GotInitialCoordinatorSync(DDSNodeId node_id, const DDSRoutingTable & routing_table, bool initial_node, uint64_t server_secret, uint64_t client_secret);
  void GotNewRoutingTable(const DDSRoutingTable & routing_table);
  void GotMessageFromServer(DDSNodeId node_id, DDSServerToServerMessageType type, const char * data);

  void SendTargetedMessage(DDSDataObjectAddress addr, std::string && message);
  DDSNodeId GetNodeIdForKey(DDSKey key) const;

  DDSDataObjectStoreBase & GetDataObjectStore(int object_type_id);

  DDSNetworkBackend & GetBackend();
  DDSNodeNetworkService & GetNodeNetwork();
  DDSCoordinatorClientProtocol & GetCoordinatorConnection();

  DDSIncomingKeyspaceTransferManager & GetIncomingKeyspace();
  DDSOutgoingKeyspaceTransferManager & GetOutgoingKeyspace();

  DDSNodeId GetLocalNodeId() const;
  const DDSRoutingTable & GetRoutingTable() const;
  DDSKeyRange GetLocalKeyRange() const;

  uint64_t GetClientSecret() const;
  uint64_t GetServerSecret() const;

  uint32_t GetLocalInterface() const;
  int GetLocalPort() const;

private:

  DDSNodeState(
    int num_data_object_types,
    const StormSockets::StormSocketInitSettings & backend_settings,
    const StormSockets::StormSocketServerFrontendWebsocketSettings & node_server_settings,
    const StormSockets::StormSocketClientFrontendWebsocketSettings & node_client_settings,
    const DDSCoordinatorClientSettings & coordinator_settings);

  void RecheckOutgoingTargetedMessages();

  void HandleIncomingTargetedMessage(DDSDataObjectAddress addr, std::string & message);

  DDSNetworkBackend m_Backend;
  DDSNodeNetworkService m_NodeNetwork;
  DDSCoordinatorClientProtocol m_CoordinatorConnection;

  DDSIncomingKeyspaceTransferManager m_IncomingKeyspace;
  DDSOutgoingKeyspaceTransferManager m_OutgoingKeyspace;

  DDSNodeId m_LocalNodeId = 0;
  DDSRoutingTable m_RoutingTable;
  DDSKeyRange m_LocalKeyRange;
  std::vector<std::pair<DDSNodeId, DDSKeyRange>> m_RoutingKeyRanges;

  std::map<DDSDataObjectAddress, std::vector<std::string>> m_PendingTargetedMessages;

  std::vector<std::unique_ptr<DDSDataObjectStoreBase>> m_DataObjectList;

  uint32_t m_LocalInterface = 0;
  int m_LocalPort = 0;

  uint64_t m_ClientSecret = 0;
  uint64_t m_ServerSecret = 0;
};

