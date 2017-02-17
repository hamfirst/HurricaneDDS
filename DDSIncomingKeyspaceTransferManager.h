#pragma once

#include <vector>

#include "DDSIncomingKeyspaceTransfer.h"
#include "DDSDataObjectAddress.h"


class DDSIncomingKeyspaceTransferManager
{
public:
  DDSIncomingKeyspaceTransferManager(int num_object_types);

  void InitializeSingleNode();
  void InitializeUnsyncedKeyspace(int table_gen, DDSKeyRange key_range);

  void ProcessNewRoutingTable(const DDSRoutingTable & new_routing_table, const DDSRoutingTable & old_routing_table, DDSKeyRange new_key_range, DDSNodeId local_node_id);
  bool SetKeyRangeComplete(int table_gen, int object_type, DDSKeyRange key_range);

  bool IsReadyForOutgoingKeyspaceTransfer(int table_gen) const;
  bool IsComplete() const;

private:

  bool m_Initialized;
  int m_NumObjectTypes;

  std::vector<DDSIncomingKeyspaceTransfer> m_PendingTransfers;
};

