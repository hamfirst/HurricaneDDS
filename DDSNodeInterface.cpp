
#include "DDSNodeInterface.h"
#include "DDSNodeState.h"
#include "DDSServerMessage.h"
#include "DDSEndpointFactoryBase.h"
#include "DDSRandom.h"

#include "DDSServerToServerMessages.refl.meta.h"

#include <StormRefl/StormReflJsonStd.h>

DDSNodeInterface::DDSNodeInterface(DDSNodeState & node_state, DDSDataObjectStoreBase * data_store, DDSKey key) :
  m_NodeState(node_state), m_DataStore(data_store), m_Key(key)
{

}

void DDSNodeInterface::FinalizeObjectLoad()
{
  m_DataStore->FinalizeObjectLoad(m_Key);
}

bool DDSNodeInterface::SendDataToLocalConnection(DDSConnectionId connection_id, const std::string & data)
{
  return m_NodeState.SendToLocalConnection(connection_id, data);
}

void DDSNodeInterface::DisconnectLocalConnection(DDSConnectionId connection_id)
{
  return m_NodeState.DisconnectLocalConnection(connection_id);
}

DDSKey DDSNodeInterface::GetLocalKey()
{
  return m_Key;
}

int DDSNodeInterface::GetObjectTypeId()
{
  return m_DataStore->GetDataClassNameHash();
}

int DDSNodeInterface::GetObjectType(uint32_t object_type_name_hash)
{
  return m_NodeState.GetTargetObjectIdForNameHash(object_type_name_hash);
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

void DDSNodeInterface::SendMessageToObjectWithResponderReturnArg(int target_object_type, DDSKey target_key, int target_method_id,
  int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && message, std::string && return_arg)
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

void DDSNodeInterface::SendResponderCall(const DDSResponderCallBase & call_data)
{
  m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ call_data.m_ObjectType, call_data.m_Key }, DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(call_data));
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

void DDSNodeInterface::QueryDatabaseInternal(const char * collection, std::string && query,
  int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg)
{
  DDSResponderCallData call_data;
  call_data.m_Key = responder_key;
  call_data.m_ObjectType = responder_object_type;
  call_data.m_MethodId = responder_method_id;
  call_data.m_ResponderArgs = return_arg;

  m_NodeState.QueryObjectData(collection, query.c_str(), std::move(call_data));
}

void DDSNodeInterface::UpdateDatabaseInternal(const char * collection, int data_object_type, std::string && data, DDSKey data_key,
  int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg)
{
  DDSResponderCallData call_data;
  call_data.m_Key = responder_key;
  call_data.m_ObjectType = responder_object_type;
  call_data.m_MethodId = responder_method_id;
  call_data.m_ResponderArgs = return_arg;

  m_NodeState.UpdateObjectData(data_object_type, data_key, collection, data.c_str(), &call_data);
}

void DDSNodeInterface::CreateTimerInternal(std::chrono::system_clock::duration duration, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg)
{
  DDSResponderCallData call_data;
  call_data.m_Key = key;
  call_data.m_ObjectType = data_object_type;
  call_data.m_MethodId = target_method_id;
  call_data.m_ResponderArgs = return_arg;

  m_NodeState.CreateTimer(duration, std::move(call_data));
}

void DDSNodeInterface::CreateHttpRequestInternal(const DDSHttpRequest & request, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg)
{
  DDSResponderCallData call_data;
  call_data.m_Key = key;
  call_data.m_ObjectType = data_object_type;
  call_data.m_MethodId = target_method_id;
  call_data.m_ResponderArgs = return_arg;

  m_NodeState.CreateHttpRequest(request, std::move(call_data));
}

DDSKey DDSNodeInterface::CreateSubscriptionInternal(int target_object_type, DDSKey target_key, const char * path, int return_object_type,
  DDSKey return_key, int return_method_id, bool delta_only, std::string && return_arg)
{
  DDSKey subscription_id = DDSGetRandomNumber64();

  DDSCreateSubscription sub_data;
  sub_data.m_DataPath = path;
  sub_data.m_Key = target_key;
  sub_data.m_ObjectType = target_object_type;
  sub_data.m_SubscriptionId = subscription_id;
  sub_data.m_ResponderObjectType = return_object_type;
  sub_data.m_ResponderKey = return_key;
  sub_data.m_ResponderMethodId = return_method_id;
  sub_data.m_ReturnArg = return_arg;
  sub_data.m_DeltaOnly = delta_only;

  DDSExportedRequestedSubscription req_sub;
  req_sub.m_ObjectType = target_object_type;
  req_sub.m_Key = target_key;
  req_sub.m_SubscriptionId = subscription_id;

  m_DataStore->AssignRequestedSubscription(return_key, req_sub);
  m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ target_object_type, target_key }, 
    DDSServerToServerMessageType::kCreateSubscription, StormReflEncodeJson(sub_data));

  return subscription_id;
}

