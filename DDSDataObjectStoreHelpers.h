#pragma once

#include "DDSResponder.h"

#include "DDSServerToServerMessages.refl.meta.h"

#include <StormRefl\StormReflJsonStd.h>
#include <StormRefl\StormReflMetaCallJson.h>
#include <StormData\StormDataPath.h>
#include <StormData\StormDataChangePacket.h>
#include <StormData\StormDataChangeNotifier.h>

#define DDS_DECLARE_HAS_FUNC(FuncName) \
template <typename T> class DDSHasFunc##FuncName \
{  \
  public :template <typename C> static char test(decltype(&C::FuncName)); template <typename C> static long test(...);  static const bool value = sizeof(test<T>(0)) == sizeof(char); \
}; \

#define DDS_DECLARE_CALL_FUNC(FuncName) \
template <bool Enable> struct DDSCallFunc##FuncName \
{ \
  template <typename T, typename ... Args> static bool Call(T & t, Args && ... args) { t.FuncName(std::forward<Args>(args)...); return true; } \
}; \
template <> struct DDSCallFunc##FuncName<false> \
{ \
  template <typename T, typename ... Args> static bool Call(T & t, Args && ... args) { return false; } \
}; \

#define DDS_DECLARE_CALL(FuncName) \
  DDS_DECLARE_HAS_FUNC(FuncName) \
  DDS_DECLARE_CALL_FUNC(FuncName) \

#define DDS_CALL_FUNC(FuncName, Inst, ...) \
DDSCallFunc##FuncName<DDSHasFunc##FuncName<std::decay_t<decltype(Inst)>>::value>::Call(Inst, __VA_ARGS__)

inline bool DDSRequiresFullObject(DDSServerToServerMessageType type)
{
  return type != DDSServerToServerMessageType::kCreateDataSubscription;
}

inline bool DDSRequiresFullObject(const std::vector<DDSExportedMessage> & pending_messages)
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

  return requires_full_object;
}

inline bool DDSRequiresActiveObject(DDSServerToServerMessageType type)
{
  return DDSRequiresFullObject(type) && type != DDSServerToServerMessageType::kResponderCall;
}

inline bool DDSRequiresActiveObject(const std::vector<DDSExportedMessage> & pending_messages)
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

    return StormReflCallCheck(deserializer, c, func);
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
bool DDSDataObjectHandleMessage(DataType & dt, DDSNodeState & node_state, DDSTargetedMessage & message)
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

  DDSResponder responder = { node_state,{ 0, -1, -1 } };

  bool parsed = false;
  auto func_visitor = [&](auto f)
  {
    auto func_pointer = f.GetFunctionPtr();
    constexpr int func_index = f.GetFunctionIndex();
    constexpr bool use_responder = StormReflIsParamOfType<DataType, func_index, 0, DDSResponder &>();

    parsed = DDSMessageCaller<func_index, use_responder>::CallWithResponder(responder, deserializer, dt, func_pointer, "");
  };

  StormReflVisitFuncByIndex(dt, func_visitor, message.m_MethodId);
  return parsed;
}

template <class DataType>
bool DDSDataObjectHandleMessage(DataType & dt, DDSNodeState & node_state, DDSTargetedMessageWithResponder & message)
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

  DDSResponder responder = { node_state,{ message.m_ResponderKey, message.m_ResponderObjectType, message.m_ResponderMethodId } };

  bool parsed = false;
  auto func_visitor = [&](auto f)
  {
    auto func_pointer = f.GetFunctionPtr();
    constexpr int func_index = f.GetFunctionIndex();
    constexpr bool use_responder = StormReflIsParamOfType<DataType, func_index, 0, DDSResponder &>();

    parsed = DDSMessageCaller<func_index, use_responder>::CallWithResponder(responder, deserializer, dt, func_pointer, "");
  };

  StormReflVisitFuncByIndex(dt, func_visitor, message.m_MethodId);
  return parsed;
}

template <class DataType>
bool DDSDataObjectHandleMessage(DataType & dt, DDSNodeState & node_state, DDSResponderCallData & message)
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

  DDSResponder responder = { node_state,{ 0, -1, -1 } };

  bool parsed = false;
  auto func_visitor = [&](auto f)
  {
    auto func_pointer = f.GetFunctionPtr();
    constexpr int func_index = f.GetFunctionIndex();
    constexpr bool use_responder = StormReflIsParamOfType<DataType, func_index, 0, DDSResponder &>();

    parsed = DDSMessageCaller<func_index, use_responder>::CallWithResponder(responder, deserializer, dt, func_pointer, message.m_ResponderArgs);
  };

  StormReflVisitFuncByIndex(dt, func_visitor, message.m_MethodId);
  return parsed;
}

inline bool DDSCheckChangeSubscription(const ReflectionChangeNotification & change_notification, const DDSExportedSubscription & sub)
{
  return change_notification.m_Path.compare(0, sub.m_DataPath.length(), sub.m_DataPath) == 0;
}

template <class DataType>
bool DDSCreateSubscriptionResponse(DataType & data_type, const ReflectionChangeNotification & change_notification, const DDSExportedSubscription & sub, DDSResponderCallData & responder_data)
{
  responder_data.m_Key = sub.m_ResponderKey;
  responder_data.m_ObjectType = sub.m_ResponderObjectType;
  responder_data.m_MethodId = sub.m_ResponderMethodId;
  responder_data.m_ResponderArgs = sub.m_ResponderArgs;

  if (sub.m_DeltaOnly)
  {
    ReflectionChangeNotification notification_copy = change_notification;
    notification_copy.m_Path = notification_copy.m_Path.substr(sub.m_DataPath.size());

    responder_data.m_MethodArgs = StormDataCreateChangePacket(notification_copy);
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

    responder_data.m_MethodArgs = data;
  }

  return true;
}

template <class DataType>
bool DDSCreateInitialSubscriptionResponse(DataType & data_type, const DDSExportedSubscription & sub, DDSResponderCallData & responder_data)
{
  responder_data.m_Key = sub.m_ResponderKey;
  responder_data.m_ObjectType = sub.m_ResponderObjectType;
  responder_data.m_MethodId = sub.m_ResponderMethodId;
  responder_data.m_ResponderArgs = sub.m_ResponderArgs;

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

  if (sub.m_DeltaOnly)
  {
    responder_data.m_MethodArgs = StormDataCreateChangePacket(ReflectionNotifyChangeType::kSet, ReflectionChangeNotification::kInvalidSubIndex, "", data);
  }
  else
  {
    responder_data.m_MethodArgs = data;
  }

  return true;
}

inline void DDSCreateDeletedSubscriptionResponse(const DDSExportedSubscription & sub, DDSSubscriptionDeleted & responder_data)
{
  responder_data.m_ResponderKey = sub.m_ResponderKey;
  responder_data.m_ResponderObjectType = sub.m_ResponderObjectType;
  responder_data.m_ResponderMethodId = sub.m_ResponderMethodId;
  responder_data.m_SubscriptionId = sub.m_SubscriptionId;
}
