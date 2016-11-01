#pragma once

#include "DDSKey.h"
#include "DDSDatabaseTypes.h"

#include <functional>
#include <memory>
#include <string>

struct DDSDatabaseConnectionInfo;

class DDSDatabaseConnection
{
public:
  DDSDatabaseConnection(const DDSDatabaseSettings & settings);
  ~DDSDatabaseConnection();

  std::pair<int, std::string> QueryDatabaseByKey(DDSKey key, const char * collection_name);
  std::pair<int, std::string> QueryDatabaseCustom(const std::string & query, const char * collection_name);
  int QueryDatabaseInsert(DDSKey key, const char * collection_name, const std::string & document);
  int QueryDatabaseUpsert(DDSKey key, const char * collection_name, const std::string & document);
  int QueryDatabaseDelete(DDSKey key, const char * collection_name);

private:
  std::unique_ptr<DDSDatabaseConnectionInfo> m_Info;
};
