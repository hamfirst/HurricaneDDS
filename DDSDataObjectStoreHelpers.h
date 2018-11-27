#pragma once

#include "DDSResponder.h"

#include "DDSServerToServerMessages.refl.meta.h"

#include <StormRefl/StormReflJsonStd.h>
#include <StormRefl/StormReflMetaCallJson.h>
#include <StormData/StormDataPath.h>
#include <StormData/StormDataChangePacket.h>
#include <StormData/StormDataChangeNotifier.h>

inline bool DDSRequiresAnyObject(DDSServerToServerMessageType type)
{
  return type != DDSServerToServerMessageType::kCreateSubscription &&
         type != DDSServerToServerMessageType::kDestroySubscription;
}

inline bool DDSRequiresFullObject(DDSServerToServerMessageType type)
{
  return type != DDSServerToServerMessageType::kCreateSubscription &&
         type != DDSServerToServerMessageType::kDestroySubscription;
}

inline bool DDSRequiresFullObject(const std::vector<DDSExportedMessage> & pending_messages, const std::vector<DDSExportedSubscription> & subs)
{
  bool requires_full_object = false;
  for (auto & msg : pending_messages)
  {
    if (DDSRequiresFullObject(msg.m_Type))
    {
      requires_full_object = true;
      break;
    }
  }

  if (requires_full_object == false)
  {
    for (auto & sub : subs)
    {
      if (sub.m_IsDataSubscription == false && sub.m_ForceLoad)
      {
        requires_full_object = true;
        break;
      }
    }
  }

  return requires_full_object;
}

inline bool DDSRequiresActiveObject(DDSServerToServerMessageType type)
{
  return DDSRequiresFullObject(type) &&
    type != DDSServerToServerMessageType::kResponderCall; // This allows the object to call or subscribe to other objects when loading
}

inline bool DDSRequiresActiveObject(const std::vector<DDSExportedMessage> & pending_messages, const std::vector<DDSExportedSubscription> & subs)
{
  bool requires_active_object = false;
  for (auto & msg : pending_messages)
  {
    if (DDSRequiresActiveObject(msg.m_Type))
    {
      requires_active_object = true;
      break;
    }
  }

  if (requires_active_object == false)
  {
    for (auto & sub : subs)
    {
      if (sub.m_IsDataSubscription == false && sub.m_ForceLoad)
      {
        requires_active_object = true;
        break;
      }
    }
  }

  return requires_active_object;
}

template <typename ReturnArg>
struct DDSMessageCallerNoResponder
{
  template <class Deserializer, class C, typename ... Args>
  static bool Call(Deserializer && deserializer, C & c, void (C::*func)(Args...), const std::string & str)
  {
    if (str.length() > 0)
    {
      std::remove_const_t<std::remove_reference_t<ReturnArg>> arg{};
      StormReflParseJson(arg, str.c_str());
      return StormReflCallCheck(deserializer, c, func, arg);
    }

    return StormReflCallCheck(deserializer, c, func);
  }
};

template <>
struct DDSMessageCallerNoResponder<void>
{
  template <class Deserializer, class C, typename ... Args>
  static bool Call(Deserializer && deserializer, C & c, void (C::*func)(Args...), const std::string & return_arg)
  {
    return StormReflCallCheck(deserializer, c, func);
  }
};

template <typename ReturnArg>
struct DDSMessageCallerWithResponder
{
  template <class Deserializer, class C, typename ... Args>
  static bool Call(DDSResponder & responder, Deserializer && deserializer, C & c, void (C::*func)(Args...), const std::string & str)
  {
    if (str.length() > 0)
    {
      std::remove_const_t<std::remove_reference_t<ReturnArg>> arg{};
      StormReflParseJson(arg, str.c_str());
      return StormReflCallCheck(deserializer, c, func, responder, arg);
    }

    return StormReflCallCheck(deserializer, c, func, responder);
  }
};

template <>
struct DDSMessageCallerWithResponder<void>
{
  template <class Deserializer, class C, typename ... Args>
  static bool Call(DDSResponder & responder, Deserializer && deserializer, C & c, void (C::*func)(Args...), const std::string & return_arg)
  {
    return StormReflCallCheck(deserializer, c, func, responder);
  }
};


template <int FuncIndex, bool TakesResponder>
struct DDSMessageCaller
{
  template <class Deserializer, class C, typename ... Args>
  static bool CallWithResponder(DDSResponder & responder, Deserializer && deserializer, C & c, void (C::*func)(Args...), const std::string & return_arg)
  {
    using ParamType = typename StormReflGetParamType<C, FuncIndex, 0>::type;
    return DDSMessageCallerNoResponder<ParamType>::Call(deserializer, c, func, return_arg);
  }
};

