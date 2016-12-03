
#include "DDSOutgoingKeyspaceTransferManager.h"
#include "DDSNodeState.h"

DDSOutgoingKeyspaceTransferManager::DDSOutgoingKeyspaceTransferManager(DDSNodeState & node_state, int num_object_types) :
  m_NodeState(node_state),
  m_NumObjectTypes(num_object_types)
{

}

void DDSOutgoingKeyspaceTransferManager::ProcessNewRoutingTable(const DDSRoutingTable & new_routing_table, DDSKeyRange original_key_range, DDSNodeId local_node_id)
{
  std::vector<std::pair<DDSNodeId, DDSKeyRange>> key_ranges;
  GetKeyRanges(new_routing_table, key_ranges);

  std::vector<std::pair<DDSNodeId, DDSKeyRange>> keyspace_transfers;

  for (auto & range_data : key_ranges)
  {
    if (range_data.first == local_node_id)
    {
      continue;
    }

    DDSKeyRange r1, r2;
    int num_overlaps = GetKeyRangeIntersection(original_key_range, range_data.second, r1, r2);

    if (num_overlaps >= 1)
    {
      keyspace_transfers.emplace_back(std::make_pair(range_data.first, r1));
    }

    if (num_overlaps >= 2)
    {
      keyspace_transfers.emplace_back(std::make_pair(range_data.first, r2));
    }
  }

  if (keyspace_transfers.size() > 0)
  {
    m_PendingTransfers.emplace_back(m_NumObjectTypes, new_routing_table.m_TableGeneration, keyspace_transfers);
  }
}

void DDSOutgoingKeyspaceTransferManager::ProcessDefunctRoutingTable(const DDSRoutingTable & new_routing_table, DDSKeyRange original_key_range)
{
  std::vector<std::pair<DDSNodeId, DDSKeyRange>> key_ranges;
  GetKeyRanges(new_routing_table, key_ranges);

  std::vector<std::pair<DDSNodeId, DDSKeyRange>> keyspace_transfers;

  for (auto & range_data : key_ranges)
  {
    DDSKeyRange r1, r2;
    int num_overlaps = GetKeyRangeIntersection(original_key_range, range_data.second, r1, r2);

    if (num_overlaps >= 1)
    {
      keyspace_transfers.emplace_back(std::make_pair(range_data.first, r1));
    }

    if (num_overlaps >= 2)
    {
      keyspace_transfers.emplace_back(std::make_pair(range_data.first, r2));
    }
  }

  if (keyspace_transfers.size() > 0)
  {
    m_PendingTransfers.emplace_back(m_NumObjectTypes, new_routing_table.m_TableGeneration, keyspace_transfers);
  }
}

void DDSOutgoingKeyspaceTransferManager::Update()
{
  if (m_PendingTransfers.size() > 0)
  {
    auto & next_transfer = m_PendingTransfers.front();
    if (next_transfer.IsReady(m_NodeState) == false)
    {
      return;
    }

    if (next_transfer.Send(m_NodeState))
    {
      m_PendingTransfers.erase(m_PendingTransfers.begin());
    }
  }
}

bool DDSOutgoingKeyspaceTransferManager::IsComplete()
{
  return m_PendingTransfers.size() == 0;
}
