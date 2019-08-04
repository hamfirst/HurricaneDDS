
#include <thread>
#include <memory>
#include <string>
#include <vector>
#include <queue>
#include <optional>

#include <hash/Hash.h>
#include <StormSockets/StormMessageQueue.h>
#include <StormSockets/StormSemaphore.h>

#include <mongoc/mongoc.h>
#include <libbson/bson.h>

#include "DDSDatabaseConnection.h"

struct DDSDatabaseConnectionInfo
{
  mongoc_client_t * m_MongoClient;
  mongoc_database_t * m_Database;
};


DDSDatabaseConnection::DDSDatabaseConnection(const DDSDatabaseSettings & settings) :
  m_Info(std::make_unique<DDSDatabaseConnectionInfo>())
{
  std::string database_url = std::string("mongodb://") + settings.DatabaseHostName + ":" + std::to_string(settings.DatabasePort);

  m_Info->m_MongoClient = mongoc_client_new(database_url.data());
  m_Info->m_Database = mongoc_client_get_database(m_Info->m_MongoClient, settings.DatabaseName);
}

DDSDatabaseConnection::~DDSDatabaseConnection()
{
  mongoc_client_destroy(m_Info->m_MongoClient);
  mongoc_database_destroy(m_Info->m_Database);
}

std::pair<int, std::string> DDSDatabaseConnection::QueryDatabaseByKey(DDSKey key, const char * collection_name)
{
  bson_oid_t oid;
  memcpy(&oid.bytes[0], &key, sizeof(DDSKey));
  memcpy(&oid.bytes[4], &key, sizeof(DDSKey));

  auto collection = mongoc_database_get_collection(m_Info->m_Database, collection_name);
  auto collection_destroy = gsl::finally([&]() { mongoc_collection_destroy(collection); });

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

    return std::make_pair(0, str);
  }
  else
  {
    return{};
  }
}

std::pair<int, std::string> DDSDatabaseConnection::QueryDatabaseCustom(const std::string & query, const char * collection_name)
{
  auto collection = mongoc_database_get_collection(m_Info->m_Database, collection_name);
  auto collection_destroy = gsl::finally([&]() { mongoc_collection_destroy(collection); });

  auto * bson = bson_new();
  auto bson_auto_destroy = gsl::finally([&]() { bson_destroy(bson); });

  bson_error_t parse_error;

  if (bson_init_from_json(bson, query.data(), -1, &parse_error) == false)
  {
    return std::make_pair(parse_error.code, "");
  }

  auto cursor = mongoc_collection_find(collection, MONGOC_QUERY_NONE, 0, 1, 0, bson, nullptr, nullptr);
  auto cursor_destroy = gsl::finally([&]() { mongoc_cursor_destroy(cursor); });

  const bson_t * doc;
  if (mongoc_cursor_next(cursor, &doc))
  {
    char * str = bson_as_json(doc, NULL);
    auto str_destroy = gsl::finally([&]() { bson_free(str); });

    return std::make_pair(0, str);
  }
  else
  {
    return{};
  }
}

int DDSDatabaseConnection::QueryDatabaseInsert(DDSKey key, const char * collection_name, const std::string & document)
{
  bson_oid_t oid;
  memcpy(&oid.bytes[0], &key, sizeof(DDSKey));
  memcpy(&oid.bytes[4], &key, sizeof(DDSKey));

  auto collection = mongoc_database_get_collection(m_Info->m_Database, collection_name);
  auto collection_destroy = gsl::finally([&]() { mongoc_collection_destroy(collection); });

  auto * bson = bson_new();
  auto bson_auto_destroy = gsl::finally([&]() { bson_destroy(bson); });

  bson_error_t parse_error;

  if (bson_init_from_json(bson, document.c_str(), -1, &parse_error) == false)
  {
    return parse_error.code;
  }

  BSON_APPEND_OID(bson, "_id", &oid);

  bson_error_t insert_error;

  if (mongoc_collection_insert(collection, MONGOC_INSERT_NONE, bson, nullptr, &insert_error) == false)
  {
    return insert_error.code;
  }

  return 0;
}

int DDSDatabaseConnection::QueryDatabaseUpsert(DDSKey key, const char * collection_name, const std::string & document)
{
  bson_oid_t oid;
  memcpy(&oid.bytes[0], &key, sizeof(DDSKey));
  memcpy(&oid.bytes[4], &key, sizeof(DDSKey));

  auto collection = mongoc_database_get_collection(m_Info->m_Database, collection_name);
  auto collection_destroy = gsl::finally([&]() { mongoc_collection_destroy(collection); });

  auto * bson_doc = bson_new();
  auto bson_doc_auto_destroy = gsl::finally([&]() { bson_destroy(bson_doc); });

  bson_error_t parse_error;

  if (bson_init_from_json(bson_doc, document.c_str(), -1, &parse_error) == false)
  {
    return parse_error.code;
  }

  auto * bson_query = bson_new();
  auto bson_query_auto_destroy = gsl::finally([&]() { bson_destroy(bson_query); });
  BSON_APPEND_OID(bson_query, "_id", &oid);

  auto flags = MONGOC_UPDATE_UPSERT;

  bson_error_t update_error;
  if (mongoc_collection_update(collection, flags, bson_query, bson_doc, nullptr, &update_error) == false)
  {
    return update_error.code;
  }

  return 0;
}

int DDSDatabaseConnection::QueryDatabaseDelete(DDSKey key, const char * collection_name)
{
  bson_oid_t oid;
  memcpy(&oid.bytes[0], &key, sizeof(DDSKey));
  memcpy(&oid.bytes[4], &key, sizeof(DDSKey));

  auto collection = mongoc_database_get_collection(m_Info->m_Database, collection_name);
  auto collection_destroy = gsl::finally([&]() { mongoc_collection_destroy(collection); });

  auto * bson = bson_new();
  auto bson_auto_destroy = gsl::finally([&]() { bson_destroy(bson); });
  BSON_APPEND_OID(bson, "_id", &oid);

  bson_error_t delete_error;
  if (mongoc_collection_remove(collection, MONGOC_REMOVE_SINGLE_REMOVE, bson, nullptr, &delete_error) == false)
  {
    return delete_error.code;
  }

  return 0;
}
