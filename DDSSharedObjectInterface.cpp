
#include "DDSSharedObjectInterface.h"
#include "DDSCoordinatorState.h"
#include "DDSRandom.h"
#include "DDSLog.h"

#include "DDSCoordinatorProtocolMessages.refl.meta.h"

#include <StormRefl/StormReflJsonStd.h>

DDSSharedObjectInterface::DDSSharedObjectInterface(DDSCoordinatorState & coordinator_state, DDSSharedObjectBase * data_store) :
  m_CoordinatorState(coordinator_state), m_DataStore(data_store)
{

}

DDSKey DDSSharedObjectInterface::GetLocalKey()
{
  return 0;
}

int DDSSharedObjectInterface::GetObjectTypeId() const
{
  return m_DataStore->GetObjectTypeId();
}

void DDSSharedObjectInterface::DestroySelf()
{
  DDSLog::LogError("Shared object is trying to destroy itself");
}

int DDSSharedObjectInterface::GetObjectType(uint32_t object_type_name_hash)
{
  return m_CoordinatorState.GetTargetObjectIdForNameHash(object_type_name_hash);
}

int DDSSharedObjectInterface::GetDataObjectType(uint32_t object_type_name_hash)
{
  return m_CoordinatorState.GetDatabaseObjectTypeIdForNameHash(object_type_name_hash);
}

int DDSSharedObjectInterface::GetSharedObjectType(uint32_t object_type_name_hash)
{
  return m_CoordinatorState.GetSharedObjectTypeIdForNameHash(object_type_name_hash);
}

void DDSSharedObjectInterface::SendMessageToObject(int target_object_type, DDSKey target_key, int target_method_id, std::string && message)
{
  DDSCoordinatorTargetedMessage packet;
  packet.m_Key = target_key;
  packet.m_ObjectType = target_object_type;
  packet.m_MethodId = target_method_id;
  packet.m_MethodArgs = message;

  m_CoordinatorState.SendTargetedMessage(DDSDataObjectAddress{ target_object_type, target_key }, DDSCoordinatorProtocolMessageType::kTargetedMessage, StormReflEncodeJson(packet));
}

void DDSSharedObjectInterface::SendMessageToObjectWithResponderReturnArg(int target_object_type, DDSKey target_key, int target_method_id,
  int responder_object_type, DDSKey responder_key, int responder_method_id, int err_method_id, std::string && message, std::string && return_arg)
{
  DDSCoordinatorTargetedMessageWithResponder packet;
  packet.m_Key = target_key;
  packet.m_ObjectType = target_object_type;
  packet.m_MethodId = target_method_id;
  packet.m_MethodArgs = message;
  packet.m_ResponderKey = responder_key;
  packet.m_ResponderObjectType = responder_object_type;
  packet.m_ResponderMethodId = responder_method_id;
  packet.m_ErrorMethodId = err_method_id;
  packet.m_ReturnArg = return_arg;

  m_CoordinatorState.SendTargetedMessage(DDSDataObjectAddress{ target_object_type, target_key }, DDSCoordinatorProtocolMessageType::kTargetedMessageResponder, StormReflEncodeJson(packet));
}

void DDSSharedObjectInterface::SendMessageToSharedObject(int target_object_type, int target_method_id, std::string && message)
{
  DDSCoordinatorTargetedMessage packet;
  packet.m_Key = 0;
  packet.m_ObjectType = target_object_type;
  packet.m_MethodId = target_method_id;
  packet.m_MethodArgs = message;

  m_CoordinatorState.SendTargetedMessage(DDSDataObjectAddress{ target_object_type, 0 }, DDSCoordinatorProtocolMessageType::kTargetedMessage, StormReflEncodeJson(packet));
}

void DDSSharedObjectInterface::SendMessageToSharedObjectWithResponderReturnArg(int target_object_type, int target_method_id,
  int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && message, std::string && return_arg)
{
  DDSCoordinatorTargetedMessageWithResponder packet;
  packet.m_Key = 0;
  packet.m_ObjectType = target_object_type;
  packet.m_MethodId = target_method_id;
  packet.m_MethodArgs = message;
  packet.m_ResponderKey = responder_key;
  packet.m_ResponderObjectType = responder_object_type;
  packet.m_ResponderMethodId = responder_method_id;
  packet.m_ReturnArg = return_arg;

  m_CoordinatorState.SendTargetedMessage(DDSDataObjectAddress{ target_object_type, 0 }, DDSCoordinatorProtocolMessageType::kTargetedMessageResponder, StormReflEncodeJson(packet));
}


