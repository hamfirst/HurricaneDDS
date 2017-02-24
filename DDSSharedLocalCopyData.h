#pragma once

#include <map>

#include <StormData/StormDataChangeNotifier.h>
#include <StormData/StormDataChangePacket.h>

#include "DDSKey.h"
#include "DDSLog.h"

class DDSBaseSharedLocalCopyData
{
public:

  void * GetVersion(int version);
  void ApplyChangePacket(const ReflectionChangeNotification & change, int data_gen);
  virtual void AppendFullJsonData(int version, std::string & str) = 0;

  void AddRef(int version);
  void DecRef(int version);


protected:

  friend class DDSSharedLocalCopy;

  struct Version
  {
    void * m_Obj;
    int m_RefCount;

    ReflectionChangeNotification m_Change;
  };

  virtual void * ApplyChangePacketInternal(const ReflectionChangeNotification & change, void * prev_version) = 0;
  virtual void ParseFull(int data_gen, const char * data) = 0;
  virtual void FreeObject(void * obj) = 0;

  void InstantiateVersion(Version & version, int data_gen);
  void CheckOldestVersion();

protected:

  std::map<int, Version> m_Versions;
};


template <typename T>
class DDSSharedLocalCopyData : public DDSBaseSharedLocalCopyData
{
public:

  virtual void AppendFullJsonData(int version, std::string & str) override
  {
    auto itr = m_Versions.find(version);
    if (itr == m_Versions.end())
    {
      DDSLog::LogError("Referencing invalid version of shared local copy");
      return;
    }

    InstantiateVersion(itr->second, version);

    T * t = (T *)itr->second.m_Obj;
    StormReflEncodeJson(*t, str);
  }

protected:

  virtual void * ApplyChangePacketInternal(const ReflectionChangeNotification & change, void * prev_version) override
  {
    T * new_t = new T();

    if (prev_version)
    {
      T * t = (T *)prev_version;
      StormReflCopy(*new_t, *t);
    }

    StormDataApplyChangePacket(*new_t, change);
    return new_t;
  }

  virtual void ParseFull(int data_gen, const char * data) override
  {
    if (m_Versions.find(data_gen) != m_Versions.end())
    {
      return;
    }

    T * t = new T();
    StormReflParseJson(*t, data);

    m_Versions.emplace(std::make_pair(data_gen, Version{ t, 0 }));
  }

  virtual void FreeObject(void * obj) override
  {
    delete (T *)obj;
  }
};



