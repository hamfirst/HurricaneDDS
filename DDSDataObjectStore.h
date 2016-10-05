#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <memory>


#include "DDSKey.h"
#include "DDSLog.h"
#include "DDSRandom.h"
#include "DDSNodeState.h"
#include "DDSDataObjectStoreBase.h"
#include "DDSDatabaseConnectionPool.h"
#include "DDSResponder.h"
#include "DDSResponderCall.h"
#include "DDSNodeInterface.h"

#include "DDSServerToServerMessages.refl.meta.h"

#include <StormRefl\StormReflJsonStd.h>
#include <StormRefl\StormReflMetaCallJson.h>
#include <StormData\StormDataPath.h>

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

  DDSResponder responder = { node_state, {0, -1, -1} };

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

  DDSResponder responder = { node_state, { message.m_ResponderKey, message.m_ResponderObjectType, message.m_ResponderMethodId } };

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

template <class DataType, class DatabaseBackedType>
class DDSDataObjectStore : public DDSDataObjectStoreBase
{
  enum ObjectState
  {
    kLoading,
    kDatabaseOnly,
    kCreating,
    kActive,
    kDeleted,
  };

  struct ObjectData
  {
    ObjectState m_State;
    std::unique_ptr<DataType> m_ActiveObject;
    std::unique_ptr<DatabaseBackedType> m_DatabaseObject;
    std::vector<DDSExportedMessage> m_PendingMessages;
    std::vector<DDSExportedMessage> m_PendingQueries;
  };

public:
  DDSDataObjectStore(DDSNodeState & node_state, int object_type_id) :
    m_NodeState(node_state), m_Collection(DatabaseBackedType::Collection()), m_ObjectTypeId(object_type_id)
  {

  }

  uint32_t GetDataClassNameHash() const
  {
    return StormReflTypeInfo<DataType>::GetNameHash();
  }

  uint32_t GetDatabaseClassNameHash() const
  {
    return StormReflTypeInfo<DatabaseBackedType>::GetNameHash();
  }

  void SpawnNewNonDatabaseBackedType(DDSKey key)
  {
    throw std::runtime_error("Trying to create a non database backed type for a database backed data store");
  }

  DDSKey GetUnusedKeyInRange(DDSKeyRange range)
  {
    while (true)
    {
      DDSKey size = GetKeyRangeSize(range);
      DDSKey test_key = (DDSGetRandomNumber64() % size) + range.m_Min;

      if (m_Objects.find(test_key) == m_Objects.end())
      {
        return test_key;
      }
    }
  }

  void HandleMessage(DDSKey key, DDSServerToServerMessageType message_type, const char * msg)
  {
    auto itr = m_Objects.find(key);
    auto & obj_data = itr == m_Objects.end() ? LoadObjectByKey(key) : itr->second;

    if (obj_data.m_State == kDatabaseOnly)
    {
      PromoteObject(key);
    }

    if (obj_data.m_State == kDeleted)
    {
      ReloadObjectByKey(key, obj_data);
    }

    if (obj_data.m_State == kActive)
    {
      ProcessMessage(obj_data, message_type, msg);
    }
    else
    {
      obj_data.m_PendingMessages.emplace_back(DDSExportedMessage{ message_type, msg });
    }
  }

  void HandleQuery(DDSKey key, DDSServerToServerMessageType message_type, const char * msg)
  {
    auto itr = m_Objects.find(key);
    auto & obj_data = itr == m_Objects.end() ? LoadObjectByKey(key) : itr->second;

    if (obj_data.m_State == kDeleted)
    {
      ReloadObjectByKey(key, obj_data);
    }

    if (obj_data.m_State != kLoading)
    {
      std::string sb;
      auto visitor = [&](auto val, const char * str)
      {
        StormReflEncodeJson(val, sb);
        return true;
      };

      StormDataVisitPath(*itr->second.m_DatabaseObject.get(), visitor, msg);
    }
    else
    {
      obj_data.m_PendingQueries.emplace_back(DDSExportedMessage{ message_type, msg });
    }
  }

