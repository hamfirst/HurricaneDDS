#pragma once

#include "DDSLog.h"
#include "DDSObjectInterface.h"
#include "DDSConnectionId.h"

class DDSNodeState;
class DDSDataObjectStoreBase;


class DDSNodeInterface : public DDSObjectInterface
{
public:
  DDSNodeInterface(DDSNodeState & node_state, DDSDataObjectStoreBase * data_store, DDSKey key);
  DDSNodeInterface(const DDSNodeInterface & rhs) = default;
  DDSNodeInterface(DDSNodeInterface && rhs) = default;

  void FinalizeObjectLoad();
  bool SendDataToLocalConnection(DDSConnectionId connection_id, const std::string & data);
  void DisconnectLocalConnection(DDSConnectionId connection_id);

  DDSKey GetLocalKey() override;
  int GetObjectTypeId() const override;

  template <typename DatabaseType, typename ReturnObject>
  void UpdateDatabase(const DatabaseType & data, void (ReturnObject::*return_func)(bool), ReturnObject * p_this)
  {
    if (GetObjectTypeId() != GetDataObjectType(StormReflTypeInfo<DatabaseType>::GetNameHash()))
    {
      DDSLog::LogError("Attemping to modify database from an external object");
      (p_this->*return_func)(false);
      return;
    }

    UpdateDatabase(DatabaseType::Collection(), GetObjectTypeId(), StormReflEncodeJson(data), GetLocalKey(), GetObjectTypeId(), GetLocalKey(),
      StormReflGetMemberFunctionIndex(return_func), std::string());
  }

  template <typename DatabaseType, typename ReturnObject, typename ReturnArg>
  void UpdateDatabase(const DatabaseType & data, void (ReturnObject::*return_func)(ReturnArg, bool), ReturnObject * p_this, ReturnArg && return_arg)
  {
    if (GetObjectTypeId() != GetDataObjectType(StormReflTypeInfo<DatabaseType>::GetNameHash()))
    {
      DDSLog::LogError("Attemping to modify database from an external object");
      (p_this->*return_func)(return_arg, false);
      return;
    }

    UpdateDatabase(DatabaseType::Collection(), GetObjectTypeId(), StormReflEncodeJson(data), GetLocalKey(), GetObjectTypeId(), GetLocalKey(),
      StormReflGetMemberFunctionIndex(return_func), StormReflEncodeJson(return_arg));
  }

  void DestroySelf() override;

  DDSRoutingTableNodeInfo GetNodeInfo(DDSKey key) override;

  time_t GetNetworkTime() override;

private:

  int GetObjectType(uint32_t object_type_name_hash) override;
  int GetDataObjectType(uint32_t object_type_name_hash) override;
  int GetSharedObjectType(uint32_t object_type_name_hash) override;

  const void * GetSharedObjectPointer(uint32_t object_type_name_hash) override;
  
  void SendMessageToObject(int target_object_type, DDSKey target_key, int target_method_id, std::string && message) override;
  void SendMessageToObjectWithResponderReturnArg(int target_object_type, DDSKey target_key, int target_method_id,
    int responder_object_type, DDSKey responder_key, int responder_method_id, int err_method_id, std::string && message, std::string && return_arg) override;
  void SendMessageToSharedObject(int target_object_type, int target_method_id, std::string && message) override;
  void SendMessageToSharedObjectWithResponderReturnArg(int target_object_type, int target_method_id,
    int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && message, std::string && return_arg) override;
  void SendResponderCall(const DDSResponderCallBase & call_data) override;

  void InsertIntoDatabaseWithResponderReturnArg(const char * collection, int data_object_type, std::string && data, DDSKey data_key,
    int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg) override;

  void QueryDatabaseInternal(const char * collection, std::string && query,
    int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg) override;
  void UpdateDatabaseInternal(const char * collection, int data_object_type, std::string && data, DDSKey data_key,
    int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg);

  void CreateTimerInternal(std::chrono::system_clock::duration duration, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg) override;
  void CreateHttpRequestInternal(const DDSHttpRequest & request, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg) override;

  DDSKey CreateSubscriptionInternal(int target_object_type, DDSKey target_key, const char * path, int return_object_type,
    DDSKey return_key, int return_method_id, bool delta_only, std::string && return_arg, int err_method_id, bool force_load, bool data_sub) override;

  void DestroySubscriptionInternal(int return_object_type, DDSKey return_key, DDSKey subscription_id) override;


private:

  DDSNodeState & m_NodeState;
  DDSDataObjectStoreBase * m_DataStore;
  DDSKey m_Key;
};
