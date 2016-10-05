#pragma once

#include <vector>

#include "DDSDataObjectStore.h"

template <class DataType, class DatabaseBackedType>
class DDSDataObjectStore;

template <class DataType, class DatabaseType, class ... Remaining>
struct DDSCreateDataObjectTypeList
{
  static const int NumTypes = (sizeof...(Remaining) / 2) + 1;

  auto operator()() const
  {
    return [](DDSNodeState & node_state, std::vector<std::unique_ptr<DDSDataObjectStoreBase>> & list)
    {
      list.push_back(std::make_unique<DDSDataObjectStore<DataType, DatabaseType>>(node_state, (int)list.size()));

      auto next = DDSCreateDataObjectTypeList<Remaining...>();
      auto func = next();
      func(node_state, list);
    };
  }
};

template <class DataType, class DatabaseType>
struct DDSCreateDataObjectTypeList<DataType, DatabaseType>
{
  static const int NumTypes = 1;

  auto operator()() const
  {
    return [](DDSNodeState & node_state, std::vector<std::unique_ptr<DDSDataObjectStoreBase>> & list)
    {
      list.push_back(std::make_unique<DDSDataObjectStore<DataType, DatabaseType>>(node_state, (int)list.size()));
    };
  }
};
