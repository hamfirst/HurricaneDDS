
#include "DDSIncomingKeyspaceTransferManager.h"


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
      incoming_key_ranges.push_back(r1);
    }

    if (num_overlaps >= 2)
    {
      incoming_key_ranges.push_back(r2);
    }
  }

  if (incoming_key_ranges.size() > 0)
  {
    m_PendingTransfers.emplace_back(m_NumObjectTypes, new_routing_table.m_TableGeneration, incoming_key_ranges);
  }
}

void DDSIncomingKeyspaceTransferManager::SetKeyRangeComplete(int table_gen, int object_type, DDSKeyRange key_range)
{
  for (int index = 0; index < (int)m_PendingTransfers.size(); index++)
  {
    if (m_PendingTransfers[index].GetTableGeneration() == table_gen)
    {
      m_PendingTransfers[index].SetKeyRangeComplete(object_type, key_range);

      if (m_PendingTransfers[index].IsComplete())
      {
        m_PendingTransfers.erase(m_PendingTransfers.begin() + index);
      }

      return;
    }
  }
}

bool DDSIncomingKeyspaceTransferManager::IsCompleteForKey(DDSDataObjectAddress addr) const
{
  for (auto & transfer : m_PendingTransfers)
  {
    if (transfer.IsCompleteForKey(addr) == false)
    {
      return false;
    }
  }

  return true;
}

bool DDSIncomingKeyspaceTransferManager::IsCompleteForKeyRange(DDSKeyRange key_range) const
{
  for (auto & transfer : m_PendingTransfers)
  {
    if (transfer.IsCompleteForKeyRange(key_range) == false)
    {
      return false;
    }
  }

  return true;
}
