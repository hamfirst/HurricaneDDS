#pragma once

#include <vector>

#include "DDSKey.h"
#include "DDSNodeId.h"
#include "DDSRoutingTable.h"

class DDSNodeState;

class DDSOutgoingKeyspaceTransfer
{
public:
  DDSOutgoingKeyspaceTransfer(DDSNodeId local_node_id, int num_object_types, int table_gen, const std::vector<std::pair<DDSNodeId, DDSKeyRange>> & output_keyranges);
  DDSOutgoingKeyspaceTransfer(DDSOutgoingKeyspaceTransfer && rhs) = default;

  DDSOutgoingKeyspaceTransfer & operator = (DDSOutgoingKeyspaceTransfer && rhs) = default;

  bool IsReady(DDSNodeState & node_state);
  bool Send(DDSNodeState & node_state);

private:

  int m_NumObjectTypes;
  int m_TableGen;

  bool m_TransferBegun;

  std::vector<DDSKeyRange> m_PendingKeyRanges;
  std::vector<std::tuple<DDSNodeId, int, DDSKeyRange>> m_PendingTransfers;
};
