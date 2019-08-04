#pragma once

#include "DDSRoutingTable.refl.h"

#include <functional>
#include <optional>

using DDSRoutingTableNodeInfo = std::optional<std::reference_wrapper<const DDSNodeElementBase>>;

std::string GetNodeAddrAsString(DDSNodeAddr addr);

DDSKeyRange GetKeyRange(DDSNodeId node_id, const DDSRoutingTable & routing_table);
void GetKeyRanges(const DDSRoutingTable & routing_table, std::vector<std::pair<DDSNodeId, DDSKeyRange>> & key_ranges);

DDSNodeId GetNodeIdForKey(DDSKey key, const std::vector<std::pair<DDSNodeId, DDSKeyRange>> & key_ranges);
DDSRoutingTableNodeInfo GetNodeDataForNodeId(DDSNodeId node_id, const DDSRoutingTable & routing_table);

bool IsNodeInRoutingTable(DDSNodeId node_id, const DDSRoutingTable & routing_table);

DDSRoutingTableNodeInfo GetNodeDataForKey(DDSKey key,
  const DDSRoutingTable & routing_table, const std::vector<std::pair<DDSNodeId, DDSKeyRange>> & key_ranges);
