
#include "DDSSharedLocalCopyData.h"


void * DDSBaseSharedLocalCopyData::GetVersion(int version)
{
  auto itr = m_Versions.find(version);
  if (itr == m_Versions.end())
  {
    DDSLog::LogError("Requesting invalid version of shared local copy");
  }

  InstantiateVersion(itr->second, version);
  return itr->second.m_Obj;
}

void DDSBaseSharedLocalCopyData::ApplyChangePacket(const ReflectionChangeNotification & change, int data_gen)
{
  m_Versions.emplace(std::make_pair(data_gen, Version{ nullptr, 0, change }));
}

void DDSBaseSharedLocalCopyData::AddRef(int version)
{
  auto itr = m_Versions.find(version);
  if (itr == m_Versions.end())
  {
    DDSLog::LogError("Addref invalid version of shared local copy");
  }

  itr->second.m_RefCount++;
}

void DDSBaseSharedLocalCopyData::DecRef(int version)
{
  auto itr = m_Versions.find(version);
  if (itr == m_Versions.end())
  {
    DDSLog::LogError("Decref invalid version of shared local copy");
  }

  itr->second.m_RefCount--;
  CheckOldestVersion();
}

std::string DDSBaseSharedLocalCopyData::MemoryReport()
{
  return "Versions: " + std::to_string(m_Versions.size());
}

void DDSBaseSharedLocalCopyData::InstantiateVersion(Version & version, int data_gen)
{
  if (version.m_Obj != nullptr)
  {
    return;
  }

  void * prev_obj = nullptr;
  if (version.m_Change.m_Type != ReflectionNotifyChangeType::kSet || version.m_Change.m_Path.size() != 0)
  {
    int prev_gen = data_gen - 1;
    auto prev_version = m_Versions.find(prev_gen);
    if (prev_version == m_Versions.end())
    {
      DDSLog::LogError("Got invalid change packet (no prev version)");
      return;
    }

    InstantiateVersion(prev_version->second, prev_gen);

    prev_obj = prev_version->second.m_Obj;
    if (prev_obj == nullptr)
    {
      DDSLog::LogError("Got invalid change packet (no prev version obj)");
      return;
    }
  }

  version.m_Obj = ApplyChangePacketInternal(version.m_Change, prev_obj);
}

void DDSBaseSharedLocalCopyData::CheckOldestVersion()
{
  while (true)
  {
    auto itr = m_Versions.begin();
    if (itr == m_Versions.end() || itr->second.m_RefCount > 0)
    {
      break;
    }

    auto next_itr = itr;
    next_itr++;

    if (next_itr != m_Versions.end() && next_itr->second.m_Obj == nullptr)
    {
      InstantiateVersion(next_itr->second, next_itr->first);
    }

    if (itr->second.m_Obj != nullptr)
    {
      FreeObject(itr->second.m_Obj);
    }

    m_Versions.erase(itr);
  }

}