template <int FuncIndex>
struct DDSMessageCaller<FuncIndex, true>
{
  template <class Deserializer, class C, typename ... Args>
  static bool CallWithResponder(DDSResponder & responder, Deserializer && deserializer, C & c, void (C::*func)(Args...), const std::string & return_arg)
  {
    using ParamType = typename StormReflGetParamType<C, FuncIndex, 1>::type;
    return DDSMessageCallerWithResponder<ParamType>::Call(responder, deserializer, c, func, return_arg);
  }
};

template <class DataType>
bool DDSDataObjectHandleMessage(DataType & dt, DDSObjectInterface & iface, DDSTargetedMessage & message)
{
  const char * str = message.m_MethodArgs.c_str();
  StormReflJsonAdvanceWhiteSpace(str);
  if (*str != '[')
  {
    return false;
  }

  str++;

  auto deserializer = [&](auto & t, bool final_arg)
  {
    if (StormReflParseJson(t, str, str) == false)
    {
      return false;
    }

    StormReflJsonAdvanceWhiteSpace(str);
    if (final_arg)
    {
      if (*str != ']')
      {
        return false;
      }

      return true;
    }
    else
    {
      if (*str != ',')
      {
        return false;
      }

      str++;
      return true;
    }
  };

  DDSResponder responder = CreateEmptyResponder(iface);

  bool parsed = false;
  auto func_visitor = [&](auto f)
  {
    auto func_pointer = f.GetFunctionPtr();
    constexpr int func_index = f.GetFunctionIndex();
    constexpr bool use_responder = StormReflIsParamOfType<DataType, func_index, 0, DDSResponder &>();

    parsed = DDSMessageCaller<func_index, use_responder>::CallWithResponder(responder, deserializer, dt, func_pointer, "");
  };

  StormReflVisitFuncByIndex(dt, func_visitor, message.m_MethodId);

  if (parsed == false)
  {
    return false;
  }

  return parsed;
}

template <class DataType>
bool DDSDataObjectHandleMessage(DataType & dt, DDSObjectInterface & iface, DDSTargetedMessageWithResponder & message)
{
  const char * str = message.m_MethodArgs.c_str();
  StormReflJsonAdvanceWhiteSpace(str);
  if (*str != '[')
  {
    return false;
  }

  str++;

  auto deserializer = [&](auto & t, bool final_arg)
  {
    if (StormReflParseJson(t, str, str) == false)
    {
      return false;
    }

    StormReflJsonAdvanceWhiteSpace(str);
    if (final_arg)
    {
      if (*str != ']')
      {
        return false;
      }

      return true;
    }
    else
    {
      if (*str != ',')
      {
        return false;
      }

      str++;
      return true;
    }
  };

  DDSResponder responder = { iface, { message.m_ResponderKey, message.m_ResponderObjectType, message.m_ResponderMethodId, message.m_ErrorMethodId, message.m_ReturnArg } };

  bool parsed = false;
  auto func_visitor = [&](auto f)
  {
    auto func_pointer = f.GetFunctionPtr();
    constexpr int func_index = f.GetFunctionIndex();
    constexpr bool use_responder = StormReflIsParamOfType<DataType, func_index, 0, DDSResponder &>();

    parsed = DDSMessageCaller<func_index, use_responder>::CallWithResponder(responder, deserializer, dt, func_pointer, "");
  };

  StormReflVisitFuncByIndex(dt, func_visitor, message.m_MethodId);

  if (parsed == false)
  {
    return false;
  }

  return parsed;
}

template <class DataType>
bool DDSDataObjectHandleMessage(DataType & dt, DDSObjectInterface & iface, DDSResponderCallData & message)
{
  const char * str = message.m_MethodArgs.c_str();
  StormReflJsonAdvanceWhiteSpace(str);
  if (*str != '[')
  {
    return false;
  }

  str++;

  auto deserializer = [&](auto & t, bool final_arg)
  {
    if (StormReflParseJson(t, str, str) == false)
    {
      return false;
    }

    StormReflJsonAdvanceWhiteSpace(str);
    if (final_arg)
    {
      if (*str != ']')
      {
        return false;
      }

      return true;
    }
    else
    {
      if (*str != ',')
      {
        return false;
      }

      str++;
      return true;
    }
  };

  DDSResponder responder = CreateEmptyResponder(iface);

  bool parsed = false;
  auto func_visitor = [&](auto f)
  {
    auto func_pointer = f.GetFunctionPtr();
    constexpr int func_index = f.GetFunctionIndex();
    constexpr bool use_responder = StormReflIsParamOfType<DataType, func_index, 0, DDSResponder &>();

    parsed = DDSMessageCaller<func_index, use_responder>::CallWithResponder(responder, deserializer, dt, func_pointer, message.m_ResponderArgs);
  };

  StormReflVisitFuncByIndex(dt, func_visitor, message.m_MethodId);

  if (parsed == false)
  {
    return false;
  }

  return parsed;
}

