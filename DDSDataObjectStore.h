#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <memory>


#include "DDSKey.h"
#include "DDSLog.h"
#include "DDSNodeState.h"
#include "DDSDataObjectStoreBase.h"
#include "DDSDatabaseConnectionPool.h"
#include "DDSResponder.h"
#include "DDSResponderCall.h"

#include <StormRefl\StormReflJson.h>
#include <StormData\StormDataPath.h>

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

  uint32_t GetDataClassNameHash()
  {
    return StormReflTypeInfo<DataType>::GetNameHash();
  }

  void HandleMessage(DDSKey key, DDSResponderData responder, const char * msg)
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
      ProcessMessage(key, obj_data, message, responder);
    }
    else
    {
      obj_data.m_PendingMessages.emplace_back(DDSExportedMessage{ message, responder });
    }
  }

  void HandleQuery(DDSKey key, DDSResponderData responder, const char * msg)
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
      auto visitor = [&](auto val)
      {
        StormReflEncodeJson(val, sb);
      };

      StormDataVisitPath(*itr->second.m_DatabaseObject.get(), visitor, query);
    }
    else
    {
      obj_data.m_PendingQueries.emplace_back(DDSExportedMessage{ message, responder });
    }
  }

  void ProcessMessage(DDSKey key, ObjectData & obj_data, const char * message, DDSResponder & responder)
  {
    //obj_data.m_ActiveObject->ProcessMessage(message, responder);
  }

  void ProcessQuery(ObjectData & obj_data, const char * query, DDSResponder & responder)
  {
    int error = 0;

    DatabaseBackedType & db_obj = *obj_data.m_DatabaseObject.get();
    std::string output;

    auto visitor = [&](auto & t)
    {
      output = StormReflEncodeJson(t, output);
    }

    if(StormDataVisitPath(db_obj) == false)
    {
      error = 1;
    }

    responder.SendResponse(error, output.c_str());
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

