
#include "DDSLog.h"
#include "DDSNodeState.h"
#include "DDSRoutingTable.h"
#include "DDSServerMessage.h"
#include "DDSEndpointFactoryBase.h"
#include "DDSDatabaseConnectionPool.h"

#include "DDSServerToServerMessages.refl.meta.h"

#include <StormRefl\StormReflJsonStd.h>

#include <StormSockets\StormSocketClientFrontendWebsocket.h>
#include <StormSockets\StormSocketServerFrontendWebsocket.h>

DDSNodeState::DDSNodeState(
  int num_data_object_types,
  const StormSockets::StormSocketInitSettings & backend_settings,
  const StormSockets::StormSocketServerFrontendWebsocketSettings & node_server_settings,
  const StormSockets::StormSocketClientFrontendWebsocketSettings & node_client_settings,
  const StormSockets::StormSocketClientFrontendHttpSettings & http_client_settings,
  const DDSCoordinatorClientSettings & coordinator_settings,
  const DDSDatabaseSettings & database_settings) :
  m_Backend(backend_settings),
  m_NodeNetwork(*this, node_server_settings, node_client_settings),
  m_HttpClient(*this, http_client_settings),
  m_CoordinatorConnection(*this, coordinator_settings),
  m_IncomingKeyspace(num_data_object_types),
  m_OutgoingKeyspace(*this, num_data_object_types),
  m_Database(std::make_unique<DDSDatabaseConnectionPool>(database_settings))
{
  inet_pton(AF_INET, node_server_settings.ListenSettings.LocalInterface, &m_LocalInterface);
  m_LocalPort = node_server_settings.ListenSettings.Port;

  m_CoordinatorConnection.RequestConnect();
}

void DDSNodeState::ProcessEvents()
{
  m_CoordinatorConnection.ProcessEvents();
  m_NodeNetwork.ProcessEvents();
  m_OutgoingKeyspace.Update();

  for (auto & endpoint_factory : m_EndpointFactoryList)
  {
    endpoint_factory->ProcessEvents();
  }
}

void DDSNodeState::GotInitialCoordinatorSync(DDSNodeId node_id, const DDSRoutingTable & routing_table, bool initial_node, uint64_t server_secret, uint64_t client_secret)
{
  m_LocalNodeId = node_id;
  m_RoutingTable = routing_table;
  GetKeyRanges(m_RoutingTable, m_RoutingKeyRanges);
  m_LocalKeyRange = GetKeyRange(node_id, m_RoutingTable);

  m_ServerSecret = server_secret;
  m_ClientSecret = client_secret;

  if (initial_node)
  {
    m_IncomingKeyspace.InitializeSingleNode();
  }
  else
  {
    m_IncomingKeyspace.InitializeUnsyncedKeyspace(routing_table.m_TableGeneration, m_LocalKeyRange);
  }
}

void DDSNodeState::GotNewRoutingTable(const DDSRoutingTable & routing_table)
{
  DDSKeyRange new_key_range = GetKeyRange(m_LocalNodeId, routing_table);
  m_IncomingKeyspace.ProcessNewRoutingTable(routing_table, m_RoutingTable, new_key_range, m_LocalNodeId);
  m_OutgoingKeyspace.ProcessNewRoutingTable(routing_table, m_LocalKeyRange, m_LocalNodeId);

  m_RoutingTable = routing_table;
  GetKeyRanges(m_RoutingTable, m_RoutingKeyRanges);
  m_LocalKeyRange = new_key_range;
}

