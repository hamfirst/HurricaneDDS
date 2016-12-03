#pragma once

#include <vector>
#include <memory>

#include <StormData/StormDataChangePacket.h>

#include "DDSDataObjectAddress.h"
#include "DDSRoutingTable.h"


class DDSIncomingKeyspaceTransfer
{
public:
  DDSIncomingKeyspaceTransfer(int num_object_types, int table_gen, DDSKeyRange key_range);
  DDSIncomingKeyspaceTransfer(int num_object_types, int table_gen, const std::vector<DDSKeyRange> & key_ranges);

  DDSIncomingKeyspaceTransfer(DDSIncomingKeyspaceTransfer && rhs) = default;

  DDSIncomingKeyspaceTransfer & operator = (DDSIncomingKeyspaceTransfer && rhs) = default;

  bool IsComplete() const;
  bool IsCompleteForKey(DDSDataObjectAddress addr) const;
  bool IsCompleteForKeyRange(DDSKeyRange key_range) const;

  int GetTableGeneration() const;

  void SetKeyRangeComplete(int object_type_id, DDSKeyRange key_range);

private:

  bool m_Complete;
  int m_NumObjectTypes;
  int m_TableGen;

  DDSKeyRange m_FullKeyRange;
  std::unique_ptr<std::vector<DDSKeyRange>[]> m_UnsyncedKeys;
};