  void ProcessMessage(ObjectData & obj_data, DDSServerToServerMessageType message_type, const char * message)
  {
    switch (message_type)
    {
      case DDSServerToServerMessageType::kTargetedMessage:
      {
        DDSTargetedMessage targeted_msg;
        StormReflParseJson(targeted_msg, message);
        if (DDSDataObjectHandleMessage(*obj_data.m_ActiveObject.get(), m_NodeState, targeted_msg))
        {
          DDSLog::LogError("Failed to process message for object");
        }
      }
      break;
      case DDSServerToServerMessageType::kTargetedMessageResponder:
      {
        DDSTargetedMessageWithResponder targeted_msg;
        StormReflParseJson(targeted_msg, message);
        if (DDSDataObjectHandleMessage(*obj_data.m_ActiveObject.get(), m_NodeState, targeted_msg))
        {
          DDSLog::LogError("Failed to process message for object");
        }
      }
      break;
      case DDSServerToServerMessageType::kResponderCall:
      {
        DDSResponderCallData responder_call;
        StormReflParseJson(responder_call, message);
        if (DDSDataObjectHandleMessage(*obj_data.m_ActiveObject.get(), m_NodeState, responder_call))
        {
          DDSLog::LogError("Failed to process message for object");
        }
      }
      break;
      default:
      {
        DDSLog::LogError("Invalid message type");
      }
    }
  }

  ObjectData & LoadObjectByKey(DDSKey key)
  {
    auto insert_data = m_Objects.emplace(std::make_pair(key, ObjectData{ kLoading }));
    DDSQueryDatabaseByKey(key, m_Collection.c_str(), [this, key](const char * data, int ec) { HandleLoadResult(key, data, ec); });

    return insert_data.first->second;
  }

  void ReloadObjectByKey(DDSKey key, ObjectData & obj_data)
  {
    obj_data.m_State = kLoading;
    DDSQueryDatabaseByKey(key, m_Collection.c_str(), [this, key](const char * data, int ec) { HandleLoadResult(key, data, ec); });
  }

  void HandleLoadResult(DDSKey key, const char * data, int ec)
  {
    if (ec)
    {
      auto & obj_data = m_Objects.at(key);
      obj_data.m_State = kDeleted;
      return;
    }
  }

  void PromoteObject(DDSKey key)
  {
    auto & obj_data = m_Objects.at(key);
    if (obj_data.m_State != kDatabaseOnly || obj_data.m_ActiveObject.get() != nullptr)
    {
      DDSLog::LogError("Incosistent object state");
      return;
    }

    obj_data.m_State = kCreating;
    obj_data.m_ActiveObject = std::make_unique<DataType>();

    LoadActiveObject(key, *obj_data.m_ActiveObject.get(), *obj_data.m_DatabaseObject.get());
  }

  void FinalizeActiveObject(DDSKey key)
  {
    auto & obj_data = m_Objects.at(key);
    obj_data.m_State = kActive;
  }

  void LoadActiveObject(DDSKey key, DataType & data, const DatabaseBackedType & db)
  {
    FinalizeActiveObject(key);
  }

  bool ExportObjectsInRange(DDSKeyRange requested_range, DDSKeyRange & output_range, DDSKeyRange & remainder_range, int max_objects, std::vector<DDSExportedObject> & output)
  {
    int num_objects = 0;
    bool complete = true;

    output_range = requested_range;

    if (m_Objects.size() == 0)
    {
      return true;
    }

    auto start_itr = m_Objects.lower_bound(requested_range.m_Min);
    auto itr = start_itr;

    if (itr == m_Objects.end())
    {
      itr = m_Objects.begin();
    }

    std::vector<decltype(itr)> saved_itrs;

    while(true)
    {
      if (num_objects >= max_objects)
      {
        complete = false;
        output_range = DDSKeyRange{ requested_range.m_Min, itr->first - 1 };
        remainder_range = DDSKeyRange{ itr->first, requested_range.m_Max };
        break;
      }

      if (KeyInKeyRange(itr->first, requested_range) == false)
      {
        break;
      }

      if (itr->second.m_State == kActive || itr->second.m_PendingMessages.size() > 0 || itr->second.m_PendingQueries.size() > 0)
      {
        DDSExportedObject obj = { itr->first };
        if (itr->second.m_ActiveObject)
        {
          StormReflEncodeJson(*itr->second.m_ActiveObject.get(), obj.m_ActiveObject);
          num_objects++;
        }

        if (itr->second.m_DatabaseObject)
        {
          StormReflEncodeJson(*itr->second.m_DatabaseObject.get(), obj.m_DatabaseObject);
          num_objects++;
        }

        for (auto & message : itr->second.m_PendingMessages)
        {
          obj.m_PendingMessages.emplace_back(message);
          num_objects++;
        }

        for (auto & message : itr->second.m_PendingQueries)
        {
          obj.m_PendingQueries.emplace_back(message);
          num_objects++;
        }

        output.emplace_back(std::move(obj));
        num_objects++;

        saved_itrs.push_back(itr);
      }

      itr++;
      if (itr == m_Objects.end())
      {
        itr = m_Objects.begin();
      }

      if (itr == start_itr)
      {
        break;
      }
    }

    for (auto itr : saved_itrs)
    {
      m_Objects.erase(itr);
    }

    return complete;
  }

