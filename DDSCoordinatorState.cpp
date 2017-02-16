

#include <StormSockets/StormSocketServerFrontendWebsocket.h>

#include <StormRefl/StormReflJson.h>

#include "DDSLog.h"
#include "DDSRandom.h"
#include "DDSCoordinatorState.h"
#include "DDSCoordinatorServerProtocol.h"
#include "DDSServerMessage.h"

#include "DDSRoutingTable.refl.meta.h"
#include "DDSCoordinatorProtocolMessages.refl.meta.h"


DDSCoordinatorState::DDSCoordinatorState(const StormSockets::StormSocketInitSettings & backend_settings,
  const StormSockets::StormSocketServerFrontendWebsocketSettings & node_server_settings,
  const StormSockets::StormSocketClientFrontendHttpSettings & http_client_settings,
  const DDSDatabaseSettings & database_settings) :
  m_Backend(backend_settings),
  m_NetworkService(m_Backend, *this, node_server_settings),
  m_LastLoadBalancerSync(time(nullptr)),
  m_NextNodeId(0),
  m_ClientSecret(DDSGetRandomNumber64()),
  m_ServerSecret(DDSGetRandomNumber64()),
  m_HttpClient(http_client_settings, m_Backend),
  m_Database(std::make_unique<DDSDatabaseConnectionPool>(database_settings))
{

}

DDSCoordinatorState::~DDSCoordinatorState()
{

}

int DDSCoordinatorState::GetDataObjectTypeIdForNameHash(uint32_t name_hash) const
{
  for (std::size_t index = 0; index < m_DataObjectNameHashes.size(); index++)
  {
    if (m_DataObjectNameHashes[index] == name_hash)
    {
      return (int)index;
    }
  }

  return -1;
}

int DDSCoordinatorState::GetDatabaseObjectTypeIdForNameHash(uint32_t name_hash) const
{
  for (std::size_t index = 0; index < m_DatabaseObjectNameHashes.size(); index++)
  {
    if (m_DatabaseObjectNameHashes[index] == name_hash)
    {
      return (int)index;
    }
  }

  return -1;
}

int DDSCoordinatorState::GetSharedObjectTypeIdForNameHash(uint32_t name_hash) const
{
  for (std::size_t index = 0; index < m_SharedObjectNameHashes.size(); index++)
  {
    if (m_SharedObjectNameHashes[index] == name_hash)
    {
      return (int)index + m_NumDataObjects;
    }
  }

  return -1;
}

int DDSCoordinatorState::GetTargetObjectIdForNameHash(uint32_t name_hash) const
{
  for (std::size_t index = 0; index < m_DatabaseObjectNameHashes.size(); index++)
  {
    if (m_DatabaseObjectNameHashes[index] == name_hash)
    {
      return (int)index;
    }
  }

  for (std::size_t index = 0; index < m_SharedObjectNameHashes.size(); index++)
  {
    if (m_SharedObjectNameHashes[index] == name_hash)
    {
      return (int)index + m_NumDataObjects;
    }
  }

  DDSLog::LogError("Invalid object id request");
  return -1;
}

void DDSCoordinatorState::InitializeLoadBalancerServer(
  const StormSockets::StormSocketServerFrontendWebsocketSettings & lb_server_settings, int endpoint_id)
{
  m_LoadBalancerServices.emplace_back(std::make_unique<DDSLoadBalancerNetworkService>(m_Backend, *this, lb_server_settings, endpoint_id));
}

void DDSCoordinatorState::CreateTimer(std::chrono::system_clock::duration duration, DDSCoordinatorResponderCallData && responder_data)
{
  std::unique_ptr<DDSDeferredCallback> callback = std::make_unique<DDSDeferredCallback>();
  DDSDeferredCallback * callback_ptr = callback.get();

  std::string responder_str = StormReflEncodeJson(responder_data);
  DDSDataObjectAddress address{ responder_data.m_ObjectType, responder_data.m_Key };

  m_TimerSystem.CreateCallback(duration, *callback.get(), [=]() mutable {
    SendTargetedMessage(address, DDSCoordinatorProtocolMessageType::kResponderCall, std::move(responder_str));
    DestroyDeferredCallback(callback_ptr);
  });

  m_DeferredCallbackList.emplace(std::move(callback));
}

