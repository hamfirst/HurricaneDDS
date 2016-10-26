
#include <tuple>

#include "DDSLog.h"
#include "DDSOutgoingKeyspaceTransfer.h"
#include "DDSIncomingKeyspaceTransferManager.h"
#include "DDSNodeState.h"
#include "DDSServerMessage.h"
#include "DDSServerToServerMessages.refl.meta.h"

#include <StormRefl/StormReflJsonStd.h>

DDSOutgoingKeyspaceTransfer::DDSOutgoingKeyspaceTransfer(int num_object_types, int table_gen, const std::vector<std::pair<DDSNodeId, DDSKeyRange>> & output_keyranges) :
  m_NumObjectTypes(num_object_types), m_TableGen(table_gen)
{
  for (auto & val : output_keyranges)
  {
    for (int index = 0; index < num_object_types; index++)
    {
      m_PendingTransfers.emplace_back(std::make_tuple(val.first, index, val.second));
    }
  }
}

bool DDSOutgoingKeyspaceTransfer::Send(DDSNodeState & node_state)
{
  for (std::size_t index = 0; index < m_PendingTransfers.size(); index++)
  {
    auto & transfer = m_PendingTransfers[0];

    auto node_id = std::get<0>(transfer);
    int object_type = std::get<1>(transfer);
    auto key_range = std::get<2>(transfer);

    if (node_state.GetNodeNetwork().RequestNodeConnection(node_id) == false)
    {
      continue;
    }

    if (node_state.GetIncomingKeyspace().IsCompleteForKeyRange(key_range) == false)
    {
      continue;
    }

    auto & data_object_store = node_state.GetDataObjectStore(object_type);

    DDSKeyRange remainder_key_range, output_key_range;

    DDSDataObjectListSync object_list;
    object_list.m_DataObjectType = object_type;
    object_list.m_RoutingTableGen = m_TableGen;

    if (data_object_store.ExportObjectsInRange(key_range, output_key_range, remainder_key_range, 100, object_list.m_Objects) == false)
    {
      std::get<2>(transfer) = remainder_key_range;
    }
    else
    {
      m_PendingTransfers.erase(m_PendingTransfers.begin() + index);
      index--;
    }

    object_list.m_KeyRangeMin = output_key_range.m_Min;
    object_list.m_KeyRangeMax = output_key_range.m_Max;

    DDSLog::LogInfo("Sending object id %d keys %d to %d node %d", object_type, output_key_range.m_Min, output_key_range.m_Max, node_id);
    DDSLog::LogInfo("Object list has %d elements", object_list.m_Objects.size());

    node_state.GetNodeNetwork().SendMessageToServer(node_id, DDSGetServerMessage(object_list));
  }

  return m_PendingTransfers.size() == 0;
}

