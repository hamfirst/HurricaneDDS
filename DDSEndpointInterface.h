#pragma once

#include <tuple>
#include <string>
#include <chrono>

#include "DDSKey.h"
#include "DDSDeferredCallback.h"
#include "DDSResolverRequest.h"

#include <StormRefl\StormReflJsonStd.h>
#include <StormRefl\StormReflMetaCallJson.h>
#include <StormSockets\StormSocketConnectionId.h>

class DDSNodeState;
class DDSEndpointFactoryBase;

class DDSEndpointInterface
{
public:
  DDSEndpointInterface(DDSNodeState & node_state, DDSEndpointFactoryBase & endpoint_factory, StormSockets::StormSocketConnectionId connection_id);
  DDSEndpointInterface(const DDSEndpointInterface & rhs) = default;
  DDSEndpointInterface(DDSEndpointInterface && rhs) = default;

  template <typename TargetObject, typename ... Args, typename ... CallArgs>
  void Call(void (TargetObject::* target_func)(Args...), DDSKey key, CallArgs && ... args)
  {
    static_assert(std::is_convertible<std::tuple<CallArgs>, std::tuple<Args>>::value, "Invalid call args for function");

    int target_object_type = GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash());
    SendMessageToObject(target_object_type, key, StormReflGetMemberFunctionIndex(func), SerializeCallData(std::forward<CallArgs>(args)...));
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

  void CreateTimer(DDSDeferredCallback & callback , std::chrono::system_clock::duration duration, std::function<void()> && function);
  void CreateHttpRequest(DDSDeferredCallback & callback, const char * url, std::function<void(bool, const std::string &)> && function);
  void CreateResolverRequest(DDSDeferredCallback & callback, const char * hostname, std::function<void(const DDSResolverRequest &)> && function);

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
  void CreateHttpRequest(const char * url, DDSKey key, void (TargetObject::*return_func)(bool success, std::string data))
  {
    CreateHttpRequest(url, key, GetDataObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()),
      StormReflGetMemberFunctionIndex(return_func), std::string());
  }

  template <typename TargetObject, typename ReturnArg>
  void CreateHttpRequest(const char * url, DDSKey key, void (TargetObject::*return_func)(bool success, std::string data), ReturnArg && return_arg)
  {
    CreateHttpRequest(url, key, GetDataObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()),
      StormReflGetMemberFunctionIndex(return_func), StormReflEncodeJson(return_arg));
  }

  void SendData(std::string && data);

private:
  template <typename ... CallArgs>
  std::string SerializeCallData(CallArgs && ... args)
  {
    std::string call_data = '[';
    StormReflMetaHelpers::StormReflCallSerializeJsonParameterPack(sb, std::forward<ParamArgs>(args)...);
    call_data += ']';
    return call_data;
  }

  int GetObjectType(uint32_t object_type_name_hash);
  int GetDataObjectType(uint32_t object_type_name_hash);

  void SendMessageToObject(int target_object_type, DDSKey target_key, int target_method_id, std::string && message);
  bool CreateObject(int target_object_type, DDSKey & output_key);
  void DestroyObject(int target_object_type, DDSKey target_key);
  void CreateTimer(std::chrono::system_clock::duration duration, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg);
  void CreateHttpRequest(const char * url, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg);

private:
  DDSNodeState & m_NodeState;
  DDSEndpointFactoryBase & m_EndpointFactory;
  StormSockets::StormSocketConnectionId m_ConnectionId;
};

