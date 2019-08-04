
#include "DDSIncomingKeyspaceTransferManager.h"
#include "DDSLog.h"

#include <cassert>

DDSIncomingKeyspaceTransferManager::DDSIncomingKeyspaceTransferManager(int num_object_types) :
  m_Initialized(false), m_NumObjectTypes(num_object_types)
{

}

void DDSIncomingKeyspaceTransferManager::InitializeSingleNode()
{
  m_Initialized = true;
}

void DDSIncomingKeyspaceTransferManager::InitializeUnsyncedKeyspace(int table_gen, DDSKeyRange key_range)
{
  m_Initialized = true;
  m_PendingTransfers.emplace_back(m_NumObjectTypes, table_gen, key_range);
}

void DDSIncomingKeyspaceTransferManager::ProcessNewRoutingTable(
  const DDSRoutingTable & new_routing_table, const DDSRoutingTable & old_routing_table, DDSKeyRange new_key_range, DDSNodeId local_node_id)
{
  std::vector<std::pair<DDSNodeId, DDSKeyRange>> key_ranges;
  GetKeyRanges(old_routing_table, key_ranges);

  std::vector<DDSKeyRange> incoming_key_ranges;

  for (auto & range_data : key_ranges)
  {
    if (range_data.first == local_node_id)
    {
      continue;
    }

    DDSKeyRange r1, r2;
    int num_overlaps = GetKeyRangeIntersection(new_key_range, range_data.second, r1, r2);

    if (num_overlaps >= 1)
    {
      assert(KeyRangeEntirelyInKeyRange(new_key_range, r1));
      incoming_key_ranges.push_back(r1);
    }

    if (num_overlaps >= 2)
    {
      assert(KeyRangeEntirelyInKeyRange(new_key_range, r2));
      incoming_key_ranges.push_back(r2);
    }
  }

  if (incoming_key_ranges.size() > 0)
  {
    m_PendingTransfers.emplace_back(m_NumObjectTypes, new_routing_table.m_TableGeneration, incoming_key_ranges, new_key_range);
  }
}

bool DDSIncomingKeyspaceTransferManager::SetKeyRangeComplete(int table_gen, int object_type, DDSKeyRange key_range)
{
  if (m_PendingTransfers.size() == 0)
  {
    return false;
  }

  if (m_PendingTransfers[0].GetTableGeneration() != table_gen)
  {
    return false;
  }

  m_PendingTransfers[0].SetKeyRangeComplete(object_type, key_range);

  if (m_PendingTransfers[0].IsComplete())
  {
    m_PendingTransfers.erase(m_PendingTransfers.begin());
  }

  return true;
}

bool DDSIncomingKeyspaceTransferManager::IsReadyForOutgoingKeyspaceTransfer(int table_gen) const
{
  if (IsComplete())
  {
    return true;
  }

  return m_PendingTransfers[0].GetTableGeneration() >= table_gen;
}

bool DDSIncomingKeyspaceTransferManager::IsComplete() const
{
  return m_PendingTransfers.size() == 0;
}
