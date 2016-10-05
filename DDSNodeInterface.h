#pragma once

#include <string>
#include <cstdint>

#include "DDSKey.h"
#include "DDSResponder.h"

#include <StormRefl\StormReflJsonStd.h>
#include <StormRefl\StormReflMetaCallJson.h>

class DDSNodeState;
class DDSDataObjectStoreBase;

class DDSNodeInterface
{
public:
  DDSNodeInterface(DDSNodeState & node_state, DDSDataObjectStoreBase * data_store, DDSKey key);
  DDSNodeInterface(const DDSNodeInterface & rhs) = default;
  DDSNodeInterface(DDSNodeInterface && rhs) = default;

  template <typename TargetObject, typename ... Args, typename ... CallArgs>
  void Call(void (TargetObject::* target_func)(Args...), DDSKey key, CallArgs && ... args)
  {
    static_assert(std::is_convertible<std::tuple<CallArgs>, std::tuple<Args>>::value, "Invalid call args for function");

    int target_object_type = GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash());
    SendMessageToObject(target_object_type, key, StormReflGetMemberFunctionIndex(func), SerializeCallData(std::forward<CallArgs>(args)...));
  }

  template <typename TargetObject, typename ... Args, typename ... CallArgs>
  void CallWithResponder(void (TargetObject::* target_func)(DDSResponder &, Args...), DDSKey key, DDSResponder & responder, CallArgs && ... args)
  {
    static_assert(std::is_convertible<std::tuple<CallArgs>, std::tuple<Args>>::value, "Invalid call args for function");

    SendMessageToObjectWithResponder(GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()), key, StormReflGetMemberFunctionIndex(func),
      responder.m_Data.m_ObjectType, responder.m_Data.m_Key, responder.m_Data.m_ReturnMethodId, SerializeCallData(std::forward<CallArgs>(args)...));
  }

  template <typename TargetObject, typename ReturnObject, typename ... Args, typename ... CallArgs, typename ... ReturnArgs>
  void CallWithResponder(void (TargetObject::* target_func)(DDSResponder &, Args...), DDSKey key, void (ReturnObject::* return_func)(ReturnArgs...), DDSKey return_key, CallArgs && ... args)
  {
    static_assert(std::is_convertible<std::tuple<CallArgs>, std::tuple<Args>>::value, "Invalid call args for function");

    SendMessageToObjectWithResponder(GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()), key, StormReflGetMemberFunctionIndex(func),
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()), return_key, StormReflGetMemberFunctionIndex(return_func), SerializeCallData(std::forward<CallArgs>(args)...));
  }

  template <typename TargetObject, typename ReturnObject, typename ... Args, typename ... CallArgs, typename ... ReturnArgs>
  void CallWithResponder(void (TargetObject::* target_func)(DDSResponder &, Args...), DDSKey key, void (ReturnObject::* return_func)(ReturnArgs...), ReturnObject * p_this, CallArgs && ... args)
  {
    static_assert(std::is_convertible<std::tuple<CallArgs>, std::tuple<Args>>::value, "Invalid call args for function");

    SendMessageToObjectWithResponder(GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()), key, StormReflGetMemberFunctionIndex(func),
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()), m_Key, StormReflGetMemberFunctionIndex(return_func), SerializeCallData(std::forward<CallArgs>(args)...));
  }

  template <typename TargetObject, typename ReturnObject, typename ReturnArg, typename ... Args, typename ... CallArgs, typename ... ReturnArgs>
  void CallWithResponderReturnArg(void (TargetObject::* target_func)(DDSResponder &, Args...), DDSKey key, 
    void (ReturnObject::* return_func)(ReturnArg, ReturnArgs...), DDSKey return_key, ReturnArg && return_arg, CallArgs && ... args)
  {
    static_assert(std::is_convertible<std::tuple<CallArgs>, std::tuple<Args>>::value, "Invalid call args for function");

    SendMessageToObjectWithResponder(GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()), key, StormReflGetMemberFunctionIndex(func),
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()), return_key, StormReflGetMemberFunctionIndex(return_func), 
      StormReflEncodeJson(return_arg), SerializeCallData(std::forward<CallArgs>(args)...));
  }

  template <typename TargetObject, typename ReturnObject, typename ReturnArg, typename ... Args, typename ... CallArgs, typename ... ReturnArgs>
  void CallWithResponderReturnArg(void (TargetObject::* target_func)(DDSResponder &, Args...), DDSKey key,
    void (ReturnObject::* return_func)(ReturnArg, ReturnArgs...), ReturnObject * p_this, ReturnArg && return_arg, CallArgs && ... args)
  {
    static_assert(std::is_convertible<std::tuple<CallArgs>, std::tuple<Args>>::value, "Invalid call args for function");

    SendMessageToObjectWithResponder(GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()), key, StormReflGetMemberFunctionIndex(func),
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()), m_Key, StormReflGetMemberFunctionIndex(return_func),
      StormReflEncodeJson(return_arg), SerializeCallData(std::forward<CallArgs>(args)...));
  }

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
  
  void SendMessageToObject(int target_object_type, DDSKey target_key, int target_method_id, std::string && message);
  void SendMessageToObjectWithResponder(int target_object_type, DDSKey target_key, int target_method_id,
    int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && message);
  void SendMessageToObjectWithResponderReturnArg(int target_object_type, DDSKey target_key, int target_method_id,
    int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg, std::string && message);

  DDSNodeState & m_NodeState;
  DDSDataObjectStoreBase * m_DataStore;
  DDSKey m_Key;
};
