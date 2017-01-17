#pragma once

#include "DDSKey.h"
#include "DDSResponder.h"
#include "DDSHttpRequest.h"
#include "DDSRoutingTable.h"

#include <string>
#include <cstdint>
#include <chrono>

#include <StormRefl/StormReflJsonStd.h>
#include <StormRefl/StormReflMetaCallJson.h>

struct DDSResponderCallBase;

template <typename DataType>
struct DDSCallTarget
{

};

template <typename DataType>
struct DDSSubscriptionTarget
{

};


template <typename ... CallArgs>
std::string DDSSerializeCallData(CallArgs && ... args)
{
  std::string call_data = "[";
  StormReflMetaHelpers::StormReflCallSerializeJsonParameterPack(call_data, std::forward<CallArgs>(args)...);
  call_data += ']';
  return call_data;
}

class DDSObjectInterface
{
public:
  virtual DDSKey GetLocalKey() = 0;
  virtual int GetObjectTypeId() const = 0;

  template <typename TargetObject, typename ... Args, typename ... CallArgs>
  void Call(void (TargetObject::* target_func)(Args...), DDSKey key, CallArgs && ... args)
  {
    static_assert(std::is_convertible<std::tuple<CallArgs...>, std::tuple<Args...>>::value, "Invalid call args for function");

    int target_object_type = GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash());
    SendMessageToObject(target_object_type, key, StormReflGetMemberFunctionIndex(target_func), DDSSerializeCallData(std::forward<CallArgs>(args)...));
  }

  template <typename TargetObject, typename ReturnObject, typename ... Args, typename ... CallArgs, typename ... ReturnArgs>
  void CallWithResponder(void (TargetObject::* target_func)(DDSResponder &, Args...), DDSKey key, void (ReturnObject::* return_func)(ReturnArgs...), ReturnObject * p_this, CallArgs && ... args)
  {
    static_assert(std::is_convertible<std::tuple<CallArgs...>, std::tuple<Args...>>::value, "Invalid call args for function");

    SendMessageToObjectWithResponderReturnArg(GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()), key, StormReflGetMemberFunctionIndex(target_func),
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()), GetLocalKey(), StormReflGetMemberFunctionIndex(return_func), -1,
      DDSSerializeCallData(std::forward<CallArgs>(args)...), std::string());
  }

  template <typename TargetObject, typename ReturnObject, typename ReturnArg, typename ... Args, typename ... CallArgs, typename ... ReturnArgs>
  void CallWithResponderReturnArg(void (TargetObject::* target_func)(DDSResponder &, Args...), DDSKey key,
    void (ReturnObject::* return_func)(ReturnArg, ReturnArgs...), ReturnObject * p_this, const ReturnArg & return_arg, CallArgs && ... args)
  {
    static_assert(std::is_convertible<std::tuple<CallArgs...>, std::tuple<Args...>>::value, "Invalid call args for function");

    SendMessageToObjectWithResponderReturnArg(GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()), key, StormReflGetMemberFunctionIndex(target_func),
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()), GetLocalKey(), StormReflGetMemberFunctionIndex(return_func), -1,
      DDSSerializeCallData(std::forward<CallArgs>(args)...), StormReflEncodeJson(return_arg));
  }

  template <typename TargetObject, typename ReturnObject, typename ReturnArg, typename ... Args, typename ... CallArgs, typename ... ReturnArgs>
  void CallWithResponderReturnArgErrorBack(void (TargetObject::* target_func)(DDSResponder &, Args...), DDSKey key,
    void (ReturnObject::* return_func)(ReturnArg, ReturnArgs...), void (ReturnObject::* error_func)(ReturnArg), 
    ReturnObject * p_this, const ReturnArg & return_arg, CallArgs && ... args)
  {
    static_assert(std::is_convertible<std::tuple<CallArgs...>, std::tuple<Args...>>::value, "Invalid call args for function");

    SendMessageToObjectWithResponderReturnArg(GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()), key, StormReflGetMemberFunctionIndex(target_func),
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()), GetLocalKey(), StormReflGetMemberFunctionIndex(return_func),
      StormReflGetMemberFunctionIndex(error_func), DDSSerializeCallData(std::forward<CallArgs>(args)...), StormReflEncodeJson(return_arg));
  }

  template <typename TargetObject, typename ... Args, typename ... CallArgs>
  void CallWithForwardedResponder(void (TargetObject::* target_func)(DDSResponder &, Args...), DDSKey key, DDSResponder & responder, CallArgs && ... args)
  {
    static_assert(std::is_convertible<std::tuple<CallArgs...>, std::tuple<Args...>>::value, "Invalid call args for function");

    SendMessageToObjectWithResponderReturnArg(GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()), key, StormReflGetMemberFunctionIndex(target_func),
      responder.m_Data.m_ObjectType, responder.m_Data.m_Key, responder.m_Data.m_ReturnMethodId, responder.m_Data.m_ErrorMethodId,
      DDSSerializeCallData(std::forward<CallArgs>(args)...), responder.m_Data.m_ReturnArg);
  }

  void CallWithForwardedResponderRaw(uint32_t type_name_hash, int method_id, DDSKey key, DDSResponderData & responder, std::string && call_args)
  {
    SendMessageToObjectWithResponderReturnArg(GetObjectType(type_name_hash), key, method_id,
      responder.m_ObjectType, responder.m_Key, responder.m_ReturnMethodId, responder.m_ErrorMethodId, std::move(call_args), std::string(responder.m_ReturnArg));
  }

  template <typename ReturnObject, typename ... ReturnArgs>
  DDSResponder CreateResponder(void (ReturnObject::* return_func)(ReturnArgs...), void (ReturnObject::* error_func)(), ReturnObject * p_this)
  {
    return DDSResponder{ *this, DDSResponderData{ GetLocalKey(), GetObjectTypeId(),
      StormReflGetMemberFunctionIndex(return_func), StormReflGetMemberFunctionIndex(error_func) } };
  }

  template <typename ReturnObject, typename ReturnArg, typename ... ReturnArgs>
  DDSResponder CreateResponder(void (ReturnObject::* return_func)(ReturnArg, ReturnArgs...), void (ReturnObject::* error_func)(ReturnArg),
    ReturnObject * p_this, const ReturnArg & return_arg)
  {
    return DDSResponder{ *this, DDSResponderData{ GetLocalKey(), GetObjectTypeId(), 
      StormReflGetMemberFunctionIndex(return_func), StormReflGetMemberFunctionIndex(error_func), StormReflEncodeJson(return_arg) } };
  }

  template <typename TargetObject, typename ... Args, typename ... CallArgs>
  void CallShared(void (TargetObject::* target_func)(Args...), CallArgs && ... args)
  {
    static_assert(std::is_convertible<std::tuple<CallArgs...>, std::tuple<Args...>>::value, "Invalid call args for function");

    int target_object_type = GetSharedObjectType(StormReflTypeInfo<TargetObject>::GetNameHash());
    SendMessageToSharedObject(target_object_type, StormReflGetMemberFunctionIndex(target_func), DDSSerializeCallData(std::forward<CallArgs>(args)...));
  }

  template <typename TargetObject, typename ReturnObject, typename ... Args, typename ... CallArgs, typename ... ReturnArgs>
  void CallSharedWithResponder(void (TargetObject::* target_func)(DDSResponder &, Args...), void (ReturnObject::* return_func)(ReturnArgs...), ReturnObject * p_this, CallArgs && ... args)
  {
    static_assert(std::is_convertible<std::tuple<CallArgs...>, std::tuple<Args...>>::value, "Invalid call args for function");

    SendMessageToSharedObjectWithResponderReturnArg(GetSharedObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()), StormReflGetMemberFunctionIndex(target_func),
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()), GetLocalKey(), StormReflGetMemberFunctionIndex(return_func),
      DDSSerializeCallData(std::forward<CallArgs>(args)...), std::string());
  }

  template <typename TargetObject, typename ReturnObject, typename ReturnArg, typename ... Args, typename ... CallArgs, typename ... ReturnArgs>
  void CallSharedWithResponderReturnArg(void (TargetObject::* target_func)(DDSResponder &, Args...),
    void (ReturnObject::* return_func)(ReturnArg, ReturnArgs...), ReturnObject * p_this, const ReturnArg & return_arg, CallArgs && ... args)
  {
    static_assert(std::is_convertible<std::tuple<CallArgs...>, std::tuple<Args...>>::value, "Invalid call args for function");

    SendMessageToSharedObjectWithResponderReturnArg(GetSharedObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()), StormReflGetMemberFunctionIndex(target_func),
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()), GetLocalKey(), StormReflGetMemberFunctionIndex(return_func),
      DDSSerializeCallData(std::forward<CallArgs>(args)...), StormReflEncodeJson(return_arg));
  }


  template <typename DatabaseType, typename ReturnObject>
  void InsertIntoDatabase(const DatabaseType & data, DDSKey key, void (ReturnObject::*return_func)(int ec), ReturnObject * p_this)
  {
    InsertIntoDatabaseWithResponderReturnArg(DatabaseType::Collection(), GetDataObjectType(StormReflTypeInfo<DatabaseType>::GetNameHash()),
      StormReflEncodeJson(data), key, GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()), GetLocalKey(),
      StormReflGetMemberFunctionIndex(return_func), std::string());
  }

  template <typename DatabaseType, typename ReturnObject, typename ReturnArg>
  void InsertIntoDatabase(const DatabaseType & data, DDSKey key, void (ReturnObject::*return_func)(ReturnArg return_arg, int ec), ReturnObject * p_this, ReturnArg && return_arg)
  {
    InsertIntoDatabaseWithResponderReturnArg(DatabaseType::Collection(), GetDataObjectType(StormReflTypeInfo<DatabaseType>::GetNameHash()),
      StormReflEncodeJson(data), key, GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()), GetLocalKey(),
      StormReflGetMemberFunctionIndex(return_func), StormReflEncodeJson(return_arg));
  }

  template <typename QueryObject, typename ReturnObject>
  void QueryDatabase(const QueryObject & query, void (ReturnObject::*return_func)(int ec, std::string data), ReturnObject * p_this)
  {
    using DatabaseObject = typename QueryObject::DatabaseType;
    QueryDatabaseInternal(DatabaseObject::Collection(), StormReflEncodeJson(query), GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()), GetLocalKey(),
      StormReflGetMemberFunctionIndex(return_func), std::string());
  }

  template <typename QueryObject, typename ReturnObject, typename ReturnArg>
  void QueryDatabase(const QueryObject & query, void (ReturnObject::*return_func)(ReturnArg return_arg, int ec, std::string data), ReturnObject * p_this, ReturnArg && return_arg)
  {
    using DatabaseObject = typename QueryObject::DatabaseType;
    QueryDatabaseInternal(DatabaseObject::Collection(), StormReflEncodeJson(query), GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()), GetLocalKey(),
      StormReflGetMemberFunctionIndex(return_func), StormReflEncodeJson(return_arg));
  }

  template <typename TargetObject>
  void CreateTimer(std::chrono::system_clock::duration duration, DDSKey key, void (TargetObject::*return_func)())
  {
    CreateTimerInternal(duration, key, GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()),
      StormReflGetMemberFunctionIndex(return_func), std::string());
  }

  template <typename TargetObject, typename ParamArg, typename ReturnArg>
  void CreateTimer(std::chrono::system_clock::duration duration, DDSKey key, void (TargetObject::*return_func)(ParamArg return_arg), ReturnArg && return_arg)
  {
    CreateTimerInternal(duration, key, GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()),
      StormReflGetMemberFunctionIndex(return_func), StormReflEncodeJson(return_arg));
  }

  template <typename TargetObject>
  void CreateHttpRequest(const DDSHttpRequest & request, DDSKey key, void (TargetObject::*return_func)(bool success, std::string data, std::string headers))
  {
    CreateHttpRequestInternal(request, key, GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()),
      StormReflGetMemberFunctionIndex(return_func), std::string());
  }

  template <typename TargetObject, typename ReturnArg>
  void CreateHttpRequest(const DDSHttpRequest & request, DDSKey key, 
    void (TargetObject::*return_func)(ReturnArg return_arg, bool success, std::string data, std::string headers), ReturnArg && return_arg)
  {
    CreateHttpRequestInternal(request, key, GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()),
      StormReflGetMemberFunctionIndex(return_func), StormReflEncodeJson(return_arg));
  }

  template <typename TargetObject, typename ReturnObject>
  DDSKey CreateSubscription(const DDSSubscriptionTarget<TargetObject> & sub, DDSKey target_key, const char * path,
    void (ReturnObject::*return_func)(std::string data), bool delta_only, 
    void (ReturnObject::*err_func)() = nullptr, bool force_load = true)
  {
    return CreateSubscriptionInternal(GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()), target_key, path,
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()),
      GetLocalKey(), StormReflGetMemberFunctionIndex(return_func), delta_only, 
      std::string(), StormReflGetMemberFunctionIndex(err_func), force_load, false);
  }

  template <typename TargetObject, typename ReturnObject, typename ReturnArg>
  DDSKey CreateSubscription(const DDSSubscriptionTarget<TargetObject> & sub, DDSKey target_key, const char * path,
    void (ReturnObject::*return_func)(ReturnArg return_arg, std::string data), bool delta_only, const ReturnArg & return_arg, 
    void (ReturnObject::*err_func)(ReturnArg return_arg) = nullptr, bool force_load = true)
  {
    return CreateSubscriptionInternal(GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()), target_key, path,
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()),
      GetLocalKey(), StormReflGetMemberFunctionIndex(return_func), delta_only, 
      StormReflEncodeJson(return_arg), StormReflGetMemberFunctionIndex(err_func), force_load, false);
  }

  template <typename TargetDataObject, typename ReturnObject>
  DDSKey CreateDataSubscription(const DDSSubscriptionTarget<TargetDataObject> & sub, DDSKey target_key, const char * path,
    void (ReturnObject::*return_func)(std::string data), bool delta_only,
    void (ReturnObject::*err_func)() = nullptr, bool force_load = true)
  {
    return CreateSubscriptionInternal(GetDataObjectType(StormReflTypeInfo<TargetDataObject>::GetNameHash()), target_key, path,
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()),
      GetLocalKey(), StormReflGetMemberFunctionIndex(return_func), delta_only, 
      std::string(), StormReflGetMemberFunctionIndex(err_func), force_load, true);
  }

  template <typename TargetDataObject, typename ReturnObject, typename ReturnArg>
  DDSKey CreateDataSubscription(const DDSSubscriptionTarget<TargetDataObject> & sub, DDSKey target_key, const char * path,
    void (ReturnObject::*return_func)(ReturnArg return_arg, std::string data), bool delta_only, const ReturnArg & return_arg,
    void (ReturnObject::*err_func)(ReturnArg return_arg) = nullptr, bool force_load = true)
  {
    return CreateSubscriptionInternal(GetObjectType(StormReflTypeInfo<TargetDataObject>::GetNameHash()), target_key, path,
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()),
      GetLocalKey(), StormReflGetMemberFunctionIndex(return_func), delta_only, 
      StormReflEncodeJson(return_arg), StormReflGetMemberFunctionIndex(err_func), force_load, true);
  }

  template <typename TargetDataObject>
  void DestroySubscription(DDSKey target_key, DDSKey subscription_id)
  {
    DestroySubscriptionInternal(GetObjectType(StormReflTypeInfo<TargetDataObject>::GetNameHash()), target_key, subscription_id);
  }

  template <typename TargetDatabaseObject>
  void DestroyDatabaseSubscription(DDSKey target_key, DDSKey subscription_id)
  {
    DestroySubscriptionInternal(GetDataObjectType(StormReflTypeInfo<TargetDatabaseObject>::GetNameHash()), target_key, subscription_id);
  }

  template <typename SharedObjectType>
  const SharedObjectType * GetSharedObject()
  {
    return (SharedObjectType *)GetSharedObjectPointer(StormReflTypeInfo<SharedObjectType>::GetNameHash());
  }

  virtual void DestroySelf() = 0;

  virtual DDSRoutingTableNodeInfo GetNodeInfo(DDSKey key) = 0;

  virtual time_t GetNetworkTime() = 0;

