#pragma once

#include <memory>

#include "DDSLog.h"
#include "DDSObjectInterface.h"
#include "DDSConnectionId.h"
#include "DDSSharedLocalCopyData.h"
#include "DDSSharedLocalCopyPtr.h"

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

    UpdateDatabaseInternal(DatabaseType::Collection(), GetObjectTypeId(), StormReflEncodeJson(data), GetLocalKey(), GetObjectTypeId(), GetLocalKey(),
      StormReflGetMemberFunctionIndex(return_func), std::string());
  }

  template <typename DatabaseType, typename ReturnObject, typename ReturnArg, typename FuncArg>
  void UpdateDatabase(const DatabaseType & data, void (ReturnObject::*return_func)(FuncArg, bool), ReturnObject * p_this, ReturnArg && return_arg)
  {
    static_assert(std::is_convertible<ReturnArg, FuncArg>::value, "Invalid call args for function");

    if (GetObjectTypeId() != GetDataObjectType(StormReflTypeInfo<DatabaseType>::GetNameHash()))
    {
      DDSLog::LogError("Attemping to modify database from an external object");
      (p_this->*return_func)(return_arg, false);
      return;
    }

    UpdateDatabaseInternal(DatabaseType::Collection(), GetObjectTypeId(), StormReflEncodeJson(data), GetLocalKey(), GetObjectTypeId(), GetLocalKey(),
      StormReflGetMemberFunctionIndex(return_func), StormReflEncodeJson(return_arg));
  }

  template <typename TargetSubDataType>
  static std::unique_ptr<DDSBaseSharedLocalCopyData> CreateSharedLocalCopyData()
  {
    return std::make_unique<DDSSharedLocalCopyData<TargetSubDataType>>();
  }

  template <typename TargetObject, typename TargetSubDataType, typename ReturnObject>
  std::pair<DDSKey, DDSKey> CreateSharedLocalCopy(
    const DDSSubscriptionTarget<TargetObject> & sub, 
    const DDSSubscriptionTarget<TargetSubDataType> & target_data, DDSKey target_key, const char * path,
    void (ReturnObject::*return_func)(std::string data, int version), void (ReturnObject::*err_func)() = nullptr)
  {
    return CreateSharedLocalCopyInternal(StormReflTypeInfo<TargetObject>::GetNameHash(), target_key, path,
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()),
      GetLocalKey(), StormReflGetMemberFunctionIndex(return_func), 
      std::string(), StormReflGetMemberFunctionIndex(err_func),
      &DDSNodeInterface::CreateSharedLocalCopyData<TargetSubDataType>);
  }

  template <typename TargetObject, typename TargetSubDataType, typename ReturnObject, typename ReturnArg>
  std::pair<DDSKey, DDSKey> CreateSharedLocalCopy(
    const DDSSubscriptionTarget<TargetObject> & sub,
    const DDSSubscriptionTarget<TargetSubDataType> & target_data, DDSKey target_key, const char * path,
    void (ReturnObject::*return_func)(ReturnArg return_arg, std::string data, int version), 
    const ReturnArg & return_arg, void (ReturnObject::*err_func)() = nullptr)
  {
    return CreateSharedLocalCopyInternal(StormReflTypeInfo<TargetObject>::GetNameHash(), target_key, path,
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()),
      GetLocalKey(), StormReflGetMemberFunctionIndex(return_func),
      StormReflEncodeJson(return_arg), err_func != nullptr ? StormReflGetMemberFunctionIndex(err_func) : -1, 
      &DDSNodeInterface::CreateSharedLocalCopyData<TargetSubDataType>);
  }

  template <typename TargetObject, typename TargetSubDataType>
  DDSSharedLocalCopyPtr<TargetSubDataType> GetSharedLocalCopyPtr(DDSKey target_key, const char * path, int version)
  {
    DDSSharedLocalCopyPtr<TargetSubDataType> ptr;

    GetSharedLocalCopyPtr(ptr, StormReflTypeInfo<TargetObject>::GetNameHash(), 
      target_key, path, version, &DDSNodeInterface::CreateSharedLocalCopyData<TargetSubDataType>);
    return ptr;
  }

  void DestroySharedLocalCopy(std::pair<DDSKey, DDSKey> subscription_info)
  {
    DestroySharedLocalCopyInternal(subscription_info);
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
  void QueryDatabaseByKeyInternal(const char * collection, DDSKey key,
    int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg) override;

  void UpdateDatabaseInternal(const char * collection, int data_object_type, std::string && data, DDSKey data_key,
    int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg);

  void DeleteFromDatabaseInternal(const char * collection, DDSKey key) override;

  void CreateTimerInternal(std::chrono::system_clock::duration duration, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg) override;
  void CreateHttpRequestInternal(const DDSHttpRequest & request, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg) override;

  DDSKey CreateSubscriptionInternal(int target_object_type, DDSKey target_key, const char * path, int return_object_type,
    DDSKey return_key, int return_method_id, bool delta_only, std::string && return_arg, int err_method_id, bool force_load, bool data_sub) override;

  void DestroySubscriptionInternal(int return_object_type, DDSKey return_key, DDSKey subscription_id) override;

  std::pair<DDSKey, DDSKey> CreateSharedLocalCopyInternal(
    uint32_t target_object_type_name_hash, DDSKey target_key, const char * path, int return_object_type,
    DDSKey return_key, int return_method_id, std::string && return_arg, int err_method_id,
    std::unique_ptr<DDSBaseSharedLocalCopyData>(*CreateFunc)());

  void DestroySharedLocalCopyInternal(std::pair<DDSKey, DDSKey> subscription_info);

  void GetSharedLocalCopyPtr(DDSSharedLocalCopyPtrBase & ptr, uint32_t target_object_type_name_hash, 
    DDSKey target_key, const char * path, int version, std::unique_ptr<DDSBaseSharedLocalCopyData>(*CreateFunc)());

private:

  DDSNodeState & m_NodeState;
  DDSDataObjectStoreBase * m_DataStore;
  DDSKey m_Key;
};
