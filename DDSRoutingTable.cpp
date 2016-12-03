
#include "DDSRoutingTable.h"
#include "DDSLog.h"

#include <stdexcept>
#include <algorithm>


std::string GetNodeAddrAsString(DDSNodeAddr addr)
{
  uint8_t * ip_addr = (uint8_t *)&addr;

  char buffer[25];
  snprintf(buffer, sizeof(buffer), "%d.%d.%d.%d", ip_addr[3], ip_addr[2], ip_addr[1], ip_addr[0]);
  return buffer;
}

DDSKeyRange GetKeyRange(DDSNodeId node_id, const DDSRoutingTable & routing_table)
{
  DDSKey local_key;
  DDSKey lowest_key = kMaxKey;
  DDSKey highest_key = kMinKey;
  bool found_key = false;

  for (auto & elem : routing_table.m_Table)
  {
    if (elem.m_Id == node_id)
    {
      local_key = elem.m_CentralKey;
      found_key = true;
    }

    lowest_key = std::min(lowest_key, elem.m_CentralKey);
    highest_key = std::max(highest_key, elem.m_CentralKey);
  }

  if (found_key == false)
  {
    DDSLog::LogError("Could not find node id in routing table");
  }

  if (routing_table.m_Table.size() == 1)
  {
    return DDSKeyRange{ kMinKey, kMaxKey };
  }

  DDSKey next_lowest_key = local_key == lowest_key ? highest_key : kMinKey;
  DDSKey next_highest_key = local_key == highest_key ? lowest_key : kMaxKey;

  for (auto & elem : routing_table.m_Table)
  {
    if (elem.m_CentralKey > local_key)
    {
      next_highest_key = std::min(next_highest_key, elem.m_CentralKey);
    }

    if (elem.m_CentralKey < local_key)
    {
      next_lowest_key = std::max(next_lowest_key, elem.m_CentralKey);
    }
  }

  DDSKey lower_key_space = (local_key - next_lowest_key);
  DDSKey upper_key_space = (next_highest_key - local_key);
  if (upper_key_space % 2 == 0)
  {
    upper_key_space--;
  }

  return DDSKeyRange{ local_key - lower_key_space / 2, local_key + upper_key_space / 2 };
}

void GetKeyRanges(const DDSRoutingTable & routing_table, std::vector<std::pair<DDSNodeId, DDSKeyRange>> & key_ranges)
{
  key_ranges.clear();

  auto table_copy = routing_table.m_Table;
  sort(table_copy.begin(), table_copy.end(), [](const DDSNodeElement & a, const DDSNodeElement & b) { return a.m_CentralKey < b.m_CentralKey; });

  std::size_t table_size = routing_table.m_Table.size();
  if (table_size == 0)
  {
    return;
  }

  if (table_size == 1)
  {
    key_ranges.emplace_back(std::make_pair(routing_table.m_Table[0].m_Id, DDSKeyRange{ kMinKey, kMaxKey }));
    return;
  }

  for (std::size_t index = 0; index < table_size; index++)
  {
    auto & cur_elem = table_copy[index];
    auto & next_elem = table_copy[(index + 1) % table_size];
    auto & prev_elem = table_copy[(index + table_size - 1) % table_size];

    DDSKey lower_key_space = (cur_elem.m_CentralKey - prev_elem.m_CentralKey);
    DDSKey upper_key_space = (next_elem.m_CentralKey - cur_elem.m_CentralKey);
    if (upper_key_space % 2 == 0)
    {
      upper_key_space--;
    }

    key_ranges.emplace_back(std::make_pair(cur_elem.m_Id,
      DDSKeyRange{ cur_elem.m_CentralKey - lower_key_space / 2, cur_elem.m_CentralKey + upper_key_space / 2 }));
  }
}

DDSNodeId GetNodeIdForKey(DDSKey key, const std::vector<std::pair<DDSNodeId, DDSKeyRange>> & key_ranges)
{
  for (auto & node_data : key_ranges)
  {
    if (KeyInKeyRange(key, node_data.second))
    {
      return node_data.first;
    }
  }

  DDSLog::LogError("Attempting to get node id for emtpy routing table");
  return{};
}

DDSRoutingTableNodeInfo GetNodeDataForNodeId(DDSNodeId node_id, const DDSRoutingTable & routing_table)
{
  for (auto & node_data : routing_table.m_Table)
  {
    if (node_data.m_Id == node_id)
    {
      return node_data;
    }
  }

  for (auto & node_data : routing_table.m_Defunct)
  {
    if (node_data.m_Id == node_id)
    {
      return node_data;
    }
  }

  return{};
}

DDSRoutingTableNodeInfo GetNodeDataForKey(DDSKey key, const DDSRoutingTable & routing_table, const std::vector<std::pair<DDSNodeId, DDSKeyRange>> & key_ranges)
{
  auto node_id = GetNodeIdForKey(key, key_ranges);
  for (auto & node : routing_table.m_Table)
  {
    if (node.m_Id == node_id)
    {
      return node;
    }
  }

  return{};
}
