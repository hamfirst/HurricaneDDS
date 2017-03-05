
#include <thread>
#include <memory>
#include <string>
#include <vector>
#include <queue>

#include <optional/optional.hpp>
#include <gsl/gsl_util.h>

#include <hash/Hash.h>
#include <StormSockets/StormMessageQueue.h>
#include <StormSockets/StormSemaphore.h>

#include <mongoc/mongoc.h>
#include <libbson/bson.h>

#include "DDSDatabaseConnectionPool.h"


struct DatabaseQueryInfo
{
  DDSKey m_Key; 
  DDSDatabaseOperation m_Operation;
  std::string m_Collection;
  std::string m_Data;
  std::function<void(const char *, int)> m_Callback;
};

struct DatabaseQueryResult
{
  std::function<void(const char *, int)> m_Callback;
  uint32_t m_ErrorCode;
  std::string m_ResultData;
};

struct DatabaseConnectionThread
{
  int m_ThreadIndex;
  std::thread m_Thread;

  StormSockets::StormSemaphore m_Semaphore;
  StormSockets::StormMessageQueue<DatabaseQueryInfo> m_InputQueue = StormSockets::StormMessageQueue<DatabaseQueryInfo>(DDSDatabaseConnectionPool::kQueueSize);
  StormSockets::StormMessageQueue<DatabaseQueryResult> m_OutputQueue = StormSockets::StormMessageQueue<DatabaseQueryResult>(DDSDatabaseConnectionPool::kQueueSize);

  std::queue<DatabaseQueryInfo> m_PendingInputs;
};

void DDSDatabaseConnectionPool::QueueResult(int thread_index, const DatabaseQueryResult & result)
{
  while (m_Threads[thread_index].m_OutputQueue.Enqueue(result) == false)
  {
    std::this_thread::yield();
    if (m_Initialized == false)
    {
      return;
    }
  }
}

