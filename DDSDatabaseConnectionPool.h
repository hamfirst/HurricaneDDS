#pragma once

#include "DDSKey.h"
#include "DDSDatabaseTypes.h"

#include <functional>
#include <memory>
#include <string>



enum class DDSDatabaseOperation
{
  kKeyQuery,
  kCustomQuery,
  kInsert,
  kUpdate,
  kUpsert,
  kDelete,
};

struct DatabaseConnectionThread;
struct DatabaseQueryResult;

class DDSDatabaseConnectionPool
{
public:
  DDSDatabaseConnectionPool(const DDSDatabaseSettings & settings);
  ~DDSDatabaseConnectionPool();

  void QueryDatabaseByKey(DDSKey key, const char * collection, std::function<void(const char *, int)> && result_callback);
  void QueryDatabaseCustom(const char * query, const char * collection, std::function<void(const char *, int)> && result_callback);
  void QueryDatabaseInsert(DDSKey key, const char * collection, const char * document, std::function<void(const char *, int)> && result_callback);
  void QueryDatabaseUpsert(DDSKey key, const char * collection, const char * document, std::function<void(const char *, int)> && result_callback);
  void QueryDatabaseDelete(DDSKey key, const char * collection, std::function<void(const char *, int)> && result_callback);

  void TriggerCallbacks();

  static const int kQueueSize = 256;

private:
  void QueueResult(int thread_index, const DatabaseQueryResult & result);
  void DatabaseThread(int thread_index);

  void QueryDatabase(DDSKey key, const char * collection, DDSDatabaseOperation operation,
    const char * data, std::function<void(const char *, int)> && result_callback);

private:
  volatile bool m_Initialized;
  int m_NumThreads;
  std::string m_DatabaseName;

  std::unique_ptr<DatabaseConnectionThread[]> m_Threads;
};


