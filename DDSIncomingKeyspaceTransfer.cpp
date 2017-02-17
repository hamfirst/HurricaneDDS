
#include "DDSIncomingKeyspaceTransfer.h"
#include "DDSLog.h"

DDSIncomingKeyspaceTransfer::DDSIncomingKeyspaceTransfer(int num_object_types, int table_gen, DDSKeyRange key_range) :
  m_Complete(false), 
  m_NumObjectTypes(num_object_types), 
  m_TableGen(table_gen), 
  m_UnsyncedKeys(std::make_unique<std::vector<DDSKeyRange>[]>(num_object_types))
{
  for (int index = 0; index < m_NumObjectTypes; index++)
  {
    m_UnsyncedKeys[index].push_back(key_range);
  }
}

DDSIncomingKeyspaceTransfer::DDSIncomingKeyspaceTransfer(int num_object_types, int table_gen, const std::vector<DDSKeyRange> & key_ranges) :
  m_Complete(false), 
  m_NumObjectTypes(num_object_types), 
  m_TableGen(table_gen), 
  m_UnsyncedKeys(std::make_unique<std::vector<DDSKeyRange>[]>(num_object_types))
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

bool DDSIncomingKeyspaceTransfer::IsCompleteForKey(DDSDataObjectAddress addr) const
{
  for (auto key_range : m_UnsyncedKeys[addr.m_ObjectType])
  {
    if (KeyInKeyRange(addr.m_ObjectKey, key_range))
    {
      return true;
    }
  }

  return true;
}

bool DDSIncomingKeyspaceTransfer::IsCompleteForKeyRange(DDSKeyRange key_range) const
{
  for (int index = 0; index < m_NumObjectTypes; index++)
  {
    for (auto src_key_range : m_UnsyncedKeys[index])
    {
      if (KeyRangeOverlapsKeyRange(key_range, src_key_range))
      {
        return false;
      }
    }
  }

  return true;
}

int DDSIncomingKeyspaceTransfer::GetTableGeneration() const
{
  return m_TableGen;
}

void DDSIncomingKeyspaceTransfer::SetKeyRangeComplete(int object_type_id, DDSKeyRange key_range)
{
  printf("Setting key range complete %llX to %llX\n", key_range.m_Min, key_range.m_Max);

  std::vector<DDSKeyRange> new_unsynced_key_list;

  for (auto src_key_range : m_UnsyncedKeys[object_type_id])
  {
    printf("Starting key range %llX to %llX\n", src_key_range.m_Min, src_key_range.m_Max);

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


  for (auto src_key_range : m_UnsyncedKeys[object_type_id])
  {
    printf("Remaining key range %llX to %llX\n", src_key_range.m_Min, src_key_range.m_Max);
  }

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
