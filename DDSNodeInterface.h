#pragma once

#include "DDSInterface.h"
#include "DDSConnectionId.h"

class DDSNodeState;
class DDSDataObjectStoreBase;


class DDSNodeInterface : public DDSInterface
{
public:
  DDSNodeInterface(DDSNodeState & node_state, DDSDataObjectStoreBase * data_store, DDSKey key);
  DDSNodeInterface(const DDSNodeInterface & rhs) = default;
  DDSNodeInterface(DDSNodeInterface && rhs) = default;

  void FinalizeObjectLoad();
  bool SendDataToLocalConnection(DDSConnectionId connection_id, const std::string & data);

  template <typename DatabaseType, typename ReturnObject>
  void UpdateDatabase(const DatabaseType & data, void (ReturnObject::*return_func)(bool), ReturnObject * p_this)
  {
    if (GetObjectTypeId() != GetDataObjectType(StormReflTypeInfo<TargetDataObject>::GetNameHash()))
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
    if (GetObjectTypeId() != GetDataObjectType(StormReflTypeInfo<TargetDataObject>::GetNameHash()))
    {
      DDSLog::LogError("Attemping to modify database from an external object");
      (p_this->*return_func)(return_arg, false);
      return;
    }

    UpdateDatabase(DatabaseType::Collection(), GetObjectTypeId(), StormReflEncodeJson(data), GetLocalKey(), GetObjectTypeId(), GetLocalKey(),
      StormReflGetMemberFunctionIndex(return_func), StormReflEncodeJson(return_arg));
  }

private:

  DDSKey GetLocalKey() override;
  int GetObjectTypeId() override;

  int GetObjectType(uint32_t object_type_name_hash) override;
  int GetDataObjectType(uint32_t object_type_name_hash) override;
  
  void SendMessageToObject(int target_object_type, DDSKey target_key, int target_method_id, std::string && message) override;
  void SendMessageToObjectWithResponderReturnArg(int target_object_type, DDSKey target_key, int target_method_id,
    int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && message, std::string && return_arg) override;
  void SendResponderCall(const DDSResponderCallBase & call_data) override;

  void InsertIntoDatabaseWithResponderReturnArg(const char * collection, int data_object_type, std::string && data, DDSKey data_key,
    int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg) override;

  void QueryDatabase(const char * collection, std::string && query,
    int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg) override;
  void UpdateDatabase(const char * collection, int data_object_type, std::string && data, DDSKey data_key,
    int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg);

  void CreateTimer(std::chrono::system_clock::duration duration, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg) override;
  void CreateHttpRequest(const char * url, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg) override;

  DDSKey CreateSubscription(int target_object_type, DDSKey target_key, const char * path, int return_object_type,
    DDSKey return_key, int return_method_id, bool delta_only, std::string && return_arg) override;
  DDSKey CreateDataSubscription(int target_object_type, DDSKey target_key, const char * path, int return_object_type,
    DDSKey return_key, int return_method_id, bool delta_only, std::string && return_arg) override;

  void DestroySubscription(int return_object_type, DDSKey return_key, DDSKey subscription_id) override;

private:

  DDSNodeState & m_NodeState;
  DDSDataObjectStoreBase * m_DataStore;
  DDSKey m_Key;
};
