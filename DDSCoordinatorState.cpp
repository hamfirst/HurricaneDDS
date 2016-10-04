

#include <StormSockets\StormSocketServerFrontendWebsocket.h>

#include <StormRefl\StormReflJson.h>

#include "DDSLog.h"
#include "DDSRandom.h"
#include "DDSCoordinatorState.h"
#include "DDSCoordinatorServerProtocol.h"

#include "DDSRoutingTable.refl.meta.h"
#include "DDSCoordinatorProtocolMessages.refl.meta.h"


DDSCoordinatorState::DDSCoordinatorState(const StormSockets::StormSocketInitSettings & backend_settings,
  const StormSockets::StormSocketServerFrontendWebsocketSettings & server_settings) :
  m_NetworkService(*this, backend_settings, server_settings),
  m_NextNodeId(0),
  m_ClientSecret(DDSGetRandomNumber()),
  m_ServerSecret(DDSGetRandomNumber())
{

}

void DDSCoordinatorState::ProcessEvents()
{
  m_NetworkService.ProcessEvents();
}

void DDSCoordinatorState::SyncRoutingTable()
{
  std::string buffer = "kRoutingTable ";
  StormReflEncodeJson(m_RoutingTable, buffer);

  DDSLog::LogVerbose("Syncing new routing table");
  DDSLog::LogVerbose(StormReflEncodePrettyJson(m_RoutingTable));

  m_NetworkService.SendMessageToAllConnectedClients(buffer.c_str(), buffer.length());
}

DDSCoordinatorNetworkService & DDSCoordinatorState::GetNetworkService()
{
  return m_NetworkService;
}

const DDSRoutingTable & DDSCoordinatorState::GetRoutingTable() const
{
  return m_RoutingTable;
}

DDSNodeId DDSCoordinatorState::CreateNode(uint32_t addr, uint16_t port)
{
  DDSLog::LogInfo("Creating new node");

  m_RoutingTable.m_TableGeneration++;

  std::size_t table_size = m_RoutingTable.m_Table.size();
  if (table_size == 0)
  {
    DDSNodeId new_node_id = 1;
    m_RoutingTable.m_Table.emplace_back(DDSNodeElement{ new_node_id, addr, port, 0 });

    m_NextNodeId = 2;
    return new_node_id;
  }

  if (table_size == 1)
  {
    DDSNodeId new_node_id = m_NextNodeId;
    m_RoutingTable.m_Table.emplace_back(DDSNodeElement{ new_node_id, addr, port, m_RoutingTable.m_Table[0].m_CentralKey + 0x8000000000000000 });

    m_NextNodeId++;
    return new_node_id;
  }

  DDSKey biggest_gap = 0;
  DDSKey best_key = 0;
  for (std::size_t index = 0; index < table_size; index++)
  {
    auto & elem = m_RoutingTable.m_Table[index];
    auto & next_elem = m_RoutingTable.m_Table[(index + 1) % table_size];

    DDSKeyRange range = DDSKeyRange{ elem.m_CentralKey, next_elem.m_CentralKey };
    DDSKey range_size = GetKeyRangeSize(range);

    if (range_size > biggest_gap)
    {
      biggest_gap = range_size;
      best_key = elem.m_CentralKey + range_size / 2;
    }
  }

  DDSNodeId new_node_id = m_NextNodeId;
  m_RoutingTable.m_Table.emplace_back(DDSNodeElement{ new_node_id, addr, port, best_key });
  m_RoutingTable.m_TableGeneration++;

  m_NextNodeId++;
  return new_node_id;
}

void DDSCoordinatorState::DestroyNode(DDSNodeId id)
{
  DDSLog::LogInfo("Destroying node");

  m_RoutingTable.m_TableGeneration++;
  std::size_t table_size = m_RoutingTable.m_Table.size();
  for (std::size_t index = 0; index < table_size; index++)
  {
    if (m_RoutingTable.m_Table[index].m_Id == id)
    {
      m_RoutingTable.m_Table.erase(m_RoutingTable.m_Table.begin() + index);
      return;
    }
  }
}

uint64_t DDSCoordinatorState::GetClientSecret() const
{
  return m_ClientSecret;
}

uint64_t DDSCoordinatorState::GetServerSecret() const
{
  return m_ServerSecret;
}