  void ProcessExportedObjects(const std::vector<DDSExportedObject> & object_list)
  {
    for (auto & object : object_list)
    {
      ObjectData obj_data = { kLoading, std::make_unique<DataType>(), std::make_unique<DatabaseBackedType>() };

      obj_data.m_PendingMessages = std::move(object.m_PendingMessages);
      obj_data.m_PendingQueries = std::move(object.m_PendingQueries);

      if (object.m_ActiveObject.size() > 0)
      {
        if (StormReflParseJson(*obj_data.m_ActiveObject.get(), object.m_ActiveObject.c_str()) == false)
        {
          DDSLog::LogError("Could not properly parse external sync message");
          return;
        }

        if (StormReflParseJson(*obj_data.m_DatabaseObject.get(), object.m_DatabaseObject.c_str()) == false)
        {
          DDSLog::LogError("Could not properly parse external sync message");
          return;
        }

        obj_data.m_State = kActive;
        m_Objects.emplace(std::make_pair(object.m_Key, std::move(obj_data)));
      }
      else if (object.m_DatabaseObject.size() > 0)
      {
        if (StormReflParseJson(*obj_data.m_DatabaseObject.get(), object.m_DatabaseObject.c_str()) == false)
        {
          DDSLog::LogError("Could not properly parse external sync message");
          return;
        }

        obj_data.m_State = kDatabaseOnly;

        m_Objects.emplace(std::make_pair(object.m_Key, std::move(obj_data)));
        PromoteObject(object.m_Key);
      }
      else
      {
        auto result = m_Objects.emplace(std::make_pair(object.m_Key, std::move(obj_data)));
        ReloadObjectByKey(object.m_Key, result.first->second);
      }
    }
  }

private:

  DDSNodeState & m_NodeState;
  std::string m_Collection;
  int m_ObjectTypeId;

  std::unordered_map<DDSKey, ObjectData> m_Objects;
};


template <class DataType>
class DDSDataObjectStore<DataType, void> : public DDSDataObjectStoreBase
{
  struct ObjectData
  {
    std::unique_ptr<DataType> m_ActiveObject;
  };

public:

  DDSDataObjectStore(DDSNodeState & node_state, int object_type_id) :
    m_NodeState(node_state), m_ObjectTypeId(object_type_id)
  {

  }

  uint32_t GetDataClassNameHash() const
  {
    return StormReflTypeInfo<DataType>::GetNameHash();
  }

  uint32_t GetDatabaseClassNameHash() const
  {
    return 0;
  }

  void SpawnNewNonDatabaseBackedType(DDSKey key)
  {
    DDSNodeInterface node_interface(m_NodeState, this, key);
    m_Objects.emplace(std::make_pair(key, ObjectData{ std::make_unique<DataType>(node_interface) }));
  }

  DDSKey GetUnusedKeyInRange(DDSKeyRange range)
  {
    while (true)
    {
      DDSKey size = GetKeyRangeSize(range);
      DDSKey test_key = (DDSGetRandomNumber64() % size) + range.m_Min;

      if (m_Objects.find(test_key) == m_Objects.end())
      {
        return test_key;
      }
    }
  }

  void DestroyObject(DDSKey key)
  {
    m_Objects.erase(key);
  }

