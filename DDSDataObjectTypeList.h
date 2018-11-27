#pragma once

#include <vector>

#include "DDSDataObjectStore.h"
#include "DDSDataObjectStoreTemporary.h"
#include "DDSDataObjectName.h"

template <class DataType, class DatabaseBackedType>
class DDSDataObjectStore;

class DDSNodeState;


template <class DataType, class DatabaseType, class ... Remaining>
struct DDSDataObjectTypeList
{
  static const int NumTypes = (sizeof...(Remaining) / 2) + 1;

  void operator()(std::vector<uint32_t> & data_name_list, std::vector<uint32_t> & database_name_list)
  {
    data_name_list.push_back(DDSDataObjectGetNameHash<DataType>());
    database_name_list.push_back(DDSDataObjectGetNameHash<DatabaseType>());

    auto next = DDSDataObjectTypeList<Remaining...>();
    next(data_name_list, database_name_list);
  }

  void operator()(DDSNodeState & node_state, std::vector<std::unique_ptr<DDSDataObjectStoreBase>> & list) const
  {
    list.push_back(std::make_unique<DDSDataObjectStore<DataType, DatabaseType>>(node_state, (int)list.size()));

    auto next = DDSDataObjectTypeList<Remaining...>();
    next(node_state, list);
  }
};


template <class DataType, class DatabaseType>
struct DDSDataObjectTypeList<DataType, DatabaseType>
{
  static const int NumTypes = 1;

  void operator()(std::vector<uint32_t> & data_name_list, std::vector<uint32_t> & database_name_list)
  {
    data_name_list.push_back(DDSDataObjectGetNameHash<DataType>());
    database_name_list.push_back(DDSDataObjectGetNameHash<DatabaseType>());
  }

  void operator()(DDSNodeState & node_state, std::vector<std::unique_ptr<DDSDataObjectStoreBase>> & list) const
  {
    list.push_back(std::make_unique<DDSDataObjectStore<DataType, DatabaseType>>(node_state, (int)list.size()));
  }
};
