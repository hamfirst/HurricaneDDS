#pragma once

#include "DDSRoutingTable.refl.h"

DDSKeyRange GetKeyRange(DDSNodeId node_id, const DDSRoutingTable & routing_table);
void GetKeyRanges(const DDSRoutingTable & routing_table, std::vector<std::pair<DDSNodeId, DDSKeyRange>> & key_ranges);
