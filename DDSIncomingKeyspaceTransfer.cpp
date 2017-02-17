
#include "DDSIncomingKeyspaceTransfer.h"
#include "DDSLog.h"

DDSIncomingKeyspaceTransfer::DDSIncomingKeyspaceTransfer(int num_object_types, int table_gen, DDSKeyRange key_range) :
  m_Complete(false), 
  m_NumObjectTypes(num_object_types), 
  m_TableGen(table_gen), 
  m_UnsyncedKeys(std::make_unique<std::vector<DDSKeyRange>[]>(num_object_types)),
  m_FullKeyRange(key_range)
{
  for (int index = 0; index < m_NumObjectTypes; index++)
  {
    m_UnsyncedKeys[index].push_back(key_range);
  }
}

DDSIncomingKeyspaceTransfer::DDSIncomingKeyspaceTransfer(int num_object_types, int table_gen, const std::vector<DDSKeyRange> & key_ranges, DDSKeyRange full_key_range) :
  m_Complete(false), 
  m_NumObjectTypes(num_object_types), 
  m_TableGen(table_gen), 
  m_UnsyncedKeys(std::make_unique<std::vector<DDSKeyRange>[]>(num_object_types)),
  m_FullKeyRange(full_key_range)
{
  for (int index = 0; index < m_NumObjectTypes; index++)
  {
    for (auto & key_range : key_ranges)
    {
      m_UnsyncedKeys[index].push_back(key_range);
    }
  }
}

bool DDSIncomingKeyspaceTransfer::IsComplete() const
{
  return m_Complete;
}

int DDSIncomingKeyspaceTransfer::GetTableGeneration() const
{
  return m_TableGen;
}

void DDSIncomingKeyspaceTransfer::SetKeyRangeComplete(int object_type_id, DDSKeyRange key_range)
{
  std::vector<DDSKeyRange> new_unsynced_key_list;

  for (auto src_key_range : m_UnsyncedKeys[object_type_id])
  {
    DDSKeyRange r1, r2;
    int outp = GetKeyRangeDifference(src_key_range, key_range, r1, r2);

    if (outp >= 1)
    {
      new_unsynced_key_list.push_back(r1);
    }

    if (outp >= 2)
    {
      new_unsynced_key_list.push_back(r2);
    }
  }

  m_UnsyncedKeys[object_type_id] = std::move(new_unsynced_key_list);

  bool has_unsynced_keys = false;
  for (int index = 0; index < m_NumObjectTypes; index++)
  {
    if (m_UnsyncedKeys[index].size() > 0)
    {
      has_unsynced_keys = true;
      break;
    }
  }

  if (has_unsynced_keys == false)
  {
    m_Complete = true;
  }
}
