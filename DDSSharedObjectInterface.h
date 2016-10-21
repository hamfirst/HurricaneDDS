#pragma once

#include "DDSInterface.h"

class DDSCoordinatorState;
class DDSSharedObjectBase;

class DDSSharedObjectInterface : public DDSInterface
{
public:
  DDSSharedObjectInterface(DDSCoordinatorState & node_state, DDSSharedObjectBase * data_store);
  DDSSharedObjectInterface(const DDSSharedObjectInterface & rhs) = default;
  DDSSharedObjectInterface(DDSSharedObjectInterface && rhs) = default;

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

  void CreateTimer(std::chrono::system_clock::duration duration, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg) override;
  void CreateHttpRequest(const char * url, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg) override;

  DDSKey CreateSubscription(int target_object_type, DDSKey target_key, const char * path, int return_object_type,
    DDSKey return_key, int return_method_id, bool delta_only, std::string && return_arg) override;
  DDSKey CreateDataSubscription(int target_object_type, DDSKey target_key, const char * path, int return_object_type,
    DDSKey return_key, int return_method_id, bool delta_only, std::string && return_arg) override;

  void DestroySubscription(int return_object_type, DDSKey return_key, DDSKey subscription_id) override;

private:
  DDSCoordinatorState & m_CoordinatorState;
  DDSSharedObjectBase * m_DataStore;
};