void DDSNodeState::GotMessageFromServer(DDSNodeId node_id, DDSServerToServerMessageType type, const char * data)
{
  if (type == DDSServerToServerMessageType::kDataObjectListSync)
  {
    DDSDataObjectListSync obj_list;
    if (StormReflParseJson(obj_list, data) == false)
    {
      DDSLog::LogError("Invalid object list packet");
      return;
    }

    DDSLog::LogInfo("Got object sync id %d keys %d to %d node %d", obj_list.m_DataObjectType, obj_list.m_KeyRangeMin, obj_list.m_KeyRangeMax, node_id);
    DDSLog::LogInfo("Object list has %d elements", obj_list.m_Objects.size());

    auto & data_store = GetDataObjectStore(obj_list.m_DataObjectType);
    data_store.ProcessExportedObjects(obj_list.m_Objects);

    m_IncomingKeyspace.SetKeyRangeComplete(obj_list.m_RoutingTableGen, obj_list.m_DataObjectType, DDSKeyRange{ obj_list.m_KeyRangeMin, obj_list.m_KeyRangeMax });
  }
  else if (type == DDSServerToServerMessageType::kTargetedMessage)
  {
    DDSTargetedMessage targeted_message;
    if (StormReflParseJson(targeted_message, data) == false)
    {
      DDSLog::LogError("Invalid targeted message");
      return;
    }

    SendTargetedMessage(DDSDataObjectAddress{ targeted_message.m_ObjectType, targeted_message.m_Key }, type, std::string(data));
  }
  else if (type == DDSServerToServerMessageType::kTargetedMessageResponder)
  {
    DDSTargetedMessageWithResponder targeted_message;
    if (StormReflParseJson(targeted_message, data) == false)
    {
      DDSLog::LogError("Invalid targeted message");
      return;
    }

    SendTargetedMessage(DDSDataObjectAddress{ targeted_message.m_ObjectType, targeted_message.m_Key }, type, std::string(data));
  }
  else if (type == DDSServerToServerMessageType::kResponderCall)
  {
    DDSResponderCallData responder_data;
    if (StormReflParseJson(responder_data, data) == false)
    {
      DDSLog::LogError("Invalid targeted message");
      return;
    }

    SendTargetedMessage(DDSDataObjectAddress{ responder_data.m_ObjectType, responder_data.m_Key }, type, std::string(data));
  }
}

void DDSNodeState::SendTargetedMessage(DDSDataObjectAddress addr, DDSServerToServerMessageType type, std::string && message)
{
  if (KeyInKeyRange(addr.m_ObjectKey, m_LocalKeyRange))
  {
    if (m_IncomingKeyspace.IsCompleteForKey(addr))
    {
      HandleIncomingTargetedMessage(addr, type, message);
      return;
    }
  }
  else
  {
    DDSNodeId node_id = GetNodeIdForKey(addr.m_ObjectKey);
    if (m_NodeNetwork.RequestNodeConnection(node_id))
    {
      m_NodeNetwork.SendMessageToServer(node_id, DDSGetServerMessage(type, message.c_str()));
      return;
    }
  }

  auto result = m_PendingTargetedMessages.emplace(std::make_pair(addr, std::vector<std::pair<DDSServerToServerMessageType, std::string>>{}));
  result.first->second.emplace_back(std::make_pair(type, message));
}

DDSNodeId DDSNodeState::GetNodeIdForKey(DDSKey key) const
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

int DDSNodeState::GetDataObjectTypeIdForNameHash(uint32_t name_hash) const
{
  for(std::size_t index = 0; index < m_DataObjectList.size(); index++)
  {
    if (m_DataObjectList[index]->GetDataClassNameHash() == name_hash)
    {
      return (int)index;
    }
  }

  DDSLog::LogError("Invalid object id request");
  return -1;
}

int DDSNodeState::GetDatabaseObjectTypeIdForNameHash(uint32_t name_hash) const
{
  for (std::size_t index = 0; index < m_DataObjectList.size(); index++)
  {
    if (m_DataObjectList[index]->GetDatabaseClassNameHash() == name_hash)
    {
      return (int)index;
    }
  }

  DDSLog::LogError("Invalid object id request");
  return -1;
}

DDSDataObjectStoreBase & DDSNodeState::GetDataObjectStore(int object_type_id)
{
  return *m_DataObjectList[object_type_id].get();
}

