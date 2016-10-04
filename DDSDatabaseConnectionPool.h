#pragma once

#include "DDSKey.h"

#include <functional>

struct DDSDatabaseSettings
{
  int NumThreads = 4;
  const char * DatabaseName = "dds";
};

void DDSInitDatabaseConnections(DDSDatabaseSettings & settings);
void DDSShutdownDatabaseConnections();

void DDSQueryDatabaseByKey(DDSKey key, const char * collection, std::function<void(const char *, int)> && result_callback);
void DDSQueryDatabaseCustom(const char * query, const char * collection, std::function<void(const char *, int)> && result_callback);
void DDSQueryDatabaseInsert(DDSKey key, const char * collection, const char * document, std::function<void(const char *, int)> && result_callback);
void DDSQueryDatabaseUpsert(DDSKey key, const char * collection, const char * document, std::function<void(const char *, int)> && result_callback);
void DDSQueryDatabaseDelete(DDSKey key, const char * collection, std::function<void(const char *, int)> && result_callback);

void DDSDatabaseTriggerCallbacks();