private:

  friend void DDSResponderCallFinalize(const DDSResponder & responder, const DDSResponderCallBase & call_data);

  virtual int GetObjectType(uint32_t object_type_name_hash) = 0;
  virtual int GetDataObjectType(uint32_t object_type_name_hash) = 0;
  virtual int GetSharedObjectType(uint32_t object_type_name_hash) = 0;

  virtual const void * GetSharedObjectPointer(uint32_t object_type_name_hash) = 0;

  virtual void SendMessageToObject(int target_object_type, DDSKey target_key, int target_method_id, std::string && message) = 0;
  virtual void SendMessageToObjectWithResponderReturnArg(int target_object_type, DDSKey target_key, int target_method_id,
    int responder_object_type, DDSKey responder_key, int responder_method_id, int error_method_id, std::string && message, std::string && return_arg) = 0;
  virtual void SendMessageToSharedObject(int target_object_type, int target_method_id, std::string && message) = 0;
  virtual void SendMessageToSharedObjectWithResponderReturnArg(int target_object_type, int target_method_id,
    int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && message, std::string && return_arg) = 0;

  virtual void SendResponderCall(const DDSResponderCallBase & call_data) = 0;

  virtual void InsertIntoDatabaseWithResponderReturnArg(const char * collection, int data_object_type, std::string && data, DDSKey data_key,
    int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg) = 0;

  virtual void QueryDatabaseInternal(const char * collection, std::string && query,
    int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg) = 0;

  virtual void CreateTimerInternal(std::chrono::system_clock::duration duration, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg) = 0;
  virtual void CreateHttpRequestInternal(const DDSHttpRequest & request, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg) = 0;

  virtual DDSKey CreateSubscriptionInternal(int target_object_type, DDSKey target_key, const char * path, int return_object_type,
    DDSKey return_key, int return_method_id, bool delta_only, std::string && return_arg, int err_method_id, bool force_load, bool data_sub) = 0;

  virtual void DestroySubscriptionInternal(int return_object_type, DDSKey return_key, DDSKey subscription_id) = 0;
};
