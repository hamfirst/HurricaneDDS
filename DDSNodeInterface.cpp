
#include "DDSNodeInterface.h"
#include "DDSNodeState.h"

#include "DDSServerToServerMessages.refl.meta.h"

#include <StormRefl\StormReflJsonStd.h>

DDSNodeInterface::DDSNodeInterface(DDSNodeState & node_state, DDSDataObjectStoreBase * data_store, DDSKey key) :
  m_NodeState(node_state), m_DataStore(data_store), m_Key(key)
{

}

void DDSNodeInterface::FinalizeObjectLoad()
{
  m_DataStore->FinalizeObjectLoad(m_Key);
}

int DDSNodeInterface::GetObjectType(uint32_t object_type_name_hash)
{
  return m_NodeState.GetDataObjectTypeIdForNameHash(object_type_name_hash);
}

int DDSNodeInterface::GetDataObjectType(uint32_t object_type_name_hash)
{
  return m_NodeState.GetDatabaseObjectTypeIdForNameHash(object_type_name_hash);
}

void DDSNodeInterface::SendMessageToObject(int target_object_type, DDSKey target_key, int target_method_id, std::string && message)
{
  DDSTargetedMessage packet;
  packet.m_Key = target_key;
  packet.m_ObjectType = target_object_type;
  packet.m_MethodId = target_method_id;
  packet.m_MethodArgs = message;

  m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ target_object_type, target_key }, DDSServerToServerMessageType::kTargetedMessage, StormReflEncodeJson(packet));
}

void DDSNodeInterface::SendMessageToObjectWithResponder(int target_object_type, DDSKey target_key, int target_method_id,
  int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && message)
{
  DDSTargetedMessageWithResponder packet;
  packet.m_Key = target_key;
  packet.m_ObjectType = target_object_type;
  packet.m_MethodId = target_method_id;
  packet.m_MethodArgs = message;
  packet.m_ResponderKey = responder_key;
  packet.m_ResponderObjectType = responder_object_type;
  packet.m_ResponderMethodId = responder_method_id;

  m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ target_object_type, target_key }, DDSServerToServerMessageType::kTargetedMessageResponder, StormReflEncodeJson(packet));
}

void DDSNodeInterface::SendMessageToObjectWithResponderReturnArg(int target_object_type, DDSKey target_key, int target_method_id,
  int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg, std::string && message)
{
  DDSTargetedMessageWithResponder packet;
  packet.m_Key = target_key;
  packet.m_ObjectType = target_object_type;
  packet.m_MethodId = target_method_id;
  packet.m_MethodArgs = message;
  packet.m_ResponderKey = responder_key;
  packet.m_ResponderObjectType = responder_object_type;
  packet.m_ResponderMethodId = responder_method_id;
  packet.m_ReturnArg = return_arg;

  m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ target_object_type, target_key }, DDSServerToServerMessageType::kTargetedMessageResponder, StormReflEncodeJson(packet));
}

void DDSNodeInterface::InsertIntoDatabaseWithResponderReturnArg(const char * collection, int data_object_type, std::string && data, DDSKey data_key,
  int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg)
{
  DDSResponderCallData call_data;
  call_data.m_Key = responder_key;
  call_data.m_ObjectType = responder_object_type;
  call_data.m_MethodId = responder_method_id;
  call_data.m_ResponderArgs = return_arg;

  m_NodeState.InsertObjectData(data_object_type, data_key, collection, data.c_str(), std::move(call_data));
}

void DDSNodeInterface::CreateTimer(std::chrono::system_clock::duration duration, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg)
{
  DDSResponderCallData call_data;
  call_data.m_Key = key;
  call_data.m_ObjectType = data_object_type;
  call_data.m_MethodId = target_method_id;
  call_data.m_ResponderArgs = return_arg;

  m_NodeState.CreateTimer(duration, std::move(call_data));
}

void DDSNodeInterface::CreateHttpRequest(const char * url, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg)
{
  DDSResponderCallData call_data;
  call_data.m_Key = key;
  call_data.m_ObjectType = data_object_type;
  call_data.m_MethodId = target_method_id;
  call_data.m_ResponderArgs = return_arg;

  m_NodeState.CreateHttpRequest(url, std::move(call_data));
}
