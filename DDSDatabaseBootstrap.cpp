
#include <gsl/gsl_util.h>


#include <mongoc/mongoc.h>
#include <libbson/bson.h>

#include <StormRefl/StormReflJsonStd.h>
#include <StormData/StormDataJsonUtil.h>

#include "DDSDatabaseBootstrap.h"
#include "DDSDatabaseTypes.h"

void DDSDatabaseBoostrapFullInternal(const std::vector<DDSDatabaseBoostrapCollectionInfo> & info, const DDSDatabaseSettings & settings)
{
  std::string database_url = std::string("mongodb://") + settings.DatabaseHostName + ":" + std::to_string(settings.DatabasePort);

  auto client = mongoc_client_new(database_url.data());
  auto destroy_client = gsl::finally([&]() { mongoc_client_destroy(client); });

  auto database = mongoc_client_get_database(client, settings.DatabaseName);
  auto destroy_database = gsl::finally([&]() { mongoc_database_destroy(database); });

  bson_error_t err;
  mongoc_database_drop(database, &err);

  for (auto & collection_info : info)
  {
    auto collection = mongoc_database_create_collection(database, collection_info.m_CollectionName.c_str(), nullptr, &err);
    auto collection_destroy = gsl::finally([&]() { mongoc_collection_destroy(collection); });

    for (auto & index : collection_info.m_Indices)
    {
      bson_t key;
      std::string index_str = "{" + index + ":1}";
      bson_init_from_json(&key, index_str.c_str(), index_str.length(), &err);
      auto key_auto_destroy = gsl::finally([&]() { bson_destroy(&key); });

      mongoc_index_opt_t options;
      mongoc_index_opt_init(&options);
      options.unique = true;

      mongoc_collection_create_index(collection, &key, &options, &err);
    }
  }
}

void DDSDatabaseBoostrapIndicesInternal(const std::vector<DDSDatabaseBoostrapCollectionInfo> & info, const DDSDatabaseSettings & settings)
{
  std::string database_url = std::string("mongodb://") + settings.DatabaseHostName + ":" + std::to_string(settings.DatabasePort);

  auto client = mongoc_client_new(database_url.data());
  auto destroy_client = gsl::finally([&]() { mongoc_client_destroy(client); });

  auto database = mongoc_client_get_database(client, settings.DatabaseName);
  auto destroy_database = gsl::finally([&]() { mongoc_database_destroy(database); });

  bson_error_t err;

  for (auto & collection_info : info)
  {
    auto collection = mongoc_database_get_collection(database, collection_info.m_CollectionName.c_str());
    auto collection_destroy = gsl::finally([&]() { mongoc_collection_destroy(collection); });

    auto cursor = mongoc_collection_find_indexes(collection, &err);
    auto cursor_destroy = gsl::finally([&]() { mongoc_cursor_destroy(cursor); });

    const bson_t * doc;
    while (mongoc_cursor_next(cursor, &doc))
    {
      char * str = bson_as_json(doc, NULL);
      auto str_destroy = gsl::finally([&]() { bson_free(str); });

      const char * name_start = StormDataFindJsonStartByPath(".name", str);
      if (name_start)
      {
        std::string name;
        if (StormReflParseJson(name, name_start))
        {
          if (name != "_id_")
          {
            mongoc_collection_drop_index(collection, name.c_str(), &err);
          }
        }
      }
    }

    for (auto & index : collection_info.m_Indices)
    {
      bson_t key;
      std::string index_str = "{" + index + ":1}";
      bson_init_from_json(&key, index_str.c_str(), index_str.length(), &err);
      auto key_auto_destroy = gsl::finally([&]() { bson_destroy(&key); });

      mongoc_index_opt_t options;
      mongoc_index_opt_init(&options);
      options.unique = true;

      mongoc_collection_create_index(collection, &key, &options, &err);
    }
  }
}
