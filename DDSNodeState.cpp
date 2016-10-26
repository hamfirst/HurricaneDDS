
#include "DDSLog.h"
#include "DDSNodeState.h"
#include "DDSRoutingTable.h"
#include "DDSServerMessage.h"
#include "DDSEndpointFactoryBase.h"
#include "DDSDatabaseConnectionPool.h"

#include "DDSServerToServerMessages.refl.meta.h"
#include "DDSCoordinatorProtocolMessages.refl.meta.h"

#include <StormRefl/StormReflJsonStd.h>

#include <StormSockets/StormSocketClientFrontendWebsocket.h>
#include <StormSockets/StormSocketServerFrontendWebsocket.h>

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
  m_HttpClient(http_client_settings, m_Backend),
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
  m_Database->TriggerCallbacks();

  m_CoordinatorConnection.ProcessEvents();
  m_NodeNetwork.ProcessEvents();

  m_OutgoingKeyspace.Update();

  m_Resolver.Update();
  m_HttpClient.Update();
  m_TimerSystem.Update();

  for (auto & endpoint_factory : m_EndpointFactoryList)
  {
    endpoint_factory->ProcessEvents();
  }

  for (auto & website_factor : m_WebsiteFactoryList)
  {
    website_factor->ProcessEvents();
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

void DDSNodeState::GotMessageFromCoordinator(DDSServerToServerMessageType type, DDSCoordinatorProtocolMessageType coordinator_type, const char * data)
{
  if (type == DDSServerToServerMessageType::kTargetedMessage)
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
  else if (coordinator_type == DDSCoordinatorProtocolMessageType::kSharedObjectDelta)
  {
    DDSCoordinatorSharedObjectDelta delta;
    if (StormReflParseJson(delta, data) == false)
    {
      DDSLog::LogError("Invalid targeted message");
      return;
    }

    m_SharedObjects[delta.m_SharedObjectType - m_DataObjectList.size()]->ProcessDelta(delta);
  }
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
  else if (type == DDSServerToServerMessageType::kCreateSubscription ||
           type == DDSServerToServerMessageType::kCreateDataSubscription ||
           type == DDSServerToServerMessageType::kCreateExistSubscription ||
           type == DDSServerToServerMessageType::kCreateDataExistSubscription)
  {
    DDSCreateDataSubscription sub_data;
    if (StormReflParseJson(sub_data, data) == false)
    {
      DDSLog::LogError("Invalid targeted message");
      return;
    }

    SendTargetedMessage(DDSDataObjectAddress{ sub_data.m_ObjectType, sub_data.m_Key }, type, std::string(data));
  }
  else if (type == DDSServerToServerMessageType::kDestroySubscription)
  {
    DDSDestroySubscription sub_data;
    if (StormReflParseJson(sub_data, data) == false)
    {
      DDSLog::LogError("Invalid targeted message");
      return;
    }

    SendTargetedMessage(DDSDataObjectAddress{ sub_data.m_ObjectType, sub_data.m_Key }, type, std::string(data));
  }
  else if (type == DDSServerToServerMessageType::kSubscriptionDeleted)
  {
    DDSSubscriptionDeleted sub_data;
    if (StormReflParseJson(sub_data, data) == false)
    {
      DDSLog::LogError("Invalid targeted message");
      return;
    }
    
    SendTargetedMessage(DDSDataObjectAddress{ sub_data.m_ResponderObjectType, sub_data.m_ResponderKey }, type, std::string(data));
  }
  else if (type == DDSServerToServerMessageType::kUnlockObject)
  {
    DDSUnlockObject obj_data;
    if (StormReflParseJson(obj_data, data) == false)
    {
      DDSLog::LogError("Invalid targeted message");
      return;
    }

    SendTargetedMessage(DDSDataObjectAddress{ obj_data.m_ObjectType, obj_data.m_Key }, type, std::string(data));
  }
}

void DDSNodeState::SendTargetedMessage(DDSDataObjectAddress addr, DDSServerToServerMessageType type, std::string && message, bool force_process)
{
  if (m_QueueMessageDepth && force_process == false)
  {
    m_QueuedTargetedMessages.emplace(std::make_tuple(addr, type, message));
    return;
  }

  if (addr.m_ObjectType >= (int)m_DataObjectList.size())
  {
    m_CoordinatorConnection.SendMessageToCoordinator(DDSGetServerMessage(type, message.c_str()));
    return;
  }
  else if (KeyInKeyRange(addr.m_ObjectKey, m_LocalKeyRange))
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

void DDSNodeState::SendSubscriptionCreate(DDSCreateDataSubscription && req)
{
  if (req.m_ObjectType >= (int)m_DataObjectList.size())
  {
    DDSExportedSubscription sub_data;
    sub_data.m_DataPath = std::move(req.m_DataPath);
    sub_data.m_SubscriptionId = req.m_SubscriptionId;
    sub_data.m_ResponderKey = req.m_ResponderKey;
    sub_data.m_ResponderObjectType = req.m_ResponderObjectType;
    sub_data.m_ResponderMethodId = req.m_ResponderMethodId;
    sub_data.m_ResponderArgs = std::move(req.m_ReturnArg);
    sub_data.m_IsDataSubscription = false;
    sub_data.m_DeltaOnly = req.m_DeltaOnly;

    m_SharedObjects[req.m_ObjectType - m_DataObjectList.size()]->CreateSubscription(std::move(sub_data));
    return;
  }

  SendTargetedMessage(DDSDataObjectAddress{ req.m_ObjectType, req.m_Key }, DDSServerToServerMessageType::kCreateSubscription, StormReflEncodeJson(req));
}

void DDSNodeState::SendSubscriptionDestroy(const DDSDestroySubscription & destroy)
{
  if (destroy.m_ObjectType >= (int)m_DataObjectList.size())
  {
    m_SharedObjects[destroy.m_ObjectType - m_DataObjectList.size()]->DestroySubscription(DDSDataObjectAddress{ destroy.m_ObjectType, destroy.m_Key }, destroy.m_SubscriptionId);
    return;
  }

  SendTargetedMessage(DDSDataObjectAddress{ destroy.m_ObjectType, destroy.m_Key }, DDSServerToServerMessageType::kDestroySubscription, StormReflEncodeJson(destroy));
}

void DDSNodeState::ExportSharedSubscriptions(DDSDataObjectAddress addr, std::vector<std::pair<int, std::vector<DDSExportedSubscription>>> & exported_list)
{
  for (int index = 0; index < (int)m_SharedObjects.size(); index++)
  {
    m_SharedObjects[index]->ExportSubscriptions(addr, exported_list);
  }
}

void DDSNodeState::ImportSharedSubscriptions(DDSDataObjectAddress addr, std::vector<std::pair<int, std::vector<DDSExportedSubscription>>> & exported_list)
{
  for(auto & list : exported_list)
  {
    m_SharedObjects[list.first - m_SharedObjects.size()]->ImportSubscriptions(addr, std::move(list.second));
  }
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

int DDSNodeState::GetSharedObjectTypeIdForNameHash(uint32_t name_hash) const
{
  for (std::size_t index = 0; index < m_SharedObjects.size(); index++)
  {
    if (m_SharedObjects[index]->GetObjectClassNameHash() == name_hash)
    {
      return (int)index + (int)m_DataObjectList.size();
    }
  }

  DDSLog::LogError("Invalid object id request");
  return -1;
}

int DDSNodeState::GetTargetObjectIdForNameHash(uint32_t name_hash) const
{
  for (std::size_t index = 0; index < m_DataObjectList.size(); index++)
  {
    if (m_DataObjectList[index]->GetDataClassNameHash() == name_hash)
    {
      return (int)index;
    }
  }

  for (std::size_t index = 0; index < m_SharedObjects.size(); index++)
  {
    if (m_SharedObjects[index]->GetObjectClassNameHash() == name_hash)
    {
      return (int)index + (int)m_DataObjectList.size();
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

void DDSNodeState::CreateHttpRequest(const DDSHttpRequest & request, DDSDeferredCallback & callback, std::function<void(bool, const std::string &, const std::string &)> && function)
{
  m_HttpClient.CreateCallback(request, callback, std::move(function));
}

void DDSNodeState::CreateHttpRequest(const DDSHttpRequest & request, DDSResponderCallData && responder_data)
{
  std::unique_ptr<DDSDeferredCallback> callback = std::make_unique<DDSDeferredCallback>();
  DDSDeferredCallback * callback_ptr = callback.get();

  DDSDataObjectAddress address{ responder_data.m_ObjectType, responder_data.m_Key };

  m_HttpClient.CreateCallback(request, *callback.get(), [=](bool success, const std::string & data, const std::string & headers) mutable {

    responder_data.m_MethodArgs = "[" + StormReflEncodeJson(success) + "," + StormReflEncodeJson(data) + "," + StormReflEncodeJson(headers) + "]";
    std::string responder_str = StormReflEncodeJson(responder_data);
    SendTargetedMessage(address, DDSServerToServerMessageType::kResponderCall, std::move(responder_str));
    DestroyDeferredCallback(callback_ptr);
  });

  m_DeferredCallbackList.emplace(std::move(callback));
}

void DDSNodeState::CreateResolverRequest(const char * hostname, bool reverse_lookup, DDSDeferredCallback & callback, std::function<void(const DDSResolverRequest &)> && function)
{
  m_Resolver.CreateCallback(std::make_pair(hostname, reverse_lookup), callback, std::move(function));
}

void DDSNodeState::QueryObjectData(int object_type_id, DDSKey key, const char * collection)
{
  m_Database->QueryDatabaseByKey(key, collection, [this, object_type_id, key](const char * data, int ec) { HandleQueryByKey(object_type_id, key, data, ec); });
}

void DDSNodeState::QueryObjectData(const char * collection, const char * query, DDSResponderCallData && responder_call)
{
  DDSDataObjectAddress address{ responder_call.m_ObjectType, responder_call.m_Key };

  auto callback = [=](const char * data, int ec) mutable {

    std::string sb;
    StormReflJsonEncodeString(data, sb);

    responder_call.m_MethodArgs = std::string("[") + sb + "," + StormReflEncodeJson(ec) + "]";
    std::string responder_str = StormReflEncodeJson(responder_call);
    SendTargetedMessage(address, DDSServerToServerMessageType::kResponderCall, std::move(responder_str));
  };

  m_Database->QueryDatabaseCustom(query, collection, std::move(callback));
}

void DDSNodeState::InsertObjectData(int object_type_id, DDSKey key, const char * collection, const char * data, DDSResponderCallData && responder_call)
{
  m_Database->QueryDatabaseInsert(key, collection, data, [this, responder_call](const char * data, int ec) mutable { HandleInsertResult(ec, responder_call); });
}

void DDSNodeState::UpdateObjectData(int object_type_id, DDSKey key, const char * collection, const char * data, DDSResponderCallData * responder_call)
{
  if (responder_call)
  {
    m_DataObjectList[object_type_id]->LockObject(key);

    DDSResponderCallData responder = std::move(*responder_call);

    DDSUnlockObject unlock_msg;
    unlock_msg.m_Key = key;
    unlock_msg.m_ObjectType = object_type_id;
    unlock_msg.m_Data = data;

    auto callback = [=] (const char *, int ec) mutable {
      if (ec != 0)
      {
        unlock_msg.m_Data.clear();
        responder.m_MethodArgs = "[false]";
      }
      else
      {
        responder.m_MethodArgs = "[true]";
      }

      SendTargetedMessage(DDSDataObjectAddress{ object_type_id, key }, DDSServerToServerMessageType::kUnlockObject, StormReflEncodeJson(unlock_msg));
      SendTargetedMessage(DDSDataObjectAddress{ object_type_id, key }, DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(responder));
    };

    m_Database->QueryDatabaseUpsert(key, collection, data, callback);
  }
  else
  {
    auto callback = [](const char *, int ec) { 
      if (ec != 0)
      {
        DDSLog::LogError("Non failing update has failed");
      }
    };

    m_Database->QueryDatabaseUpsert(key, collection, data, callback);
  }
}

void DDSNodeState::BeginQueueingMessages()
{
  m_QueueMessageDepth++;
}

void DDSNodeState::EndQueueingMessages()
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

bool DDSNodeState::SendToLocalConnection(DDSConnectionId connection_id, const std::string & data)
{
  StormSockets::StormSocketConnectionId id;
  id.m_Index.Raw = connection_id.m_ConnectionId;

  return connection_id.m_EndpointFactory->SendData(id, data);
}

void DDSNodeState::DisconnectLocalConnection(DDSConnectionId connection_id)
{
  StormSockets::StormSocketConnectionId id;
  id.m_Index.Raw = connection_id.m_ConnectionId;

  connection_id.m_EndpointFactory->ForceDisconnect(id);
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
            HandleIncomingTargetedMessage(itr_copy->first, message.first, message.second);
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
    DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(responder_call));
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
