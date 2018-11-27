
#include <tuple>

#include "DDSLog.h"
#include "DDSOutgoingKeyspaceTransfer.h"
#include "DDSIncomingKeyspaceTransferManager.h"
#include "DDSNodeState.h"
#include "DDSServerMessage.h"
#include "DDSServerToServerMessages.refl.meta.h"

#include <StormRefl/StormReflJsonStd.h>

#include <sb/vector.h>

DDSOutgoingKeyspaceTransfer::DDSOutgoingKeyspaceTransfer(DDSNodeId local_node_id, int num_object_types, int table_gen, 
  const std::vector<std::pair<DDSNodeId, DDSKeyRange>> & output_keyranges, const std::shared_ptr<std::string> & slc_transfer_packet) :
  m_NumObjectTypes(num_object_types), 
  m_TableGen(table_gen), 
  m_TransferBegun(false),
  m_SLCTransferPacket(slc_transfer_packet)
{
  for (auto & val : output_keyranges)
  {
    DDSLog::LogVerbose("Transfering %llX - %llX to node %d from node %d", val.second.m_Min, val.second.m_Max, val.first, local_node_id);

    m_PendingSharedLocalCopyTransfers.emplace_back(val.first);
    m_PendingKeyRanges.emplace_back(val.second);

    for (int index = 0; index < num_object_types; index++)
    {
      m_PendingTransfers.emplace_back(TransferInfo{ val.first, index, val.second });
    }
  }
}

bool DDSOutgoingKeyspaceTransfer::IsReady(DDSNodeState & node_state)
{
  if (m_TransferBegun)
  {
    return true;
  }

  if (node_state.m_IncomingKeyspace.IsReadyForOutgoingKeyspaceTransfer(m_TableGen) == false)
  {
    return false;
  }

  m_TransferBegun = true;

  for (auto & key_range : m_PendingKeyRanges)
  {
    node_state.PrepareObjectsForMove(key_range);
  }

  return false;
}

bool DDSOutgoingKeyspaceTransfer::Send(DDSNodeState & node_state)
{
  for (std::size_t index = 0; index < m_PendingTransfers.size(); index++)
  {
    auto & transfer = m_PendingTransfers[index];

    if (node_state.m_NodeNetwork.RequestNodeConnection(transfer.m_NodeId) == false)
    {
      continue;
    }

    for (std::size_t slc = 0; slc < m_PendingSharedLocalCopyTransfers.size(); slc++)
    {
      node_state.m_NodeNetwork.SendMessageToServer(transfer.m_NodeId, DDSServerToServerMessageType::kSharedLocalCopyDatabaseDump, *m_SLCTransferPacket.get());
      vremove_index_quick(m_PendingSharedLocalCopyTransfers, slc);
    }

    auto & data_object_store = node_state.GetDataObjectStore(transfer.m_ObjectType);

    DDSKeyRange remainder_key_range, output_key_range;

    DDSDataObjectListSync object_list;
    object_list.m_TargetNode = transfer.m_NodeId;
    object_list.m_DataObjectType = transfer.m_ObjectType;
    object_list.m_RoutingTableGen = m_TableGen;

    if (data_object_store.ExportObjectsInRange(transfer.m_KeyRange, output_key_range, remainder_key_range, 100, object_list.m_Objects) == false)
    {
      transfer.m_KeyRange = remainder_key_range;
    }
    else
    {
      m_PendingTransfers.erase(m_PendingTransfers.begin() + index);
      index--;
    }

    object_list.m_KeyRangeMin = output_key_range.m_Min;
    object_list.m_KeyRangeMax = output_key_range.m_Max;

    node_state.m_NodeNetwork.SendMessageToServer(transfer.m_NodeId, DDSServerToServerMessageType::kDataObjectListSync, StormReflEncodeJson(object_list));
  }

  return m_PendingTransfers.size() == 0;
}