void DDSDatabaseConnectionPool::DatabaseThread(int thread_index)
{
  auto & thread_data = m_Threads[thread_index];

  auto client = mongoc_client_new(m_DatabaseUrl.data());
  auto destroy_client = gsl::finally([&]() { mongoc_client_destroy(client); });

  auto database = mongoc_client_get_database(client, m_DatabaseName.data());
  auto destroy_database = gsl::finally([&]() { mongoc_database_destroy(database); });

  bson_oid_t oid;

  while (m_Initialized)
  {
    thread_data.m_Semaphore.WaitOne(1000);

    DatabaseQueryInfo query;
    while(thread_data.m_InputQueue.TryDequeue(query))
    {
      memcpy(oid.bytes, &query.m_Key, sizeof(DDSKey));
      memcpy(&oid.bytes[4], &query.m_Key, sizeof(DDSKey));

      auto collection = mongoc_database_get_collection(database, query.m_Collection.data());
      auto collection_destroy = gsl::finally([&]() { mongoc_collection_destroy(collection); });

      switch (query.m_Operation)
      {
      case DDSDatabaseOperation::kKeyQuery:
        {
          auto * bson = bson_new();
          auto bson_auto_destroy = gsl::finally([&]() { bson_destroy(bson); });
          BSON_APPEND_OID(bson, "_id", &oid);

          auto cursor = mongoc_collection_find(collection, MONGOC_QUERY_NONE, 0, 1, 0, bson, nullptr, nullptr);
          auto cursor_destroy = gsl::finally([&]() { mongoc_cursor_destroy(cursor); });

          const bson_t * doc;
          if (mongoc_cursor_next(cursor, &doc))
          {
            char * str = bson_as_json(doc, NULL);
            auto str_destroy = gsl::finally([&]() { bson_free(str); });

            QueueResult(thread_index, DatabaseQueryResult{ query.m_Callback, 0, str });
          }
          else
          {
            QueueResult(thread_index, DatabaseQueryResult{ query.m_Callback, 1 });
          }
        }
        break;
      case DDSDatabaseOperation::kCustomQuery:
        {
          auto * bson = bson_new();
          auto bson_auto_destroy = gsl::finally([&]() { bson_destroy(bson); });

          bson_error_t parse_error;

          if (bson_init_from_json(bson, query.m_Data.c_str(), -1, &parse_error) == false)
          {
            DatabaseQueryResult result = { query.m_Callback, parse_error.code };
            QueueResult(thread_index, result);
            break;
          }

          auto cursor = mongoc_collection_find(collection, MONGOC_QUERY_NONE, 0, 1, 0, bson, nullptr, nullptr);
          auto cursor_destroy = gsl::finally([&]() { mongoc_cursor_destroy(cursor); });

          DatabaseQueryResult result = { query.m_Callback };

          const bson_t * doc;
          if (mongoc_cursor_next(cursor, &doc))
          {
            char * str = bson_as_json(doc, NULL);
            auto str_destroy = gsl::finally([&]() { bson_free(str); });

            QueueResult(thread_index, DatabaseQueryResult{ query.m_Callback, 0, str });
          }
          else
          {
            QueueResult(thread_index, DatabaseQueryResult{ query.m_Callback, 1 });
          }
        }
        break;
      case DDSDatabaseOperation::kInsert:
        {
          auto * bson = bson_new();
          auto bson_auto_destroy = gsl::finally([&]() { bson_destroy(bson); });

          bson_error_t parse_error;

          if (bson_init_from_json(bson, query.m_Data.c_str(), -1, &parse_error) == false)
          {
            DatabaseQueryResult result = { query.m_Callback, parse_error.code };
            QueueResult(thread_index, result);
            break;
          }

          BSON_APPEND_OID(bson, "_id", &oid);

          bson_error_t insert_error;

          if (mongoc_collection_insert(collection, MONGOC_INSERT_NONE, bson, nullptr, &insert_error) == false)
          {
            DatabaseQueryResult result = { query.m_Callback, insert_error.code };
            QueueResult(thread_index, result);
            break;
          }

          DatabaseQueryResult result = { query.m_Callback, 0 };
          QueueResult(thread_index, result);
        }
        break;
      case DDSDatabaseOperation::kUpdate:
      case DDSDatabaseOperation::kUpsert:
        {
          auto * bson_doc = bson_new();
          auto bson_doc_auto_destroy = gsl::finally([&]() { bson_destroy(bson_doc); });

          bson_error_t parse_error;

          if (bson_init_from_json(bson_doc, query.m_Data.c_str(), -1, &parse_error) == false)
          {
            DatabaseQueryResult result = { query.m_Callback, parse_error.code };
            QueueResult(thread_index, result);
            break;
          }

          auto * bson_query = bson_new();
          auto bson_query_auto_destroy = gsl::finally([&]() { bson_destroy(bson_query); });
          BSON_APPEND_OID(bson_query, "_id", &oid);

          auto flags = (query.m_Operation == DDSDatabaseOperation::kUpdate ? MONGOC_UPDATE_NONE : MONGOC_UPDATE_UPSERT);

          bson_error_t update_error;
          if (mongoc_collection_update(collection, flags, bson_query, bson_doc, nullptr, &update_error) == false)
          {
            DatabaseQueryResult result = { query.m_Callback, update_error.code };
            QueueResult(thread_index, result);
            break;
          }

          DatabaseQueryResult result = { query.m_Callback, 0 };
          QueueResult(thread_index, result);
        }
        break;
      case DDSDatabaseOperation::kDelete:
        {
          auto * bson = bson_new();
          auto bson_auto_destroy = gsl::finally([&]() { bson_destroy(bson); });
          BSON_APPEND_OID(bson, "_id", &oid);

          bson_error_t delete_error;
          if (mongoc_collection_remove(collection, MONGOC_REMOVE_SINGLE_REMOVE, bson, nullptr, &delete_error) == false)
          {
            DatabaseQueryResult result = { query.m_Callback, delete_error.code };
            QueueResult(thread_index, result);
            break;
          }

          DatabaseQueryResult result = { query.m_Callback, 0 };
          QueueResult(thread_index, result);
        }
        break;
      }
    }
  }
}