  void HandleMessage(DDSKey key, DDSServerToServerMessageType message_type, const char * msg)
  {
    auto itr = m_Objects.find(key);
    if (itr == m_Objects.end())
    {
      return;
    }

    auto & obj_data = itr->second;

    ProcessMessage(obj_data, message_type, msg);
  }

  void HandleQuery(DDSKey key, DDSServerToServerMessageType message_type, const char * msg)
  {
    DDSLog::LogError("Query sent to invalid data object");
  }

  void ProcessMessage(ObjectData & obj_data, DDSServerToServerMessageType message_type, const char * message)
  {
    switch (message_type)
    {
      case DDSServerToServerMessageType::kTargetedMessage:
      {
        DDSTargetedMessage targeted_msg;
        StormReflParseJson(targeted_msg, message);
        if (DDSDataObjectHandleMessage(*obj_data.m_ActiveObject.get(), m_NodeState, targeted_msg))
        {
          DDSLog::LogError("Failed to process message for object");
        }
      }
      break;
      case DDSServerToServerMessageType::kTargetedMessageResponder:
      {
        DDSTargetedMessageWithResponder targeted_msg;
        StormReflParseJson(targeted_msg, message);
        if (DDSDataObjectHandleMessage(*obj_data.m_ActiveObject.get(), m_NodeState, targeted_msg))
        {
          DDSLog::LogError("Failed to process message for object");
        }
      }
      break;
      case DDSServerToServerMessageType::kResponderCall:
      {
        DDSResponderCallData responder_call;
        StormReflParseJson(responder_call, message);
        if (DDSDataObjectHandleMessage(*obj_data.m_ActiveObject.get(), m_NodeState, responder_call))
        {
          DDSLog::LogError("Failed to process message for object");
        }
      }
      break;
      default:
      {
        DDSLog::LogError("Invalid message type");
      }
    }
  }

  bool ExportObjectsInRange(DDSKeyRange requested_range, DDSKeyRange & output_range, DDSKeyRange & remainder_range, int max_objects, std::vector<DDSExportedObject> & output)
  {
    int num_objects = 0;
    bool complete = true;

    output_range = requested_range;

    if (m_Objects.size() == 0)
    {
      return true;
    }

    auto start_itr = m_Objects.lower_bound(requested_range.m_Min);
    auto itr = start_itr;

    if (itr == m_Objects.end())
    {
      itr = m_Objects.begin();
    }

    std::vector<decltype(itr)> saved_itrs;

    while (true)
    {
      if (num_objects >= max_objects)
      {
        complete = false;
        output_range = DDSKeyRange{ requested_range.m_Min, itr->first - 1 };
        remainder_range = DDSKeyRange{ itr->first, requested_range.m_Max };
        break;
      }

      if (KeyInKeyRange(itr->first, requested_range) == false)
      {
        break;
      }

      DDSExportedObject obj = { itr->first };
      StormReflEncodeJson(*itr->second.m_ActiveObject.get(), obj.m_ActiveObject);

      output.emplace_back(std::move(obj));
      num_objects++;

      saved_itrs.push_back(itr);

      itr++;
      if (itr == m_Objects.end())
      {
        itr = m_Objects.begin();
      }

      if (itr == start_itr)
      {
        break;
      }
    }

    for (auto itr : saved_itrs)
    {
      m_Objects.erase(itr);
    }

    return complete;
  }

  void ProcessExportedObjects(const std::vector<DDSExportedObject> & object_list)
  {
    for (auto & object : object_list)
    {
      DDSNodeInterface node_interface(m_NodeState, this, object.m_Key);
      ObjectData obj_data = { std::make_unique<DataType>(node_interface) };

      if (StormReflParseJson(*obj_data.m_ActiveObject.get(), object.m_ActiveObject.c_str()) == false)
      {
        DDSLog::LogError("Could not properly parse external sync message");
        return;
      }

      m_Objects.emplace(std::make_pair(object.m_Key, std::move(obj_data)));
    }
  }

private:

  DDSNodeState & m_NodeState;
  std::string m_Collection;
  int m_ObjectTypeId;

  std::unordered_map<DDSKey, ObjectData> m_Objects;
};