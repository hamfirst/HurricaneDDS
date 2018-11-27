#pragma once

#include <vector>
#include <memory>

#include "DDSKey.h"
#include "DDSNodeId.h"
#include "DDSRoutingTable.h"

class DDSNodeState;

class DDSOutgoingKeyspaceTransfer
{
public:
  DDSOutgoingKeyspaceTransfer(DDSNodeId local_node_id, int num_object_types, int table_gen, 
    const std::vector<std::pair<DDSNodeId, DDSKeyRange>> & output_keyranges, const std::shared_ptr<std::string> & slc_transfer_packet);
  DDSOutgoingKeyspaceTransfer(DDSOutgoingKeyspaceTransfer && rhs) = default;

  DDSOutgoingKeyspaceTransfer & operator = (DDSOutgoingKeyspaceTransfer && rhs) = default;

  bool IsReady(DDSNodeState & node_state);
  bool Send(DDSNodeState & node_state);

private:

  struct TransferInfo
  {
    DDSNodeId m_NodeId;
    int m_ObjectType;
    DDSKeyRange m_KeyRange;
  };


  int m_NumObjectTypes;
  int m_TableGen;

  bool m_TransferBegun;

  std::shared_ptr<std::string> m_SLCTransferPacket;

  std::vector<DDSKeyRange> m_PendingKeyRanges;
  std::vector<TransferInfo> m_PendingTransfers;
  std::vector<DDSNodeId> m_PendingSharedLocalCopyTransfers;
};