bool DDSNodeState::IsReadyToCreateObjects()
{
  return m_IncomingKeyspace.IsCompleteForKeyRange(m_LocalKeyRange);
}

bool DDSNodeState::CreateNewDataObject(int object_type_id, DDSKey & output_key)
{
  if (IsReadyToCreateObjects() == false)
  {
    return false;
  }

  output_key = m_DataObjectList[object_type_id]->GetUnusedKeyInRange(m_LocalKeyRange);
  m_DataObjectList[object_type_id]->SpawnNewNonDatabaseBackedType(output_key);
  return true;
}

bool DDSNodeState::DestroyDataObject(int object_type_id, DDSKey key)
{
  if (IsReadyToCreateObjects() == false)
  {
    return false;
  }

  return m_DataObjectList[object_type_id]->DestroyNonDatabaseBackedType(key);
}

void DDSNodeState::CreateTimer(std::chrono::system_clock::duration duration, DDSDeferredCallback & callback, std::function<void()> && function)
{
  m_TimerSystem.CreateCallback(duration, callback, std::move(function));
}

void DDSNodeState::CreateTimer(std::chrono::system_clock::duration duration, DDSResponderCallData && responder_data)
{
  std::unique_ptr<DDSDeferredCallback> callback = std::make_unique<DDSDeferredCallback>();
  DDSDeferredCallback * callback_ptr = callback.get();

  std::string responder_str = StormReflEncodeJson(responder_data);
  DDSDataObjectAddress address{ responder_data.m_ObjectType, responder_data.m_Key };

  m_TimerSystem.CreateCallback(duration, *callback.get(), [=]() mutable { 
    SendTargetedMessage(address, DDSServerToServerMessageType::kResponderCall, std::move(responder_str));
    DestroyDeferredCallback(callback_ptr);
  });

  m_DeferredCallbackList.emplace(std::move(callback));
}

void DDSNodeState::CreateHttpRequest(const char * url, DDSDeferredCallback & callback, std::function<void(bool, const std::string &)> && function)
{
  m_HttpClient.CreateCallback(url, callback, std::move(function));
}

void DDSNodeState::CreateHttpRequest(const char * url, DDSResponderCallData && responder_data)
{
  std::unique_ptr<DDSDeferredCallback> callback = std::make_unique<DDSDeferredCallback>();
  DDSDeferredCallback * callback_ptr = callback.get();

  DDSDataObjectAddress address{ responder_data.m_ObjectType, responder_data.m_Key };

  m_HttpClient.CreateCallback(url, *callback.get(), [=](bool success, const std::string & data) mutable {

    responder_data.m_MethodArgs = "[" + StormReflEncodeJson(success) + "," + StormReflEncodeJson(data) + "]";
    std::string responder_str = StormReflEncodeJson(responder_data);
    SendTargetedMessage(address, DDSServerToServerMessageType::kResponderCall, std::move(responder_str));
    DestroyDeferredCallback(callback_ptr);
  });

  m_DeferredCallbackList.emplace(std::move(callback));
}

void DDSNodeState::CreateResolverRequest(const char * hostname, DDSDeferredCallback & callback, std::function<void(const DDSResolverRequest &)> && function)
{
  m_Resolver.CreateCallback(hostname, callback, std::move(function));
}

void DDSNodeState::QueryObjectData(int object_type_id, DDSKey key, const char * collection)
{
  m_Database->QueryDatabaseByKey(key, collection, [&](const char * data, int ec) { HandleQueryByKey(object_type_id, key, data, ec); });
}

void DDSNodeState::InsertObjectData(int object_type_id, DDSKey key, const char * collection, const char * data, DDSResponderCallData && responder_call)
{
  m_Database->QueryDatabaseInsert(key, collection, data, [this, responder_call](const char * data, int ec) mutable { HandleInsertResult(ec, responder_call); });
}