DDSDatabaseConnectionPool::DDSDatabaseConnectionPool(const DDSDatabaseSettings & settings)
{
  m_Initialized = true;
  m_NumThreads = settings.NumThreads;
  m_DatabaseName = settings.DatabaseName;
  m_DatabaseUrl = std::string("mongodb://") + settings.DatabaseHostName + ":" + std::to_string(settings.DatabasePort);

  m_Threads = std::make_unique<DatabaseConnectionThread[]>(settings.NumThreads);
  for (int index = 0; index < settings.NumThreads; index++)
  {
    m_Threads[index].m_Semaphore.Init(kQueueSize);
    m_Threads[index].m_Thread = std::thread(&DDSDatabaseConnectionPool::DatabaseThread, this, index);
  }
}

DDSDatabaseConnectionPool::~DDSDatabaseConnectionPool()
{
  if (m_Initialized == false)
  {
    return;
  }

  m_Initialized = false;

  for (int index = 0; index < m_NumThreads; index++)
  {
    m_Threads[index].m_Semaphore.Release();
    m_Threads[index].m_Thread.join();
  }

  m_Threads.release();
  m_NumThreads = 0;
}

void DDSDatabaseConnectionPool::QueryDatabase(DDSKey key, const char * collection, DDSDatabaseOperation operation,
                                  const char * data, std::function<void(const char *, int)> && result_callback)
{
  int thread_index = key % m_NumThreads;
  if (m_Threads[thread_index].m_PendingInputs.size() > 0 ||
      m_Threads[thread_index].m_InputQueue.Enqueue(DatabaseQueryInfo{ key, operation, collection, data ? data : "", result_callback }) == false)
  {
    m_Threads[thread_index].m_PendingInputs.emplace(DatabaseQueryInfo{ key, operation, collection, data ? data : "", result_callback });
  }
  else
  {
    m_Threads[thread_index].m_Semaphore.Release();
  }
}

void DDSDatabaseConnectionPool::QueryDatabaseByKey(DDSKey key, const char * collection, std::function<void(const char *, int)> && result_callback)
{
  QueryDatabase(key, collection, DDSDatabaseOperation::kKeyQuery, nullptr, std::move(result_callback));
}

void DDSDatabaseConnectionPool::QueryDatabaseCustom(const char * query, const char * collection, std::function<void(const char *, int)> && result_callback)
{
  QueryDatabase(crc32(query), collection, DDSDatabaseOperation::kCustomQuery, query, std::move(result_callback));
}

void DDSDatabaseConnectionPool::QueryDatabaseInsert(DDSKey key, const char * collection, const char * document, std::function<void(const char *, int)> && result_callback)
{
  QueryDatabase(key, collection, DDSDatabaseOperation::kInsert, document, std::move(result_callback));
}

void DDSDatabaseConnectionPool::QueryDatabaseUpsert(DDSKey key, const char * collection, const char * document, std::function<void(const char *, int)> && result_callback)
{
  QueryDatabase(key, collection, DDSDatabaseOperation::kUpsert, document, std::move(result_callback));
}

void DDSDatabaseConnectionPool::QueryDatabaseDelete(DDSKey key, const char * collection, std::function<void(const char *, int)> && result_callback)
{
  QueryDatabase(key, collection, DDSDatabaseOperation::kDelete, nullptr, std::move(result_callback));
}

void DDSDatabaseConnectionPool::TriggerCallbacks()
{
  for (int index = 0; index < m_NumThreads; index++)
  {
    DatabaseQueryResult result;
    while (m_Threads[index].m_OutputQueue.TryDequeue(result))
    {
      if (result.m_Callback)
      {
        result.m_Callback(result.m_ResultData.data(), result.m_ErrorCode);
      }
    }

    while(m_Threads[index].m_PendingInputs.size())
    {
      auto & query = m_Threads[index].m_PendingInputs.front();
      if (m_Threads[index].m_InputQueue.Enqueue(query) == false)
      {
        break;
      }

      m_Threads[index].m_PendingInputs.pop();
    }
  }
}

std::string DDSDatabaseConnectionPool::MemoryReport()
{
  std::string report = "Database:\n";
  for (int index = 0; index < m_NumThreads; index++)
  {
    report += "  Thread" + std::to_string(index);
    report += ": " + std::to_string(m_Threads[index].m_PendingInputs.size());
    report += "\n";
  }

  return report;
}
