
#include "DDSEndpointInterface.h"
#include "DDSEndpointFactoryBase.h"
#include "DDSNodeState.h"

#include "DDSServerToServerMessages.refl.meta.h"

DDSEndpointInterface::DDSEndpointInterface(DDSNodeState & node_state, DDSEndpointFactoryBase & endpoint_factory, StormSockets::StormSocketConnectionId connection_id) :
  m_NodeState(node_state), m_EndpointFactory(endpoint_factory), m_ConnectionId(connection_id)
{

}

void DDSEndpointInterface::CreateTimer(DDSDeferredCallback & callback, std::chrono::system_clock::duration duration, std::function<void()> && function)
{
  m_NodeState.CreateTimer(duration, callback, std::move(function));
}

void DDSEndpointInterface::CreateHttpRequest(DDSDeferredCallback & callback, const char * url, std::function<void(bool, const std::string &)> && function)
{
  m_NodeState.CreateHttpRequest(url, callback, std::move(function));
}

void DDSEndpointInterface::CreateResolverRequest(DDSDeferredCallback & callback, const char * hostname, std::function<void(const DDSResolverRequest &)> && function)
{
  m_NodeState.CreateResolverRequest(hostname, callback, std::move(function));
}

bool DDSEndpointInterface::SendData(const std::string & data)
{
  return m_EndpointFactory.SendData(m_ConnectionId, data);
}

int DDSEndpointInterface::GetObjectType(uint32_t object_type_name_hash)
{
  return m_NodeState.GetDataObjectTypeIdForNameHash(object_type_name_hash);
}

int DDSEndpointInterface::GetDataObjectType(uint32_t object_type_name_hash)
{
  return m_NodeState.GetDatabaseObjectTypeIdForNameHash(object_type_name_hash);
}

void * DDSEndpointInterface::GetLocalObject(int target_object_type, DDSKey target_key)
{
  auto & data_store = m_NodeState.GetDataObjectStore(target_object_type);
  auto data_val = data_store.GetDataObjectForKey(target_key);

  if (data_val == nullptr)
  {
    return nullptr;
  }

  data_store.BeginObjectModification(target_key);
  return data_val;
}

void DDSEndpointInterface::FinalizeLocalObject(int target_object_type, DDSKey target_key)
{
  auto & data_store = m_NodeState.GetDataObjectStore(target_object_type);
  data_store.EndObjectModification();
}

void DDSEndpointInterface::SendMessageToObject(int target_object_type, DDSKey target_key, int target_method_id, std::string && message)
{
  DDSTargetedMessage packet;
  packet.m_Key = target_key;
  packet.m_ObjectType = target_object_type;
  packet.m_MethodId = target_method_id;
  packet.m_MethodArgs = message;

  m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ target_object_type, target_key }, DDSServerToServerMessageType::kTargetedMessage, StormReflEncodeJson(packet));
}

bool DDSEndpointInterface::CreateObject(int target_object_type, DDSKey & output_key)
{
  return m_NodeState.CreateNewDataObject(target_object_type, output_key);
}

void DDSEndpointInterface::DestroyObject(int target_object_type, DDSKey target_key)
{
  m_NodeState.DestroyDataObject(target_object_type, target_key);
}

void DDSEndpointInterface::CreateTimer(std::chrono::system_clock::duration duration, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg)
{
  DDSResponderCallData call_data;
  call_data.m_Key = key;
  call_data.m_ObjectType = data_object_type;
  call_data.m_MethodId = target_method_id;
  call_data.m_ResponderArgs = return_arg;

  m_NodeState.CreateTimer(duration, std::move(call_data));
}

void DDSEndpointInterface::CreateHttpRequest(const char * url, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg)
{
  DDSResponderCallData call_data;
  call_data.m_Key = key;
  call_data.m_ObjectType = data_object_type;
  call_data.m_MethodId = target_method_id;
  call_data.m_ResponderArgs = return_arg;

  m_NodeState.CreateHttpRequest(url, std::move(call_data));
}

