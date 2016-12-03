#pragma once

#include <tuple>
#include <string>
#include <chrono>

#include "DDSKey.h"
#include "DDSRoutingTable.h"
#include "DDSConnectionId.h"
#include "DDSConnectionFactoryBase.h"
#include "DDSDeferredCallback.h"
#include "DDSResolverRequest.h"
#include "DDSHttpRequest.h"

#include <StormRefl/StormReflJsonStd.h>
#include <StormRefl/StormReflMetaCallJson.h>
#include <StormSockets/StormSocketConnectionId.h>

class DDSNodeState;


class DDSConnectionInterface
{
public:
  DDSConnectionInterface(DDSNodeState & node_state, DDSConnectionFactoryBase & connection_factory,
    StormSockets::StormSocketConnectionId connection_id, uint32_t remote_ip, uint16_t remote_port);

  DDSConnectionInterface(const DDSConnectionInterface & rhs) = default;
  DDSConnectionInterface(DDSConnectionInterface && rhs) = default;

  uint32_t GetRemoteIp() const;
  uint16_t GetRemotePort() const;

  void GetRemoteIp(char * buffer, int buffer_len) const;
  std::string GetRemoteIpAsString() const;

  template <typename TargetObject, typename ... Args, typename ... CallArgs>
  void Call(void (TargetObject::* target_func)(Args...), DDSKey key, CallArgs && ... args)
  {
    static_assert(std::is_convertible<std::tuple<CallArgs...>, std::tuple<Args...>>::value, "Invalid call args for function");

    int target_object_type = GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash());
    SendMessageToObject(target_object_type, key, StormReflGetMemberFunctionIndex(target_func), SerializeCallData(std::forward<CallArgs>(args)...));
  }

  template <typename TargetObject>
  bool CreateObject(DDSKey & output_key)
  {
    int target_object_type = GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash());
    return CreateObject(target_object_type, output_key);
  }

  template <typename TargetObject>
  void DestroyObject(DDSKey key)
  {
    int target_object_type = GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash());
    DestroyObject(target_object_type, key);
  }

  void CreateTimer(DDSDeferredCallback & callback, std::chrono::system_clock::duration duration, std::function<void()> && function);
  void CreateHttpRequest(DDSDeferredCallback & callback, const DDSHttpRequest & request, std::function<void(bool, const std::string &, const std::string &)> && function);
  void CreateResolverRequest(DDSDeferredCallback & callback, const char * hostname, bool reverse_lookup, std::function<void(const DDSResolverRequest &)> && function);

  template <typename TargetObject>
  void CreateTimer(std::chrono::system_clock::duration duration, DDSKey key, void (TargetObject::*return_func)())
  {
    CreateTimer(duration, key, GetDataObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()),
      StormReflGetMemberFunctionIndex(return_func), std::string());
  }

  template <typename TargetObject, typename ReturnArg>
  void CreateTimer(std::chrono::system_clock::duration duration, DDSKey key, void (TargetObject::*return_func)(), ReturnArg && return_arg)
  {
    CreateTimer(duration, key, GetDataObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()),
      StormReflGetMemberFunctionIndex(return_func), StormReflEncodeJson(return_arg));
  }

  template <typename TargetObject>
  void CreateHttpRequest(const DDSHttpRequest & request, DDSKey key, void (TargetObject::*return_func)(bool success, std::string data, std::string headers))
  {
    CreateHttpRequest(request, key, GetDataObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()),
      StormReflGetMemberFunctionIndex(return_func), std::string());
  }

  template <typename TargetObject, typename ReturnArg>
  void CreateHttpRequest(const DDSHttpRequest & request, DDSKey key, void (TargetObject::*return_func)(bool success, std::string data, std::string headers), ReturnArg && return_arg)
  {
    CreateHttpRequest(request, key, GetDataObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()),
      StormReflGetMemberFunctionIndex(return_func), StormReflEncodeJson(return_arg));
  }

  bool IsLocalKey(DDSKey key);
  DDSRoutingTableNodeInfo GetNodeInfo(DDSKey key);

  void ForceDisconnect();

protected:
  template <typename ... CallArgs>
  std::string SerializeCallData(CallArgs && ... args)
  {
    std::string call_data = "[";
    StormReflMetaHelpers::StormReflCallSerializeJsonParameterPack(call_data, std::forward<CallArgs>(args)...);
    call_data += ']';
    return call_data;
  }

  int GetObjectType(uint32_t object_type_name_hash);
  int GetDataObjectType(uint32_t object_type_name_hash);

  void * GetLocalObject(int target_object_type, DDSKey target_key);
  void FinalizeLocalObject(int target_object_type, DDSKey target_key);

  void SendMessageToObject(int target_object_type, DDSKey target_key, int target_method_id, std::string && message);
  bool CreateObject(int target_object_type, DDSKey & output_key);
  void DestroyObject(int target_object_type, DDSKey target_key);
  void CreateTimer(std::chrono::system_clock::duration duration, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg);
  void CreateHttpRequest(const DDSHttpRequest & request, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg);

protected:
  DDSNodeState & m_NodeState;
  DDSConnectionFactoryBase & m_ConnectionFactory;
  StormSockets::StormSocketConnectionId m_ConnectionId;
  uint32_t m_RemoteIp;
  uint16_t m_RemotePort;
};

