
#include "DDSSharedLocalCopyDatabase.h"
#include "DDSSharedLocalCopy.h"
#include "DDSNodeState.h"

DDSSharedLocalCopyDatabase::DDSSharedLocalCopyDatabase(DDSNodeState & node_state) :
  m_NodeState(node_state)
{

}

DDSSharedLocalCopyDatabase::~DDSSharedLocalCopyDatabase()
{

}

DDSKey DDSSharedLocalCopyDatabase::CreateNewSharedLocalCopySubscription(
  DDSDataObjectAddress addr, const char * path, const std::string & return_args,
  DDSDataObjectAddress return_addr, int return_method, int error_method, bool data_sub,
  DDSKey subscription_id, std::unique_ptr<DDSBaseSharedLocalCopyData>(*CreateFunc)())
{ 
  auto shared_local_copy_key = GetSharedLocalCopyKey(addr, crc64(path), data_sub);
  auto itr = m_Database.find(shared_local_copy_key);

  if (itr == m_Database.end())
  {
    CopyInfo new_copy;
    new_copy.m_Data = std::make_unique<DDSSharedLocalCopy>(m_NodeState, addr, path, shared_local_copy_key, CreateFunc(), 0, data_sub);
    
    auto result = m_Database.emplace(std::make_pair(shared_local_copy_key, std::move(new_copy)));
    itr = result.first;
  }

  if (itr->second.m_Data == nullptr)
  {
    SpawnImportedSubscription(itr->second, shared_local_copy_key, CreateFunc);
  }

  itr->second.m_Data->CreateSubscription(subscription_id, return_addr, return_method, error_method, return_args, 0, true);
  return shared_local_copy_key;
}

void DDSSharedLocalCopyDatabase::CreateExistingSharedLocalCopySubscription(DDSExportedAggregateRequestedSubscription & sub_info, DDSDataObjectAddress return_addr)
{
  auto addr = DDSDataObjectAddress{ sub_info.m_ObjectType, sub_info.m_Key };

  auto shared_local_copy_key = GetSharedLocalCopyKey(addr, crc64(sub_info.m_Path), sub_info.m_DataSub);
  auto itr = m_Database.find(shared_local_copy_key);

  if (itr == m_Database.end())
  {
    DDSLog::LogError("Importing existing subscription could not find sub data");
  }
  else
  {
    if (itr->second.m_Data)
    {
      itr->second.m_Data->CreateSubscription(sub_info.m_SubscriptionId, 
        return_addr, sub_info.m_ReturnMethod, sub_info.m_ErrorMethod, sub_info.m_ReturnArgs, sub_info.m_DataGen, sub_info.m_DataValid);
    }
    else
    {
      itr->second.m_Import->m_ImportSubs.emplace_back(std::move(sub_info));
    }
  }
}

void DDSSharedLocalCopyDatabase::DestroySharedLocalCopySubscription(DDSKey shared_local_copy_key, DDSKey subscription_id)
{
  auto itr = m_Database.find(shared_local_copy_key);
  if (itr == m_Database.end())
  {
    return;
  }

  itr->second.m_Data->DestroySubscription(subscription_id);
  if (itr->second.m_Data->HasSubscriptions() == false)
  {
    itr->second.m_Data->TerminateLocalCopy();
    m_Database.erase(itr);
  }
}


DDSSharedLocalCopy * DDSSharedLocalCopyDatabase::GetSharedLocalCopy(DDSKey shared_local_copy_key)
{
  auto itr = m_Database.find(shared_local_copy_key);
  if (itr == m_Database.end())
  {
    return nullptr;
  }

  if (itr->second.m_Data == nullptr)
  {
    DDSLog::LogError("Could not get shared copy for modify");
    return nullptr;
  }

  return itr->second.m_Data.get();
}

DDSSharedLocalCopy * DDSSharedLocalCopyDatabase::GetSharedLocalCopy(DDSKey shared_local_copy_key, std::unique_ptr<DDSBaseSharedLocalCopyData>(*CreateFunc)())
{
  auto itr = m_Database.find(shared_local_copy_key);
  if (itr == m_Database.end())
  {
    return nullptr;
  }

  if (itr->second.m_Data.get() == nullptr)
  {
    SpawnImportedSubscription(itr->second, shared_local_copy_key, CreateFunc);
  }

  return itr->second.m_Data.get();
}

