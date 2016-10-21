#pragma once

#include "DDSKey.h"
#include "DDSResponder.h"

#include <string>
#include <cstdint>
#include <chrono>

#include <StormRefl\StormReflJsonStd.h>
#include <StormRefl\StormReflMetaCallJson.h>

struct DDSResponderCallBase;

template <typename DataType>
struct DDSSubscriptionTarget
{

};

class DDSInterface
{
public:

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

    SendMessageToObjectWithResponderReturnArg(GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()), key, StormReflGetMemberFunctionIndex(func),
      responder.m_Data.m_ObjectType, responder.m_Data.m_Key, responder.m_Data.m_ReturnMethodId, SerializeCallData(std::forward<CallArgs>(args)...), std::string());
  }

  template <typename TargetObject, typename ReturnObject, typename ... Args, typename ... CallArgs, typename ... ReturnArgs>
  void CallWithResponder(void (TargetObject::* target_func)(DDSResponder &, Args...), DDSKey key, void (ReturnObject::* return_func)(ReturnArgs...), DDSKey return_key, CallArgs && ... args)
  {
    static_assert(std::is_convertible<std::tuple<CallArgs>, std::tuple<Args>>::value, "Invalid call args for function");

    SendMessageToObjectWithResponderReturnArg(GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()), key, StormReflGetMemberFunctionIndex(func),
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()), return_key, StormReflGetMemberFunctionIndex(return_func),
      SerializeCallData(std::forward<CallArgs>(args)...), std::string());
  }

  template <typename TargetObject, typename ReturnObject, typename ... Args, typename ... CallArgs, typename ... ReturnArgs>
  void CallWithResponder(void (TargetObject::* target_func)(DDSResponder &, Args...), DDSKey key, void (ReturnObject::* return_func)(ReturnArgs...), ReturnObject * p_this, CallArgs && ... args)
  {
    static_assert(std::is_convertible<std::tuple<CallArgs>, std::tuple<Args>>::value, "Invalid call args for function");

    SendMessageToObjectWithResponderReturnArg(GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()), key, StormReflGetMemberFunctionIndex(func),
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()), GetLocalKey(), StormReflGetMemberFunctionIndex(return_func),
      SerializeCallData(std::forward<CallArgs>(args)...), std::string());
  }

  template <typename TargetObject, typename ReturnObject, typename ReturnArg, typename ... Args, typename ... CallArgs, typename ... ReturnArgs>
  void CallWithResponderReturnArg(void (TargetObject::* target_func)(DDSResponder &, Args...), DDSKey key,
    void (ReturnObject::* return_func)(ReturnArg, ReturnArgs...), DDSKey return_key, ReturnArg && return_arg, CallArgs && ... args)
  {
    static_assert(std::is_convertible<std::tuple<CallArgs>, std::tuple<Args>>::value, "Invalid call args for function");

    SendMessageToObjectWithResponderReturnArg(GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()), key, StormReflGetMemberFunctionIndex(func),
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()), return_key, StormReflGetMemberFunctionIndex(return_func),
      StormReflEncodeJson(return_arg), SerializeCallData(std::forward<CallArgs>(args)...), StormReflEncodeJson(return_arg));
  }

  template <typename TargetObject, typename ReturnObject, typename ReturnArg, typename ... Args, typename ... CallArgs, typename ... ReturnArgs>
  void CallWithResponderReturnArg(void (TargetObject::* target_func)(DDSResponder &, Args...), DDSKey key,
    void (ReturnObject::* return_func)(ReturnArg, ReturnArgs...), ReturnObject * p_this, ReturnArg && return_arg, CallArgs && ... args)
  {
    static_assert(std::is_convertible<std::tuple<CallArgs>, std::tuple<Args>>::value, "Invalid call args for function");

    SendMessageToObjectWithResponderReturnArg(GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()), key, StormReflGetMemberFunctionIndex(func),
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()), GetLocalKey(), StormReflGetMemberFunctionIndex(return_func),
      StormReflEncodeJson(return_arg), SerializeCallData(std::forward<CallArgs>(args)...), StormReflEncodeJson(return_arg));
  }

  template <typename DatabaseType, typename ReturnObject>
  void InsertIntoDatabase(const DatabaseType & data, DDSKey key, void (ReturnObject::*return_func)(int ec), ReturnObject * p_this)
  {
    InsertIntoDatabaseWithResponder(DatabaseType::Collection(), GetDataObjectType(StormReflTypeInfo<DatabaseType>::GetNameHash()),
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
    using DatabaseObject = QueryObject::DatabaseType;
    QueryDatabase(DatabaseObject::Collection(), StormReflEncodeJson(query), GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()), GetLocalKey(),
      StormReflGetMemberFunctionIndex(return_func), std::string());
  }

  template <typename QueryObject, typename ReturnObject, typename ReturnArg>
  void QueryDatabase(const QueryObject & query, void (ReturnObject::*return_func)(ReturnArg return_arg, int ec, std::string data), ReturnObject * p_this, ReturnArg && return_arg)
  {
    using DatabaseObject = QueryObject::DatabaseType;
    QueryDatabase(DatabaseObject::Collection(), StormReflEncodeJson(query), GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()), GetLocalKey(),
      StormReflGetMemberFunctionIndex(return_func), StormReflEncodeJson(return_arg));
  }

  template <typename TargetObject>
  void CreateTimer(std::chrono::system_clock::duration duration, DDSKey key, void (TargetObject::*return_func)())
  {
    CreateTimer(duration, key, GetDataObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()),
      StormReflGetMemberFunctionIndex(return_func), std::string());
  }

  template <typename TargetObject, typename ReturnArg>
  void CreateTimer(std::chrono::system_clock::duration duration, DDSKey key, void (TargetObject::*return_func)(ReturnArg return_arg), ReturnArg && return_arg)
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
  void CreateHttpRequest(const char * url, DDSKey key, void (TargetObject::*return_func)(ReturnArg return_arg, bool success, std::string data), ReturnArg && return_arg)
  {
    CreateHttpRequest(url, key, GetDataObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()),
      StormReflGetMemberFunctionIndex(return_func), StormReflEncodeJson(return_arg));
  }

  template <typename TargetObject, typename ReturnObject>
  void CreateSubscription(const DDSSubscriptionTarget<TargetObject> & sub, DDSKey target_key, const char * path, 
    void (ReturnObject::* return_func)(std::string data))
  {
    CreateSubscription(GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()), target_key, path, 
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()),
      GetLocalKey(), StormReflGetMemberFunctionIndex(return_func), std::string());
  }

  template <typename TargetObject, typename ReturnObject, typename ReturnArg>
  void CreateSubscription(const DDSSubscriptionTarget<TargetObject> & sub, DDSKey target_key, const char * path, 
    void (ReturnObject::* return_func)(ReturnArg return_arg, std::string data), ReturnArg && return_arg)
  {
    CreateSubscription(GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash()), target_key, path, 
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()),
      GetLocalKey(), StormReflGetMemberFunctionIndex(return_func), StormReflEncodeJson(return_arg));
  }

  template <typename TargetDataObject, typename ReturnObject>
  DDSKey CreateDataSubscription(const DDSSubscriptionTarget<TargetDataObject> & sub, DDSKey target_key, const char * path,
    void (ReturnObject::* return_func)(std::string data), bool delta_only)
  {
    return CreateSubscription(GetDataObjectType(StormReflTypeInfo<TargetDataObject>::GetNameHash()), target_key, path, 
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()),
      GetLocalKey(), StormReflGetMemberFunctionIndex(return_func), delta_only, std::string());
  }

  template <typename TargetDataObject, typename ReturnObject, typename ReturnArg>
  DDSKey CreateDataSubscription(const DDSSubscriptionTarget<TargetDataObject> & sub, DDSKey target_key, const char * path,
    void (ReturnObject::* return_func)(ReturnArg return_arg, std::string data), bool delta_only, ReturnArg && return_arg)
  {
    return CreateSubscription(GetObjectType(StormReflTypeInfo<TargetDataObject>::GetNameHash()), target_key, path,
      GetObjectType(StormReflTypeInfo<ReturnObject>::GetNameHash()),
      GetLocalKey(), StormReflGetMemberFunctionIndex(return_func), delta_only, StormReflEncodeJson(return_arg));
  }

  template <typename TargetDataObject>
  void DestroySubscription(DDSKey target_key, DDSKey subscription_id)
  {
    DestroySubscription(GetObjectType(StormReflTypeInfo<TargetDataObject>::GetNameHash()), subscription_id);
  }

  template <typename TargetDatabaseObject>
  void DestroyDatabaseSubscription(DDSKey target_key, DDSKey subscription_id)
  {
    DestroySubscription(GetDataObjectType(StormReflTypeInfo<TargetDatabaseObject>::GetNameHash()), subscription_id);
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

  friend void DDSResponderCallFinalize(const DDSResponder & responder, const DDSResponderCallBase & call_data);

  virtual DDSKey GetLocalKey() = 0;
  virtual int GetObjectTypeId() = 0;

  virtual int GetObjectType(uint32_t object_type_name_hash) = 0;
  virtual int GetDataObjectType(uint32_t object_type_name_hash) = 0;

  virtual void SendMessageToObject(int target_object_type, DDSKey target_key, int target_method_id, std::string && message) = 0;
  virtual void SendMessageToObjectWithResponderReturnArg(int target_object_type, DDSKey target_key, int target_method_id,
    int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && message, std::string && return_arg) = 0;
  virtual void SendResponderCall(const DDSResponderCallBase & call_data) = 0;

  virtual void InsertIntoDatabaseWithResponderReturnArg(const char * collection, int data_object_type, std::string && data, DDSKey data_key,
    int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg) = 0;

  virtual void QueryDatabase(const char * collection, std::string && query,
    int responder_object_type, DDSKey responder_key, int responder_method_id, std::string && return_arg) = 0;

  virtual void CreateTimer(std::chrono::system_clock::duration duration, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg) = 0;
  virtual void CreateHttpRequest(const char * url, DDSKey key, int data_object_type, int target_method_id, std::string && return_arg) = 0;

  virtual DDSKey CreateSubscription(int target_object_type, DDSKey target_key, const char * path, int return_object_type,
    DDSKey return_key, int return_method_id, bool delta_only, std::string && return_arg) = 0;
  virtual DDSKey CreateDataSubscription(int target_object_type, DDSKey target_key, const char * path, int return_object_type,
    DDSKey return_key, int return_method_id, bool delta_only, std::string && return_arg) = 0;

  virtual void DestroySubscription(int return_object_type, DDSKey return_key, DDSKey subscription_id) = 0;
};

