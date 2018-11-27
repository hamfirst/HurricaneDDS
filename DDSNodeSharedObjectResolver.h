#pragma once

#include <map>
#include <vector>

#include "DDSKey.h"
#include "DDSCoordinatorProtocolMessages.refl.h"

class DDSNodeSharedObjectResolver
{
public:

  void AddNewRoutingTableEntry(int routing_table_gen, DDSKeyRange local_key_range);
  void AddSharedChange(int routing_table_gen, const DDSCoordinatorSharedObjectDelta & delta);

  std::vector<std::vector<DDSCoordinatorSharedObjectDelta> *> GetChangeList(int routing_table_gen, DDSKey object_key);

  void Clear();

private:
  struct DDSNodeSharedObjectChangeList
  {
    DDSKeyRange m_KeyRange;
    std::vector<DDSCoordinatorSharedObjectDelta> m_Changes;
  };

  std::map<int, DDSNodeSharedObjectChangeList> m_SharedChanges;
  int m_HighestRoutingTable = 0;
};
