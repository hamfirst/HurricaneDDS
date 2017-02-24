#pragma once

#include <string>
#include <vector>

#include <StormRefl/StormReflMetaFuncs.h>

#include "DDSDatabaseTypes.h"

struct DDSDatabaseBoostrapCollectionInfo
{
  std::string m_CollectionName;
  std::vector<std::string> m_Indices;
};

void DDSDatabaseBoostrapFullInternal(const std::vector<DDSDatabaseBoostrapCollectionInfo> & info, const DDSDatabaseSettings & settings);
void DDSDatabaseBoostrapIndicesInternal(const std::vector<DDSDatabaseBoostrapCollectionInfo> & info, const DDSDatabaseSettings & settings);

template <class DatabaseType>
void DDSDatabaseBoostrapAdd(std::vector<DDSDatabaseBoostrapCollectionInfo> & collections)
{
  DDSDatabaseBoostrapCollectionInfo info;
  info.m_CollectionName = DatabaseType::Collection();

  auto visitor = [&](auto f)
  {
    info.m_Indices.emplace_back(f.GetName());
  };

  StormReflVisitFieldsWithAnnotation<DatabaseType, decltype(visitor)>("UniqueIndex", visitor);
  collections.emplace_back(info);
}

template <>
inline void DDSDatabaseBoostrapAdd<void>(std::vector<DDSDatabaseBoostrapCollectionInfo> & collections)
{

}

template <class ... Args>
struct DDSDatabaseBoostrapInfo
{
  static void Process(std::vector<DDSDatabaseBoostrapCollectionInfo> & collections)
  {

  }
};

template <class DataType, class DatabaseType, class ... Remaining>
struct DDSDatabaseBoostrapInfo<DataType, DatabaseType, Remaining...>
{
  static void Process(std::vector<DDSDatabaseBoostrapCollectionInfo> & collections)
  {
    DDSDatabaseBoostrapAdd<DatabaseType>(collections);
    DDSDatabaseBoostrapInfo<Remaining...>::Process(collections);
  }
};

template <class DataType, class DatabaseType, class ... Remaining>
struct DDSDataObjectTypeList;

template <class ... Args>
void DDSDatabaseBoostrapFull(const DDSDataObjectTypeList<Args...> & list, const DDSDatabaseSettings & settings)
{
  std::vector<DDSDatabaseBoostrapCollectionInfo> collection_info;
  DDSDatabaseBoostrapInfo<Args...>::Process(collection_info);

  DDSDatabaseBoostrapFullInternal(collection_info, settings);
}

template <class ... Args>
void DDSDatabaseBoostrapFull(const DDSDataObjectTypeList<Args...> & list, 
  const std::vector<DDSDatabaseBoostrapCollectionInfo> & additional_collections, const DDSDatabaseSettings & settings)
{
  std::vector<DDSDatabaseBoostrapCollectionInfo> collection_info;
  DDSDatabaseBoostrapInfo<Args...>::Process(collection_info);

  collection_info.insert(additional_collections.end(), additional_collections.begin(), additional_collections.end());

  DDSDatabaseBoostrapFullInternal(collection_info, settings);
}


template <class ... Args>
void DDSDatabaseBoostrapIndices(const DDSDataObjectTypeList<Args...> & list, const DDSDatabaseSettings & settings)
{
  std::vector<DDSDatabaseBoostrapCollectionInfo> collection_info;
  DDSDatabaseBoostrapInfo<Args...>::Process(collection_info);

  DDSDatabaseBoostrapIndicesInternal(collection_info, settings);
}