void DDSSharedObjectInterface::SendResponderCall(const DDSResponderCallBase & call_data)
{
  m_CoordinatorState.SendTargetedMessage(DDSDataObjectAddress{ call_data.m_ObjectType, call_data.m_Key }, DDSCoordinatorProtocolMessageType::kResponderCall, StormReflEncodeJson(call_data));
}

void DDSSharedObjectInterface::InsertIntoDatabaseWithResponderReturnArg(const char * collection, int data_object_type, std::string && data, DDSKey data_key,
  int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg)
{
  DDSCoordinatorResponderCallData call_data;
  call_data.m_Key = responder_key;
  call_data.m_ObjectType = responder_object_type;
  call_data.m_MethodId = responder_method_id;
  call_data.m_ResponderArgs = return_arg;

  m_CoordinatorState.InsertObjectData(data_object_type, data_key, collection, data.c_str(), std::move(call_data));
}

void DDSSharedObjectInterface::QueryDatabaseInternal(const char * collection, std::string && query,
  int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg)
{
  DDSCoordinatorResponderCallData call_data;
  call_data.m_Key = responder_key;
  call_data.m_ObjectType = responder_object_type;
  call_data.m_MethodId = responder_method_id;
  call_data.m_ResponderArgs = return_arg;

  m_CoordinatorState.QueryObjectData(collection, query.c_str(), std::move(call_data));
}

void DDSSharedObjectInterface::CreateTimerInternal(std::chrono::system_clock::duration duration, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg)
{
  DDSCoordinatorResponderCallData call_data;
  call_data.m_Key = key;
  call_data.m_ObjectType = data_object_type;
  call_data.m_MethodId = target_method_id;
  call_data.m_ResponderArgs = return_arg;

  m_CoordinatorState.CreateTimer(duration, std::move(call_data));
}

void DDSSharedObjectInterface::CreateHttpRequestInternal(const DDSHttpRequest & request, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg)
{
  DDSCoordinatorResponderCallData call_data;
  call_data.m_Key = key;
  call_data.m_ObjectType = data_object_type;
  call_data.m_MethodId = target_method_id;
  call_data.m_ResponderArgs = return_arg;

  m_CoordinatorState.CreateHttpRequest(request, std::move(call_data));
}

DDSKey DDSSharedObjectInterface::CreateSubscriptionInternal(int target_object_type, DDSKey target_key, const char * path, int return_object_type,
  DDSKey return_key, int return_method_id, bool delta_only, std::string && return_arg, int err_method_id, bool force_load, bool data_sub)
{
  DDSKey subscription_id = DDSGetRandomNumber64();

  DDSCoordinatorCreateSubscription sub_data;
  sub_data.m_DataPath = path;
  sub_data.m_Key = target_key;
  sub_data.m_ObjectType = target_object_type;
  sub_data.m_SubscriptionId = subscription_id;
  sub_data.m_ResponderObjectType = return_object_type;
  sub_data.m_ResponderKey = return_key;
  sub_data.m_ResponderMethodId = return_method_id;
  sub_data.m_ErrorMethodId = err_method_id;
  sub_data.m_ReturnArg = return_arg;
  sub_data.m_DeltaOnly = delta_only;
  sub_data.m_ForceLoad = force_load;
  sub_data.m_DataSubscription = data_sub;

  DDSExportedRequestedSubscription req_sub;
  req_sub.m_ObjectType = target_object_type;
  req_sub.m_Key = target_key;
  req_sub.m_SubscriptionId = subscription_id;

  m_DataStore->AssignRequestedSubscription(req_sub);
  m_CoordinatorState.SendTargetedMessage(DDSDataObjectAddress{ target_object_type, target_key },
    DDSCoordinatorProtocolMessageType::kCreateSubscription, StormReflEncodeJson(sub_data));

  return subscription_id;
}

void DDSSharedObjectInterface::DestroySubscriptionInternal(int return_object_type, DDSKey return_key, DDSKey subscription_id)
{
  DDSCoordinatorDestroySubscription sub_data;
  sub_data.m_Key = return_key;
  sub_data.m_ObjectType = return_object_type;
  sub_data.m_SubscriptionId = subscription_id;

  m_DataStore->RemoveRequestedSubscription(subscription_id);
  m_CoordinatorState.SendTargetedMessage(DDSDataObjectAddress{ return_object_type, return_key },
    DDSCoordinatorProtocolMessageType::kDestroySubscription, StormReflEncodeJson(sub_data));
}

DDSRoutingTableNodeInfo DDSSharedObjectInterface::GetNodeInfo(DDSKey key)
{
  return m_CoordinatorState.GetNodeInfo(key);
}

void DDSSharedObjectCopyInterface::NotImplemented() const
{
  DDSLog::LogError("Calling shared object function from outside coordinator");
}

