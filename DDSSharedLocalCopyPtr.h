#pragma once

#include <memory>

#include <StormRefl/StormReflJsonStd.h>

#include <StormData/StormData.h>
#include <StormData/StormDataJsonUtil.h>
#include <StormData/StormDataParent.h>

#include "DDSLog.h"
#include "DDSKey.h"
#include "DDSDataObjectAddress.h"
#include "DDSSharedLocalCopyData.h"

class DDSNodeState;
class DDSSharedLocalCopy;
class DDSSharedLocalCopyPtrBase;

extern thread_local DDSNodeState * g_CurrentNode;
extern thread_local bool g_ExportObjectsAsFull;

void * DDSGetSharedLocalCopyPtr(DDSNodeState * node_state, DDSKey shared_local_copy_key, int data_gen, std::unique_ptr<DDSBaseSharedLocalCopyData>(*CreateFunc)());
void DDSSetSharedLocalCopyVersion(DDSSharedLocalCopyPtrBase & ptr, int data_gen, std::unique_ptr<DDSBaseSharedLocalCopyData>(*CreateFunc)());
void DDSApplySharedLocalCopyChangePacketImpl(DDSSharedLocalCopyPtrBase & ptr, 
  const std::string & change_packet, int data_gen, bool create_new_change_packet, std::unique_ptr<DDSBaseSharedLocalCopyData>(*CreateFunc)());

class DDSSharedLocalCopyPtrBase
{
  STORM_CHANGE_NOTIFIER_INFO;

public:

  DDSSharedLocalCopyPtrBase();

  DDSSharedLocalCopyPtrBase(const DDSSharedLocalCopyPtrBase & rhs) noexcept;
  DDSSharedLocalCopyPtrBase(DDSSharedLocalCopyPtrBase && rhs) noexcept;
  DDSSharedLocalCopyPtrBase(DDSSharedLocalCopyPtrBase && rhs, StormReflectionParentInfo * new_parent);

  DDSSharedLocalCopyPtrBase & operator = (const DDSSharedLocalCopyPtrBase & rhs);
  DDSSharedLocalCopyPtrBase & operator = (DDSSharedLocalCopyPtrBase && rhs) noexcept;

  ~DDSSharedLocalCopyPtrBase();

  void SetRaw(const DDSSharedLocalCopyPtrBase & rhs);
  void UpdateCachedPointer(std::unique_ptr<DDSBaseSharedLocalCopyData>(*CreateFunc)()) const;

  virtual std::string SerializeFull() const = 0;

private:

  void Set();

public:

  DDSNodeState * m_NodeState;
  DDSKey m_SharedLocalCopyKey;
  int m_DataGen;
  void * m_CachedPtr;
};

template <typename T>
struct DDSSharedLocalCopyPtr : public DDSSharedLocalCopyPtrBase
{
  DDSSharedLocalCopyPtr() = default;
  DDSSharedLocalCopyPtr(const DDSSharedLocalCopyPtr<T> & rhs) = default;
  DDSSharedLocalCopyPtr(DDSSharedLocalCopyPtr<T> && rhs) = default;

  DDSSharedLocalCopyPtr(DDSSharedLocalCopyPtr<T> && rhs, StormReflectionParentInfo * new_parent) :
    DDSSharedLocalCopyPtrBase(std::move(rhs), new_parent)
  {

  }

  DDSSharedLocalCopyPtr<T> & operator = (const DDSSharedLocalCopyPtr<T> & rhs) = default;
  DDSSharedLocalCopyPtr<T> & operator = (DDSSharedLocalCopyPtr<T> && rhs) noexcept = default;

  static std::unique_ptr<DDSBaseSharedLocalCopyData> CreateFunc()
  {
    return std::make_unique<DDSSharedLocalCopyData<T>>();
  }

  T * operator ->()
  {
    UpdateCachedPointer(CreateFunc);
    return (T *)m_CachedPtr;
  }

  const T * operator ->() const
  {
    UpdateCachedPointer(CreateFunc);
    return (T *)m_CachedPtr;
  }

  T & operator *()
  {
    UpdateCachedPointer(CreateFunc);
    return *(T *)m_CachedPtr;
  }

  const T & operator *() const
  {
    UpdateCachedPointer(CreateFunc);
    return *(T *)m_CachedPtr;
  }

  virtual std::string SerializeFull() const override
  {
    UpdateCachedPointer(CreateFunc);
    return StormReflEncodeJson(*(T *)m_CachedPtr);
  }
};

template <typename T>
void DDSApplySharedLocalCopyChangePacket(DDSSharedLocalCopyPtr<T> & ptr, const std::string & change_packet, int data_gen, bool create_new_change_packet = true)
{
  DDSApplySharedLocalCopyChangePacketImpl(ptr, change_packet, data_gen, create_new_change_packet, &DDSSharedLocalCopyPtr<T>::CreateFunc);
}

template <typename T>
struct StormReflJson<DDSSharedLocalCopyPtr<T>, void>
{
  static_assert(std::is_class<T>::value, "Shared Local Copies must be objects");

  template <class StringBuilder>
  static void Encode(const DDSSharedLocalCopyPtr<T> & val, StringBuilder & sb)
  {
    std::tuple<DDSKey, int> data =
      std::make_tuple(val.m_SharedLocalCopyKey, val.m_DataGen);

    if (g_ExportObjectsAsFull)
    {
      auto & t = *val;
      StormReflEncodeJsonWithMetaData(t, data, sb);
      return;
    }

    StormReflEncodeJson(data, sb);
  }

  template <class StringBuilder>
  static void EncodePretty(const DDSSharedLocalCopyPtr<T> & val, StringBuilder & sb, int indent)
  {
    std::tuple<DDSKey, int> data =
      std::make_tuple(val.m_SharedLocalCopyKey, val.m_DataGen);

    if (g_ExportObjectsAsFull)
    {
      auto & t = *val;
      StormReflEncodeJsonWithMetaData(t, data, sb);
      return;
    }

    StormReflEncodeJson(data, sb);
  }

  static bool Parse(DDSSharedLocalCopyPtr<T> & t, const char * str, const char *& result)
  {
    StormReflJsonAdvanceWhiteSpace(str);

    std::tuple<DDSKey, int> data;

    if (*str == '[')
    {
      if (StormReflParseJson(data, str, result) == false)
      {
        return false;
      }
    }
    else
    {
      auto meta = StormDataFindJsonStartByPath(".__meta", str);
      if (meta == nullptr)
      {
        return false;
      }

      const char * crap;
      if (StormReflParseJson(data, str, crap) == false)
      {
        return false;
      }

      if (StormReflJsonParseOverObject(str, result) == false)
      {
        return false;
      }
    }

    auto key = std::get<0>(data);
    int data_gen = std::get<1>(data);

    if (t.m_SharedLocalCopyKey != key)
    {
      DDSSetSharedLocalCopyVersion(t, 0, &DDSSharedLocalCopyPtr<T>::CreateFunc);

      t.m_SharedLocalCopyKey = key;
      t.m_DataGen = 0;
    }

    DDSSetSharedLocalCopyVersion(t, data_gen, &DDSSharedLocalCopyPtr<T>::CreateFunc);
    return true;
  }
};

template <typename T>
struct SetParentInfoStruct<DDSSharedLocalCopyPtr<T>> : public SetBasicParentInfo<DDSSharedLocalCopyPtr<T>>
{

};

