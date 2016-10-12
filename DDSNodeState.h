#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>

#include "DDSNodeId.h"
#include "DDSDataObjectAddress.h"
#include "DDSDataObjectStoreBase.h"
#include "DDSRoutingTable.h"
#include "DDSDatabaseTypes.h"
#include "DDSTimerSystem.h"
#include "DDSHttpClient.h"
#include "DDSResolver.h"
#include "DDSNetworkBackend.h"
#include "DDSNodeNetworkService.h"
#include "DDSCoordinatorClientProtocol.h"
#include "DDSDatabaseConnectionPool.h"
#include "DDSIncomingKeyspaceTransferManager.h"
#include "DDSOutgoingKeyspaceTransferManager.h"
#include "DDSServerToServerMessages.refl.h"

struct DDSResponder;
struct DDSResponderCallData;

class DDSNodeState
{
public:

  template <typename TypeList, typename ... EndpointFactoryTypes>
  DDSNodeState(
    const TypeList & type_list,
    const StormSockets::StormSocketInitSettings & backend_settings,
    const StormSockets::StormSocketServerFrontendWebsocketSettings & node_server_settings,
    const StormSockets::StormSocketClientFrontendWebsocketSettings & node_client_settings,
    const StormSockets::StormSocketClientFrontendHttpSettings & http_client_settings,
    const DDSCoordinatorClientSettings & coordinator_settings,
    const DDSDatabaseSettings & database_settings,
    EndpointFactoryTypes && ... endpoints) :
    DDSNodeState(TypeList::NumTypes, backend_settings, node_server_settings, node_client_settings, http_client_settings, coordinator_settings, database_settings)
  {
    auto func = type_list();
    func(*this, m_DataObjectList);

    InitEndpointFactories(std::forward<EndpointFactoryTypes>(endpoints)...);
  }

  ~DDSNodeState() = default;

  void ProcessEvents();

  int GetDataObjectTypeIdForNameHash(uint32_t name_hash) const;
  int GetDatabaseObjectTypeIdForNameHash(uint32_t name_hash) const;

  template <typename DataType>
  int GetDataObjectTypeId() const
  {
    return GetDataObjectTypeIdForNameHash(StormReflTypeInfo<DataType>::GetNameHash());
  }

  template <typename DatabaseType>
  int GetDatabaseObjectTypeId() const
  {
    return GetDataObjectTypeIdForNameHash(StormReflTypeInfo<DatabaseType>::GetNameHash());
  }

  bool IsReadyToCreateObjects();
  bool CreateNewDataObject(int object_type_id, DDSKey & output_key);
  bool DestroyDataObject(int object_type_id, DDSKey key);

  template <typename DataType, typename ... Args, typename ... FuncArgs>
  bool CallObjectLocal(DDSKey key, void (DataType::* func)(FuncArgs...), Args && ... args)
  {
    int data_type = GetDataObjectTypeId<DataType>();
    if (data_type == -1)
    {
      return false;
    }

    auto & data_store = GetDataObjectStore(data_type);
    auto data_val = static_cast<DataType *>(data_store.GetDataObjectForKey(key));

    if (data_val == nullptr)
    {
      return false;
    }

    data_store.BeginObjectModification(key);
    (data_val->*func)(std::forward<Args>(args)...);
    data_store.EndObjectModification();
    return true;
  }

  template <typename DataType, typename ... Args, typename ... FuncArgs>
  void CallObjectRemote(DDSKey key, void (DataType::* func)(FuncArgs...), Args && ... args)
  {
    int data_type = GetDataObjectTypeId<DataType>();
    if (data_type == -1)
    {
      return;
    }

    DDSNodeInterface node_interface(*this, &GetDataObjectStore(data_type), key);
    node_interface.Call(func, key, std::forward<Args>(args)...);
  }

  void CreateTimer(std::chrono::system_clock::duration duration, DDSDeferredCallback & callback, std::function<void()> && function);
  void CreateTimer(std::chrono::system_clock::duration duration, DDSResponderCallData && responder_data);

  void CreateHttpRequest(const char * url, DDSDeferredCallback & callback, std::function<void(bool, const std::string &)> && function);
  void CreateHttpRequest(const char * url, DDSResponderCallData && responder_data);

  void CreateResolverRequest(const char * hostname, DDSDeferredCallback & callback, std::function<void(const DDSResolverRequest &)> && function);

private:

  friend class DDSCoordinatorClientProtocol;
  friend class DDSOutgoingKeyspaceTransfer;
  friend class DDSServerToServerReceiver;
  friend class DDSServerToServerSender;
  friend class DDSNodeNetworkService;
  friend class DDSNodeInterface;
  friend class DDSEndpointFactoryBase;
  friend class DDSEndpointInterface;
  friend class DDSHttpClient;
  friend struct DDSResponder;