void DDSCoordinatorState::CreateHttpRequest(const DDSHttpRequest & request, DDSCoordinatorResponderCallData && responder_data)
{
  std::unique_ptr<DDSDeferredCallback> callback = std::make_unique<DDSDeferredCallback>();
  DDSDeferredCallback * callback_ptr = callback.get();

  DDSDataObjectAddress address{ responder_data.m_ObjectType, responder_data.m_Key };

  m_HttpClient.CreateCallback(request, *callback.get(), [=](bool success, const std::string & data, const std::string & headers) mutable {

    responder_data.m_MethodArgs = "[" + StormReflEncodeJson(success) + "," + StormReflEncodeJson(data) + "," + StormReflEncodeJson(headers) + "]";
    std::string responder_str = StormReflEncodeJson(responder_data);
    SendTargetedMessage(address, DDSCoordinatorProtocolMessageType::kResponderCall, std::move(responder_str));
    DestroyDeferredCallback(callback_ptr);
  });

  m_DeferredCallbackList.emplace(std::move(callback));
}

DDSRoutingTableNodeInfo DDSCoordinatorState::GetNodeInfo(DDSKey key)
{
  return GetNodeDataForKey(key, m_RoutingTable, m_RoutingKeyRanges);
}

time_t DDSCoordinatorState::GetNetworkTime()
{
  return time(nullptr);
}

void DDSCoordinatorState::GotMessageFromServer(DDSNodeId server_id, DDSCoordinatorProtocolMessageType type, const char * data)
{
  if (type == DDSCoordinatorProtocolMessageType::kTargetedMessage)
  {
    DDSTargetedMessage targeted_message;
    if (StormReflParseJson(targeted_message, data) == false)
    {
      DDSLog::LogError("Invalid targeted message");
      return;
    }

    SendTargetedMessage(DDSDataObjectAddress{ targeted_message.m_ObjectType, targeted_message.m_Key }, type, std::string(data));
  }
  else if (type == DDSCoordinatorProtocolMessageType::kTargetedMessageResponder)
  {
    DDSTargetedMessageWithResponder targeted_message;
    if (StormReflParseJson(targeted_message, data) == false)
    {
      DDSLog::LogError("Invalid targeted message");
      return;
    }

    SendTargetedMessage(DDSDataObjectAddress{ targeted_message.m_ObjectType, targeted_message.m_Key }, type, std::string(data));
  }
  else if (type == DDSCoordinatorProtocolMessageType::kResponderCall)
  {
    DDSResponderCallData responder_data;
    if (StormReflParseJson(responder_data, data) == false)
    {
      DDSLog::LogError("Invalid targeted message");
      return;
    }

    SendTargetedMessage(DDSDataObjectAddress{ responder_data.m_ObjectType, responder_data.m_Key }, type, std::string(data));
  }
  else if (type == DDSCoordinatorProtocolMessageType::kCreateSubscription)
  {
    DDSCoordinatorCreateSubscription sub_data;
    if (StormReflParseJson(sub_data, data) == false)
    {
      DDSLog::LogError("Invalid targeted message");
      return;
    }

    SendTargetedMessage(DDSDataObjectAddress{ sub_data.m_ObjectType, sub_data.m_Key }, type, std::string(data));
  }
  else if (type == DDSCoordinatorProtocolMessageType::kDestroySubscription)
  {
    DDSCoordinatorDestroySubscription sub_data;
    if (StormReflParseJson(sub_data, data) == false)
    {
      DDSLog::LogError("Invalid targeted message");
      return;
    }

    SendTargetedMessage(DDSDataObjectAddress{ sub_data.m_ObjectType, sub_data.m_Key }, type, std::string(data));
  }
  else if (type == DDSCoordinatorProtocolMessageType::kSubscriptionDeleted)
  {
    DDSCoordinatorSubscriptionDeleted sub_data;
    if (StormReflParseJson(sub_data, data) == false)
    {
      DDSLog::LogError("Invalid targeted message");
      return;
    }

    SendTargetedMessage(DDSDataObjectAddress{ sub_data.m_ObjectType, sub_data.m_Key }, type, std::string(data));
  }
  else if (type == DDSCoordinatorProtocolMessageType::kShutDown)
  {
    SetNodeDefunct(server_id);
    SyncRoutingTable();
  }
  else if (type == DDSCoordinatorProtocolMessageType::kCPUUsage)
  {
    DDSCoordinatorNodeCPUUsage msg;
    if (StormReflParseJson(msg, data) == false)
    {
      DDSLog::LogError("Invalid targeted message");
      return;
    }

    for (auto & elem : m_LoadBalancerServices)
    {
      elem->UpdateNode(server_id, msg.m_Usage);
    }
  }
}