void DDSSharedLocalCopyDatabase::Export(DDSSharedLocalCopyDatabaseDump & db_dump)
{
  for (auto & elem : m_Database)
  {
    DDSSharedLocalCopyDatabaseElem elem_dump;

    if (elem.second.m_Data)
    {
      elem.second.m_Data->Export(elem_dump);
    }
    else
    {
      elem_dump = elem.second.m_Import->m_ImportData;
    }

    db_dump.m_Copies.emplace(elem.first, std::move(elem_dump));
  }
}

void DDSSharedLocalCopyDatabase::GetSubscriptionInfo(DDSExportedAggregateRequestedSubscription & sub_info)
{
  auto itr = m_Database.find(sub_info.m_SharedLocalCopyKey);
  if (itr == m_Database.end())
  {
    DDSLog::LogError("Exporting aggregate sub for invalid SLC");
    return;
  }

  if (itr->second.m_Data)
  {
    sub_info.m_DataGen = itr->second.m_Data->GetLatestDataGeneration();
    sub_info.m_DataValid = itr->second.m_Data->IsDataValid();
  }
  else
  {
    sub_info.m_DataGen = itr->second.m_Import->m_ImportData.m_DataGen;
    sub_info.m_DataValid = itr->second.m_Import->m_ImportData.m_DataValid;
  }
}

void DDSSharedLocalCopyDatabase::Import(DDSSharedLocalCopyDatabaseDump & db_dump)
{
  for (auto & elem : db_dump.m_Copies)
  {
    auto itr = m_Database.find(elem.first);
    if (itr != m_Database.end())
    {
      continue;
    }

    auto import_info = std::make_unique<ImportInfo>();
    import_info->m_ImportData = std::move(elem.second);
    
    m_Database.emplace(std::make_pair(elem.first, CopyInfo{ {}, std::move(import_info) }));
  }
}

void DDSSharedLocalCopyDatabase::HandleAllClear()
{
  std::vector<std::unordered_map<DDSKey, CopyInfo>::iterator> dead_itrs;
  for (auto itr = m_Database.begin(), end = m_Database.end(); itr != end; ++itr)
  {
    if (itr->second.m_Data == nullptr)
    {
      dead_itrs.emplace_back(itr);
    }
  }

  for (auto & itr : dead_itrs)
  {
    m_Database.erase(itr);
  }
}

std::string DDSSharedLocalCopyDatabase::GetMemoryReport()
{
  std::string report = "Shared Local Copy Database\n";
  report += "  Objects: " + std::to_string(m_Database.size()) + "\n";

  for (auto & elem : m_Database)
  {
    if (elem.second.m_Data)
    {
      report += "  " + std::to_string(elem.first) + ": " + elem.second.m_Data->MemoryReport() + "\n";
    }
  }

  return report;
}

DDSKey DDSSharedLocalCopyDatabase::GetSharedLocalCopyKey(DDSDataObjectAddress addr, DDSKey path_hash, bool is_data_sub)
{
  return addr.m_ObjectKey + crc64integer(addr.m_ObjectType) | path_hash + is_data_sub;
}

void DDSSharedLocalCopyDatabase::SpawnImportedSubscription(CopyInfo & copy, DDSKey shared_local_copy_key, std::unique_ptr<DDSBaseSharedLocalCopyData>(*CreateFunc)())
{
  auto & import = copy.m_Import->m_ImportData;

  auto addr = DDSDataObjectAddress{ import.m_ObjectType, import.m_Key };
  copy.m_Data = std::make_unique<DDSSharedLocalCopy>(m_NodeState, addr, import.m_Path, shared_local_copy_key, CreateFunc(), import.m_DataGen, import.m_DataSub);
  copy.m_Data->CreateDataVersion(import.m_DataGen, std::move(import.m_Data));

  for (auto & sub_info : copy.m_Import->m_ImportSubs)
  {
    auto return_addr = DDSDataObjectAddress{ sub_info.m_ReturnObjectType, sub_info.m_ReturnKey };
    copy.m_Data->CreateSubscription(sub_info.m_SubscriptionId, return_addr,
      sub_info.m_ReturnMethod, sub_info.m_ErrorMethod, sub_info.m_ReturnArgs, sub_info.m_DataGen, sub_info.m_DataValid);
  }
  copy.m_Import.release();

}