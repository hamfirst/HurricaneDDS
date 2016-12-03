#pragma once

#include "DDSObjectInterface.h"

class DDSCoordinatorState;
class DDSSharedObjectBase;

class DDSSharedObjectInterface : public DDSObjectInterface
{
public:
  DDSSharedObjectInterface(DDSCoordinatorState & node_state, DDSSharedObjectBase * data_store);
  DDSSharedObjectInterface(const DDSSharedObjectInterface & rhs) = default;
  DDSSharedObjectInterface(DDSSharedObjectInterface && rhs) = default;

  DDSKey GetLocalKey() override;
  int GetObjectTypeId() override;

  DDSRoutingTableNodeInfo GetNodeInfo(DDSKey key) override;

private:

  int GetObjectType(uint32_t object_type_name_hash) override;
  int GetDataObjectType(uint32_t object_type_name_hash) override;

  void SendMessageToObject(int target_object_type, DDSKey target_key, int target_method_id, std::string && message) override;
  void SendMessageToObjectWithResponderReturnArg(int target_object_type, DDSKey target_key, int target_method_id,
    int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && message, std::string && return_arg) override;
  void SendResponderCall(const DDSResponderCallBase & call_data) override;

  void InsertIntoDatabaseWithResponderReturnArg(const char * collection, int data_object_type, std::string && data, DDSKey data_key,
    int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg) override;

  void QueryDatabaseInternal(const char * collection, std::string && query,
    int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg) override;

  void CreateTimerInternal(std::chrono::system_clock::duration duration, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg) override;
  void CreateHttpRequestInternal(const DDSHttpRequest & request, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg) override;

  DDSKey CreateSubscriptionInternal(int target_object_type, DDSKey target_key, const char * path, int return_object_type,
    DDSKey return_key, int return_method_id, bool delta_only, std::string && return_arg) override;
  DDSKey CreateDataSubscriptionInternal(int target_object_type, DDSKey target_key, const char * path, int return_object_type,
    DDSKey return_key, int return_method_id, bool delta_only, std::string && return_arg) override;

  DDSKey CreateExistSubscriptionInternal(int target_object_type, DDSKey target_key, int return_object_type,
    DDSKey return_key, int return_method_id, std::string && return_arg) override;
  DDSKey CreateDataExistSubscriptionInternal(int target_object_type, DDSKey target_key, int return_object_type,
    DDSKey return_key, int return_method_id, std::string && return_arg) override;

  void DestroySubscriptionInternal(int return_object_type, DDSKey return_key, DDSKey subscription_id) override;
private:
  DDSCoordinatorState & m_CoordinatorState;
  DDSSharedObjectBase * m_DataStore;
};