DDSKey DDSNodeInterface::CreateDataSubscriptionInternal(int target_object_type, DDSKey target_key, const char * path, int return_object_type,
  DDSKey return_key, int return_method_id, bool delta_only, std::string && return_arg)
{
  DDSKey subscription_id = DDSGetRandomNumber64();

  DDSCreateDataSubscription sub_data;
  sub_data.m_DataPath = path;
  sub_data.m_Key = target_key;
  sub_data.m_ObjectType = target_object_type;
  sub_data.m_SubscriptionId = subscription_id;
  sub_data.m_ResponderObjectType = return_object_type;
  sub_data.m_ResponderKey = return_key;
  sub_data.m_ResponderMethodId = return_method_id;
  sub_data.m_ReturnArg = return_arg;
  sub_data.m_DeltaOnly = delta_only;

  DDSExportedRequestedSubscription req_sub;
  req_sub.m_ObjectType = target_object_type;
  req_sub.m_Key = target_key;
  req_sub.m_SubscriptionId = subscription_id;

  m_DataStore->AssignRequestedSubscription(return_key, req_sub);
  m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ target_object_type, target_key },
    DDSServerToServerMessageType::kCreateDataSubscription, StormReflEncodeJson(sub_data));

  return subscription_id;
}

DDSKey DDSNodeInterface::CreateExistSubscriptionInternal(int target_object_type, DDSKey target_key, int return_object_type,
  DDSKey return_key, int return_method_id, std::string && return_arg)
{
  DDSKey subscription_id = DDSGetRandomNumber64();

  DDSCreateExistSubscription sub_data;
  sub_data.m_Key = target_key;
  sub_data.m_ObjectType = target_object_type;
  sub_data.m_SubscriptionId = subscription_id;
  sub_data.m_ResponderObjectType = return_object_type;
  sub_data.m_ResponderKey = return_key;
  sub_data.m_ResponderMethodId = return_method_id;
  sub_data.m_ReturnArg = return_arg;

  DDSExportedRequestedSubscription req_sub;
  req_sub.m_ObjectType = target_object_type;
  req_sub.m_Key = target_key;
  req_sub.m_SubscriptionId = subscription_id;

  m_DataStore->AssignRequestedSubscription(return_key, req_sub);
  m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ target_object_type, target_key },
    DDSServerToServerMessageType::kCreateExistSubscription, StormReflEncodeJson(sub_data));

  return subscription_id;
}

DDSKey DDSNodeInterface::CreateDataExistSubscriptionInternal(int target_object_type, DDSKey target_key, int return_object_type,
  DDSKey return_key, int return_method_id, std::string && return_arg)
{
  DDSKey subscription_id = DDSGetRandomNumber64();

  DDSCreateDataExistSubscription sub_data;
  sub_data.m_Key = target_key;
  sub_data.m_ObjectType = target_object_type;
  sub_data.m_SubscriptionId = subscription_id;
  sub_data.m_ResponderObjectType = return_object_type;
  sub_data.m_ResponderKey = return_key;
  sub_data.m_ResponderMethodId = return_method_id;
  sub_data.m_ReturnArg = return_arg;

  DDSExportedRequestedSubscription req_sub;
  req_sub.m_ObjectType = target_object_type;
  req_sub.m_Key = target_key;
  req_sub.m_SubscriptionId = subscription_id;

  m_DataStore->AssignRequestedSubscription(return_key, req_sub);
  m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ target_object_type, target_key },
    DDSServerToServerMessageType::kCreateDataExistSubscription, StormReflEncodeJson(sub_data));

  return subscription_id;
}


void DDSNodeInterface::DestroySubscriptionInternal(int return_object_type, DDSKey return_key, DDSKey subscription_id)
{
  DDSDestroySubscription sub_data;
  sub_data.m_Key = return_key;
  sub_data.m_ObjectType = return_object_type;
  sub_data.m_SubscriptionId = subscription_id;

  m_DataStore->RemoveRequestedSubscription(return_key, subscription_id);
  m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ return_object_type, return_key },
    DDSServerToServerMessageType::kDestroySubscription, StormReflEncodeJson(sub_data));
}

DDSRoutingTableNodeInfo DDSNodeInterface::GetNodeInfo(DDSKey key)
{
  return m_NodeState.GetNodeInfo(key);
}
