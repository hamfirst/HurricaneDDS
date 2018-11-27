
#include "DDSNodeSharedObjectResolver.h"

void DDSNodeSharedObjectResolver::AddNewRoutingTableEntry(int routing_table_gen, DDSKeyRange local_key_range)
{
  m_SharedChanges.emplace(std::make_pair(routing_table_gen, DDSNodeSharedObjectChangeList{ local_key_range }));
  m_HighestRoutingTable = std::max(routing_table_gen, m_HighestRoutingTable);
}

void DDSNodeSharedObjectResolver::AddSharedChange(int routing_table_gen, const DDSCoordinatorSharedObjectDelta & delta)
{
  auto itr = m_SharedChanges.find(routing_table_gen);
  if (itr == m_SharedChanges.end())
  {
    return;
  }

  itr->second.m_Changes.push_back(delta);
}

std::vector<std::vector<DDSCoordinatorSharedObjectDelta> *> DDSNodeSharedObjectResolver::GetChangeList(int routing_table_gen, DDSKey object_key)
{
  std::vector<std::vector<DDSCoordinatorSharedObjectDelta> *> change_lists;

  for(auto itr = m_SharedChanges.lower_bound(routing_table_gen); itr != m_SharedChanges.end(); ++itr)
  {
    if (KeyInKeyRange(object_key, itr->second.m_KeyRange))
    {
      change_lists.push_back(&itr->second.m_Changes);
    }
  }

  return change_lists;
}

void DDSNodeSharedObjectResolver::Clear()
{
  m_SharedChanges.clear();
  m_HighestRoutingTable = 0;
}