DDSNetworkBackend & DDSNodeState::GetBackend()
{
  return m_Backend;
}

DDSNodeNetworkService & DDSNodeState::GetNodeNetwork()
{
  return m_NodeNetwork;
}

DDSCoordinatorClientProtocol & DDSNodeState::GetCoordinatorConnection()
{
  return m_CoordinatorConnection;
}

DDSIncomingKeyspaceTransferManager & DDSNodeState::GetIncomingKeyspace()
{
  return m_IncomingKeyspace;
}

DDSOutgoingKeyspaceTransferManager & DDSNodeState::GetOutgoingKeyspace()
{
  return m_OutgoingKeyspace;
}

DDSNodeId DDSNodeState::GetLocalNodeId() const
{
  return m_LocalNodeId;
}

const DDSRoutingTable & DDSNodeState::GetRoutingTable() const
{
  return m_RoutingTable;
}

DDSKeyRange DDSNodeState::GetLocalKeyRange() const
{
  return m_LocalKeyRange;
}

uint64_t DDSNodeState::GetClientSecret() const
{
  return m_ClientSecret;
}

uint64_t DDSNodeState::GetServerSecret() const
{
  return m_ServerSecret;
}

uint32_t DDSNodeState::GetLocalInterface() const
{
  return m_LocalInterface;
}

int DDSNodeState::GetLocalPort() const
{
  return m_LocalPort;
}

void DDSNodeState::RecheckOutgoingTargetedMessages()
{
  auto itr = m_PendingTargetedMessages.begin();
  while(itr != m_PendingTargetedMessages.end())
  {
    auto itr_copy = itr;
    itr++;

    for (auto & msg : itr_copy->second)
    {
      if (KeyInKeyRange(itr_copy->first.m_ObjectKey, m_LocalKeyRange))
      {
        if (m_IncomingKeyspace.IsCompleteForKey(itr_copy->first))
        {
          for (auto & message : itr_copy->second)
          {
            HandleIncomingTargetedMessage(itr_copy->first, message.first, std::move(message.second));
          }

          m_PendingTargetedMessages.erase(itr_copy);
        }
      }
      else
      {
        DDSNodeId node_id = GetNodeIdForKey(itr_copy->first.m_ObjectKey);
        if (m_NodeNetwork.RequestNodeConnection(node_id))
        {
          for (auto & message : itr_copy->second)
          {
            m_NodeNetwork.SendMessageToServer(node_id, DDSGetServerMessage(message.first, message.second.c_str()));
          }

          m_PendingTargetedMessages.erase(itr_copy);
        }
      }
    }
  }
}

void DDSNodeState::HandleQueryByKey(int object_type_id, DDSKey key, const char * result_data, int ec)
{
  m_DataObjectList[object_type_id]->HandleLoadResult(key, result_data, ec);
}

void DDSNodeState::HandleInsertResult(int ec, DDSResponderCallData & responder_call)
{
  char result_code[128];
  snprintf(result_code, sizeof(result_code), "[%d]", ec);

  responder_call.m_MethodArgs = result_code;

  SendTargetedMessage(DDSDataObjectAddress{ responder_call.m_ObjectType, responder_call.m_Key },
    DDSServerToServerMessageType::kResponderCall, DDSGetServerMessage(responder_call));
}

void DDSNodeState::HandleIncomingTargetedMessage(DDSDataObjectAddress addr, DDSServerToServerMessageType type, std::string & message)
{
  m_DataObjectList[addr.m_ObjectType]->HandleMessage(addr.m_ObjectKey, type, message.c_str());
}

void DDSNodeState::DestroyDeferredCallback(DDSDeferredCallback * callback)
{
  for(auto itr = m_DeferredCallbackList.begin(); itr != m_DeferredCallbackList.end(); ++itr)
  {
    if (itr->get() == callback)
    {
      m_DeferredCallbackList.erase(itr);
      return;
    }
  }
}