bool DDSCoordinatorState::SendTargetedMessage(DDSDataObjectAddress addr, DDSCoordinatorProtocolMessageType type, std::string && message, bool force_process)
{
  if (m_QueueMessageDepth && force_process == false)
  {
    m_QueuedTargetedMessages.emplace(std::make_tuple(addr, type, message));
    return true;
  }

  if (addr.m_ObjectType >= m_NumDataObjects)
  {
    int shared_object_id = addr.m_ObjectType - m_NumDataObjects;
    m_SharedObjects[shared_object_id]->ProcessMessage(type, message.c_str());
    return true;
  }
  else
  {
    DDSNodeId node_id;

    if (m_RoutingTable.m_Table.size() == 0)
    {
      return false;
    }

    for (auto key_range_data : m_RoutingKeyRanges)
    {
      if (KeyInKeyRange(addr.m_ObjectKey, key_range_data.second))
      {
        node_id = key_range_data.first;
        break;
      }
    }

    std::string data = StormReflGetEnumAsString(type);
    data += " " + message;

    return m_NetworkService.SendMessageToNode(node_id, data.c_str(), data.length());
  }
}

void DDSCoordinatorState::SendToAllConnectedClients(std::string && message)
{
  m_NetworkService.SendMessageToAllConnectedClients(message.data(), message.size());
}

void DDSCoordinatorState::ProcessEvents()
{
  m_Database->TriggerCallbacks();

  m_NetworkService.ProcessEvents();

  for (auto & elem : m_LoadBalancerServices)
  {
    elem->ProcessEvents();
  }

  m_Resolver.Update();
  m_HttpClient.Update();
  m_TimerSystem.Update();

  auto cur_time = time(nullptr);
  if (cur_time - m_LastLoadBalancerSync > 5)
  {
    for (auto & elem : m_LoadBalancerServices)
    {
      elem->SyncNodeList();
    }

    m_LastLoadBalancerSync = cur_time;
  }
}

void DDSCoordinatorState::SyncRoutingTable()
{
  std::string buffer = "kRoutingTable ";
  StormReflEncodeJson(m_RoutingTable, buffer);

  DDSLog::LogVerbose("Syncing new routing table");
  DDSLog::LogVerbose(StormReflEncodePrettyJson(m_RoutingTable));

  m_NetworkService.SendMessageToAllConnectedClients(buffer.c_str(), buffer.length());

  for (auto & elem : m_LoadBalancerServices)
  {
    elem->UpdateRoutingTable(m_RoutingTable);
  }
}

void DDSCoordinatorState::QueryObjectData(int object_type_id, DDSKey key, const char * collection)
{
  m_Database->QueryDatabaseByKey(key, collection, [&](const char * data, int ec) { HandleQueryByKey(object_type_id, key, data, ec); });
}

void DDSCoordinatorState::QueryObjectData(const char * collection, const char * query, DDSCoordinatorResponderCallData && responder_call)
{
  DDSDataObjectAddress address{ responder_call.m_ObjectType, responder_call.m_Key };

  auto callback = [&](const char * data, int ec) {

    std::string sb;
    StormReflJsonEncodeString(data, sb);

    responder_call.m_MethodArgs = "[" + sb + "," + StormReflEncodeJson(ec) + "]";
    std::string responder_str = StormReflEncodeJson(responder_call);
    SendTargetedMessage(address, DDSCoordinatorProtocolMessageType::kResponderCall, std::move(responder_str));
  };

  m_Database->QueryDatabaseCustom(query, collection, std::move(callback));
}

void DDSCoordinatorState::InsertObjectData(int object_type_id, DDSKey key, const char * collection, const char * data, DDSCoordinatorResponderCallData && responder_call)
{
  m_Database->QueryDatabaseInsert(key, collection, data, [this, responder_call](const char * data, int ec) mutable { HandleInsertResult(ec, responder_call); });
}

void DDSCoordinatorState::DestroyDeferredCallback(DDSDeferredCallback * callback)
{
  for (auto itr = m_DeferredCallbackList.begin(); itr != m_DeferredCallbackList.end(); ++itr)
  {
    if (itr->get() == callback)
    {
      m_DeferredCallbackList.erase(itr);
      return;
    }
  }
}

void DDSCoordinatorState::HandleQueryByKey(int object_type_id, DDSKey key, const char * result_data, int ec)
{

}

void DDSCoordinatorState::HandleInsertResult(int ec, DDSCoordinatorResponderCallData & responder_call)
{
  char result_code[128];
  snprintf(result_code, sizeof(result_code), "[%d]", ec);

  responder_call.m_MethodArgs = result_code;

  SendTargetedMessage(DDSDataObjectAddress{ responder_call.m_ObjectType, responder_call.m_Key },
    DDSCoordinatorProtocolMessageType::kResponderCall, StormReflEncodeJson(responder_call));
}

