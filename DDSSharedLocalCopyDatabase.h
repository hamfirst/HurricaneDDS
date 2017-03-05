#pragma once

#include <unordered_map>
#include <memory>

#include "DDSKey.h"
#include "DDSDataObjectAddress.h"
#include "DDSSharedMessages.refl.h"
#include "DDSServerToServerMessages.refl.h"

class DDSNodeState;
class DDSSharedLocalCopy;
class DDSBaseSharedLocalCopyData;

struct DDSSharedLocalCopyDatabaseDump;

class DDSSharedLocalCopyDatabase
{
public:
  DDSSharedLocalCopyDatabase(DDSNodeState & node_state);
  ~DDSSharedLocalCopyDatabase();

  DDSKey CreateNewSharedLocalCopySubscription(DDSDataObjectAddress addr, const char * path, const std::string & return_args,
    DDSDataObjectAddress return_addr, int return_method, int error_method, bool data_sub,
    DDSKey subscription_id, std::unique_ptr<DDSBaseSharedLocalCopyData>(*CreateFunc)());

  void CreateExistingSharedLocalCopySubscription(DDSExportedAggregateRequestedSubscription & sub_info, DDSDataObjectAddress return_addr);

  void DestroySharedLocalCopySubscription(DDSKey shared_local_copy_key, DDSKey subscription_id);

  DDSSharedLocalCopy * GetSharedLocalCopy(DDSKey shared_local_copy_key);
  DDSSharedLocalCopy * GetSharedLocalCopy(DDSKey shared_local_copy_key, std::unique_ptr<DDSBaseSharedLocalCopyData>(*CreateFunc)());

  void Export(DDSSharedLocalCopyDatabaseDump & db_dump);
  void Import(DDSSharedLocalCopyDatabaseDump & db_dump);

  void GetSubscriptionInfo(DDSExportedAggregateRequestedSubscription & sub_info);

  void HandleAllClear();
  std::string GetMemoryReport();

  static DDSKey GetSharedLocalCopyKey(DDSDataObjectAddress addr, DDSKey path_hash, bool is_data_sub);

private:

  struct ImportInfo
  {
    DDSSharedLocalCopyDatabaseElem m_ImportData;
    std::vector<DDSExportedAggregateRequestedSubscription> m_ImportSubs;
  };

  struct CopyInfo
  {
    std::unique_ptr<DDSSharedLocalCopy> m_Data;
    std::unique_ptr<ImportInfo> m_Import;
  };

  void SpawnImportedSubscription(CopyInfo & copy, DDSKey shared_local_copy_key, std::unique_ptr<DDSBaseSharedLocalCopyData>(*CreateFunc)());

private:

  DDSNodeState & m_NodeState;
  std::unordered_map<DDSKey, CopyInfo> m_Database;
};
