
#include "DDSConnectionInterface.h"
#include "DDSEndpointFactoryBase.h"
#include "DDSNodeState.h"

#include "DDSServerToServerMessages.refl.meta.h"

DDSConnectionInterface::DDSConnectionInterface(DDSNodeState & node_state, DDSConnectionFactoryBase & connection_factory,
  StormSockets::StormSocketConnectionId connection_id, uint32_t remote_ip, uint16_t remote_port) :
  m_NodeState(node_state),
  m_ConnectionFactory(connection_factory),
  m_ConnectionId(connection_id),
  m_RemoteIp(remote_ip),
  m_RemotePort(remote_port)
{

}

uint32_t DDSConnectionInterface::GetRemoteIp() const
{
  return m_RemoteIp;
}

uint16_t DDSConnectionInterface::GetRemotePort() const
{
  return m_RemotePort;
}

void DDSConnectionInterface::GetRemoteIp(char * buffer, int buffer_len) const
{
  uint8_t * ip_addr = (uint8_t *)&m_RemoteIp;
  snprintf(buffer, buffer_len, "%d.%d.%d.%d", ip_addr[3], ip_addr[2], ip_addr[1], ip_addr[0]);
}

std::string DDSConnectionInterface::GetRemoteIpAsString() const
{
  char ip_text[20];
  GetRemoteIp(ip_text, sizeof(ip_text));
  return ip_text;
}

void DDSConnectionInterface::CreateTimer(DDSDeferredCallback & callback, std::chrono::system_clock::duration duration, std::function<void()> && function)
{
  m_NodeState.CreateTimer(duration, callback, std::move(function));
}

void DDSConnectionInterface::CreateHttpRequest(DDSDeferredCallback & callback, const DDSHttpRequest & request, std::function<void(bool, const std::string &, const std::string &)> && function)
{
  m_NodeState.CreateHttpRequest(request, callback, std::move(function));
}

void DDSConnectionInterface::CreateResolverRequest(DDSDeferredCallback & callback, const char * hostname, bool reverse_lookup, std::function<void(const DDSResolverRequest &)> && function)
{
  m_NodeState.CreateResolverRequest(hostname, reverse_lookup, callback, std::move(function));
}

bool DDSConnectionInterface::IsLocalKey(DDSKey key)
{
  return KeyInKeyRange(key, m_NodeState.GetLocalKeyRange());
}

DDSRoutingTableNodeInfo DDSConnectionInterface::GetNodeInfo(DDSKey key)
{
  return m_NodeState.GetNodeInfo(key);
}

void DDSConnectionInterface::ForceDisconnect()
{
  m_ConnectionFactory.ForceDisconnect(m_ConnectionId);
}

int DDSConnectionInterface::GetObjectType(uint32_t object_type_name_hash)
{
  return m_NodeState.GetDataObjectTypeIdForNameHash(object_type_name_hash);
}

int DDSConnectionInterface::GetDataObjectType(uint32_t object_type_name_hash)
{
  return m_NodeState.GetDatabaseObjectTypeIdForNameHash(object_type_name_hash);
}

void * DDSConnectionInterface::GetLocalObject(int target_object_type, DDSKey target_key)
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

void DDSConnectionInterface::FinalizeLocalObject(int target_object_type, DDSKey target_key)
{
  auto & data_store = m_NodeState.GetDataObjectStore(target_object_type);
  data_store.EndObjectModification();
}

void DDSConnectionInterface::SendMessageToObject(int target_object_type, DDSKey target_key, int target_method_id, std::string && message)
{
  DDSTargetedMessage packet;
  packet.m_Key = target_key;
  packet.m_ObjectType = target_object_type;
  packet.m_MethodId = target_method_id;
  packet.m_MethodArgs = message;

  m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ target_object_type, target_key }, DDSServerToServerMessageType::kTargetedMessage, StormReflEncodeJson(packet));
}

bool DDSConnectionInterface::CreateObject(int target_object_type, DDSKey & output_key)
{
  return m_NodeState.CreateNewDataObject(target_object_type, output_key);
}

void DDSConnectionInterface::DestroyObject(int target_object_type, DDSKey target_key)
{
  m_NodeState.DestroyDataObject(target_object_type, target_key);
}

void DDSConnectionInterface::CreateTimer(std::chrono::system_clock::duration duration, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg)
{
  DDSResponderCallData call_data;
  call_data.m_Key = key;
  call_data.m_ObjectType = data_object_type;
  call_data.m_MethodId = target_method_id;
  call_data.m_ResponderArgs = return_arg;

  m_NodeState.CreateTimer(duration, std::move(call_data));
}

void DDSConnectionInterface::CreateHttpRequest(const DDSHttpRequest & request, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg)
{
  DDSResponderCallData call_data;
  call_data.m_Key = key;
  call_data.m_ObjectType = data_object_type;
  call_data.m_MethodId = target_method_id;
  call_data.m_ResponderArgs = return_arg;

  m_NodeState.CreateHttpRequest(request, std::move(call_data));
}

