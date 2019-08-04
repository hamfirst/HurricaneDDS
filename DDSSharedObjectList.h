#pragma once

#include <vector>
#include <memory>

#include "DDSSharedObject.h"
#include "DDSDataObjectName.h"

template <class DataType, class DatabaseBackedType>
class DDSDataObjectStore;

class DDSCoordinatorState;
class DDSNodeState;


template <class ... Types>
struct DDSSharedObjectTypeList
{
  static const int NumTypes = 0;

  void operator()(DDSCoordinatorState & coordinator_state, std::vector<std::unique_ptr<DDSSharedObjectBase>> & list, int num_data_objects) const
  {
    
  }

  void operator()(DDSNodeState & node_state, std::vector<std::unique_ptr<DDSSharedObjectCopyBase>> & list, int num_data_objects) const
  {

  }

  void operator()(std::vector<uint32_t> & shared_name_list) const
  {

  }
};


template <class DataType, class ... Remaining>
struct DDSSharedObjectTypeList<DataType, Remaining...>
{
  static const int NumTypes = sizeof...(Remaining) + 1;

  void operator()(DDSCoordinatorState & coordinator_state, std::vector<std::unique_ptr<DDSSharedObjectBase>> & list, int num_data_objects) const
  {
    list.push_back(std::make_unique<DDSSharedObject<DataType>>(coordinator_state, (int)list.size() + num_data_objects));

    auto next = DDSSharedObjectTypeList<Remaining...>();
    next(coordinator_state, list, num_data_objects);
  }

  void operator()(DDSNodeState & node_state, std::vector<std::unique_ptr<DDSSharedObjectCopyBase>> & list, int num_data_objects) const
  {
    list.push_back(std::make_unique<DDSSharedObjectCopy<DataType>>(node_state, (int)list.size() + num_data_objects));

    auto next = DDSSharedObjectTypeList<Remaining...>();
    next(node_state, list, num_data_objects);
  }

  void operator()(std::vector<uint32_t> & shared_name_list) const
  {
    shared_name_list.push_back(DDSDataObjectGetNameHash<DataType>());

    auto next = DDSSharedObjectTypeList<Remaining...>();
    next(shared_name_list);
  }
};


