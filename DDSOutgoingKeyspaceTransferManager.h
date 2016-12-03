#pragma once

#include <vector>

#include "DDSOutgoingKeyspaceTransfer.h"

class DDSNodeState;

class DDSOutgoingKeyspaceTransferManager
{
public:
  DDSOutgoingKeyspaceTransferManager(DDSNodeState & node_state, int num_object_types);

  void ProcessNewRoutingTable(const DDSRoutingTable & new_routing_table, DDSKeyRange original_key_range, DDSNodeId local_node_id);
  void ProcessDefunctRoutingTable(const DDSRoutingTable & new_routing_table, DDSKeyRange original_key_range);

  void Update();
  bool IsComplete();

private:

  DDSNodeState & m_NodeState;
  int m_NumObjectTypes;

  std::vector<DDSOutgoingKeyspaceTransfer> m_PendingTransfers;
};