template <typename SubscriptionObj, typename NodeState>
inline bool DDSSendChangeSubscription(const ReflectionChangeNotification & change_notification, const DDSExportedSubscription & sub, SubscriptionObj * base_obj, NodeState & node_state)
{
  DDSLog::LogVerbose("Sending subscription response from object %s", typeid(SubscriptionObj).name());

  DDSResponderCallData call_data;
  if (DDSCreateSubscriptionResponse(*base_obj, change_notification, sub, call_data) == false)
  {
    DDSLog::LogError("Could not serialize subscription change");
  }

  node_state.SendTargetedMessage(DDSDataObjectAddress{ call_data.m_ObjectType, call_data.m_Key }, DDSResponderCallData::Type, StormReflEncodeJson(call_data));
  return true;
}

template <class DataType>
bool DDSCreateSubscriptionResponse(DataType & data_type, const ReflectionChangeNotification & change_notification, const DDSExportedSubscription & sub, DDSResponderCallData & responder_data)
{
  responder_data.m_Key = sub.m_ResponderKey;
  responder_data.m_ObjectType = sub.m_ResponderObjectType;
  responder_data.m_MethodId = sub.m_ResponderMethodId;
  responder_data.m_ResponderArgs = sub.m_ResponderArgs;

  if (sub.m_State != kSubSentValid)
  {
    DDSLog::LogError("Didn't sent initial subscription response");
  }

  if (sub.m_DeltaOnly)
  {
    ReflectionChangeNotification notification_copy = change_notification;
    notification_copy.m_Path = notification_copy.m_Path.substr(sub.m_DataPath.size());

    responder_data.m_MethodArgs = "[";
    responder_data.m_MethodArgs += StormReflEncodeJson(StormDataCreateChangePacket(notification_copy));
    responder_data.m_MethodArgs += "]";
  }
  else
  {
    std::string data;
    auto visitor = [&](auto & f, const char * str)
    {
      data = StormReflEncodeJson(f);
      return true;
    };

    if (StormDataVisitPath(data_type, visitor, sub.m_DataPath.c_str()) == false)
    {
      return false;
    }

    responder_data.m_MethodArgs = "[";
    responder_data.m_MethodArgs += StormReflEncodeJson(data);
    responder_data.m_MethodArgs += "]";
  }

  return true;
}

template <class DataType>
bool DDSCreateInitialSubscriptionResponse(DataType & data_type, DDSExportedSubscription & sub, DDSResponderCallData & responder_data)
{
  responder_data.m_Key = sub.m_ResponderKey;
  responder_data.m_ObjectType = sub.m_ResponderObjectType;
  responder_data.m_MethodId = sub.m_ResponderMethodId;
  responder_data.m_ResponderArgs = sub.m_ResponderArgs;

  DDSLog::LogVerbose("Sending initial subscription response from object %s", typeid(DataType).name());

  std::string data;
  auto visitor = [&](auto & f, const char * str)
  {
    data = StormReflEncodeJson(f);
    return true;
  };

  if (StormDataVisitPath(data_type, visitor, sub.m_DataPath.c_str()) == false)
  {
    sub.m_State = kSubSentInvalid;
    if (sub.m_ErrorMethodId != -1)
    {
      responder_data.m_MethodArgs = "[]";
      responder_data.m_MethodId = sub.m_ErrorMethodId;
      return true;
    }
    else
    {
      return false;
    }
  }

  sub.m_State = kSubSentValid;

  responder_data.m_MethodArgs = "[";
  if (sub.m_DeltaOnly)
  {
    responder_data.m_MethodArgs += 
      StormReflEncodeJson(StormDataCreateChangePacket(ReflectionNotifyChangeType::kSet, ReflectionChangeNotification::kInvalidSubIndex, "", data));
  }
  else
  {
    responder_data.m_MethodArgs += StormReflEncodeJson(data);
  }
  responder_data.m_MethodArgs += "]";

  return true;
}

inline bool DDSCreateErrorSubscriptionResponse(DDSExportedSubscription & sub, DDSResponderCallData & responder_data)
{
  sub.m_State = kSubSentInvalid;

  if (sub.m_ErrorMethodId == -1)
  {
    return false;
  }

  responder_data.m_Key = sub.m_ResponderKey;
  responder_data.m_ObjectType = sub.m_ResponderObjectType;
  responder_data.m_MethodId = sub.m_ErrorMethodId;
  responder_data.m_MethodArgs = "[]";
  responder_data.m_ResponderArgs = sub.m_ResponderArgs;
  return true;
}

inline void DDSCreateDeletedSubscriptionResponse(const DDSExportedSubscription & sub, DDSSubscriptionDeleted & responder_data)
{
  responder_data.m_Key = sub.m_ResponderKey;
  responder_data.m_ObjectType = sub.m_ResponderObjectType;
  responder_data.m_SubscriptionId = sub.m_SubscriptionId;
}