  template <class DataType, class DatabaseBackedType>
  friend class DDSDataObjectStore;

  friend void DDSResponderCallFinalize(const DDSResponder & responder, const DDSResponderCallData & call_data);

  DDSNodeState(
    int num_data_object_types,
    const StormSockets::StormSocketInitSettings & backend_settings,
    const StormSockets::StormSocketServerFrontendWebsocketSettings & node_server_settings,
    const StormSockets::StormSocketClientFrontendWebsocketSettings & node_client_settings,
    const StormSockets::StormSocketClientFrontendHttpSettings & http_client_settings,
    const DDSCoordinatorClientSettings & coordinator_settings,
    const DDSDatabaseSettings & database_settings);

  template <typename EndpointFactoryType, typename ... Remaining>
  void InitEndpointFactories(EndpointFactoryType && factory_type, Remaining && ... remaining)
  {
    factory_type(*this, m_EndpointFactoryList);
    InitEndpointFactories(std::forward<Remaining>(remaining)...);
  }

  void InitEndpointFactories()
  {

  }

  void SendTargetedMessage(DDSDataObjectAddress addr, DDSServerToServerMessageType type, std::string && message);

  void GotInitialCoordinatorSync(DDSNodeId node_id, const DDSRoutingTable & routing_table, bool initial_node, uint64_t server_secret, uint64_t client_secret);
  void GotNewRoutingTable(const DDSRoutingTable & routing_table);
  void GotMessageFromServer(DDSNodeId node_id, DDSServerToServerMessageType type, const char * data);

  void QueryObjectData(int object_type_id, DDSKey key, const char * collection);
  void InsertObjectData(int object_type_id, DDSKey key, const char * collection, const char * data, DDSResponderCallData && responder_call);

  DDSNodeId GetNodeIdForKey(DDSKey key) const;

  DDSDataObjectStoreBase & GetDataObjectStore(int object_type_id);

  DDSNetworkBackend & GetBackend();
  DDSNodeNetworkService & GetNodeNetwork();
  DDSCoordinatorClientProtocol & GetCoordinatorConnection();

  DDSIncomingKeyspaceTransferManager & GetIncomingKeyspace();
  DDSOutgoingKeyspaceTransferManager & GetOutgoingKeyspace();

  DDSNodeId GetLocalNodeId() const;
  const DDSRoutingTable & GetRoutingTable() const;
  DDSKeyRange GetLocalKeyRange() const;

  uint64_t GetClientSecret() const;
  uint64_t GetServerSecret() const;

  uint32_t GetLocalInterface() const;
  int GetLocalPort() const;

  void RecheckOutgoingTargetedMessages();

  void HandleQueryByKey(int object_type_id, DDSKey key, const char * result_data, int ec);
  void HandleInsertResult(int ec, DDSResponderCallData & responder_call);
  void HandleIncomingTargetedMessage(DDSDataObjectAddress addr, DDSServerToServerMessageType type, std::string & message);
  void DestroyDeferredCallback(DDSDeferredCallback * callback);

private:

  DDSNetworkBackend m_Backend;
  DDSNodeNetworkService m_NodeNetwork;
  DDSCoordinatorClientProtocol m_CoordinatorConnection;

  DDSIncomingKeyspaceTransferManager m_IncomingKeyspace;
  DDSOutgoingKeyspaceTransferManager m_OutgoingKeyspace;

  DDSTimerSystem m_TimerSystem;
  DDSHttpClient m_HttpClient;
  DDSResolver m_Resolver;

  DDSNodeId m_LocalNodeId = 0;
  DDSRoutingTable m_RoutingTable;
  DDSKeyRange m_LocalKeyRange;
  std::vector<std::pair<DDSNodeId, DDSKeyRange>> m_RoutingKeyRanges;

  std::map<DDSDataObjectAddress, std::vector<std::pair<DDSServerToServerMessageType, std::string>>> m_PendingTargetedMessages;

  std::vector<std::unique_ptr<DDSDataObjectStoreBase>> m_DataObjectList;
  std::vector<std::unique_ptr<DDSEndpointFactoryBase>> m_EndpointFactoryList;

  std::set<std::unique_ptr<DDSDeferredCallback>> m_DeferredCallbackList;

  std::unique_ptr<DDSDatabaseConnectionPool> m_Database;

  uint32_t m_LocalInterface = 0;
  int m_LocalPort = 0;

  uint64_t m_ClientSecret = 0;
  uint64_t m_ServerSecret = 0;
};