void DDSCoordinatorState::BeginQueueingMessages()
{
  m_QueueMessageDepth++;
}

void DDSCoordinatorState::EndQueueingMessages()
{
  m_QueueMessageDepth--;
  if (m_QueueMessageDepth == 0)
  {
    m_QueueMessageDepth++;

    while (m_QueuedTargetedMessages.size())
    {
      auto message = m_QueuedTargetedMessages.back();
      SendTargetedMessage(std::get<0>(message), std::get<1>(message), std::move(std::get<2>(message)), true);
      m_QueuedTargetedMessages.pop();
    }

    m_QueueMessageDepth--;
  }
}

DDSCoordinatorNetworkService & DDSCoordinatorState::GetNetworkService()
{
  return m_NetworkService;
}

const DDSRoutingTable & DDSCoordinatorState::GetRoutingTable() const
{
  return m_RoutingTable;
}

DDSNodeId DDSCoordinatorState::GetNodeIdForKey(DDSKey key) const
{
  for (auto & key_range : m_RoutingKeyRanges)
  {
    if (KeyInKeyRange(key, key_range.second))
    {
      return key_range.first;
    }
  }

  throw std::runtime_error("Invalid routing table");
}

DDSNodeId DDSCoordinatorState::CreateNode(uint32_t addr, uint16_t port, const std::vector<DDSNodePort> & endpoint_ports, const std::vector<DDSNodePort> & website_ports)
{
  DDSLog::LogInfo("Creating new node");

  m_RoutingTable.m_TableGeneration++;

  DDSNodeElement node;
  node.m_Id = m_NextNodeId;
  node.m_Addr = addr;
  node.m_Port = port;
  node.m_EndpointPorts = endpoint_ports;
  node.m_WebsitePorts = website_ports;

  std::size_t table_size = m_RoutingTable.m_Table.size();
  if (table_size == 0)
  {
    node.m_CentralKey = 0x0000000000000000;
    node.m_Id = 1;

    m_RoutingTable.m_Table.emplace_back(node);

    m_NextNodeId = 2;

    GetKeyRanges(m_RoutingTable, m_RoutingKeyRanges);
    return node.m_Id;
  }

  if (table_size == 1)
  {
    node.m_CentralKey = m_RoutingTable.m_Table[0].m_CentralKey + 0x8000000000000000;

    m_RoutingTable.m_Table.emplace_back(node);

    m_NextNodeId++;

    GetKeyRanges(m_RoutingTable, m_RoutingKeyRanges);
    return node.m_Id;
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

  node.m_CentralKey = best_key;

  m_RoutingTable.m_Table.emplace_back(node);
  m_RoutingTable.m_TableGeneration++;

  m_NextNodeId++;
  GetKeyRanges(m_RoutingTable, m_RoutingKeyRanges);
  return node.m_Id;
}

void DDSCoordinatorState::SetNodeDefunct(DDSNodeId id)
{
  DDSLog::LogInfo("Coordinator is shutting down node");

  m_RoutingTable.m_TableGeneration++;
  std::size_t table_size = m_RoutingTable.m_Table.size();
  for (std::size_t index = 0; index < table_size; index++)
  {
    if (m_RoutingTable.m_Table[index].m_Id == id)
    {
      m_RoutingTable.m_Defunct.push_back(m_RoutingTable.m_Table[index]);
      m_RoutingTable.m_Table.erase(m_RoutingTable.m_Table.begin() + index);
      return;
    }
  }

  DDSLog::LogError("Node was set to defunct, but not in the actual node list");
}

void DDSCoordinatorState::DestroyNode(DDSNodeId id)
{
  DDSLog::LogInfo("Destroying node");

  m_RoutingTable.m_TableGeneration++;
  std::size_t table_size = m_RoutingTable.m_Defunct.size();
  for (std::size_t index = 0; index < table_size; index++)
  {
    if (m_RoutingTable.m_Defunct[index].m_Id == id)
    {
      m_RoutingTable.m_Defunct.erase(m_RoutingTable.m_Defunct.begin() + index);
      return;
    }
  }

  DDSLog::LogError("Node was set to destroy, but not in the actual node list");
}

uint64_t DDSCoordinatorState::GetClientSecret() const
{
  return m_ClientSecret;
}

uint64_t DDSCoordinatorState::GetServerSecret() const
{
  return m_ServerSecret;
}

const void * DDSCoordinatorState::GetSharedObjectPointer(int shared_object_type)
{
  return m_SharedObjects[shared_object_type - m_NumDataObjects]->GetSharedObjectPointer();
}
