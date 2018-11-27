
#include "DDSSharedLocalCopyPtr.h"
#include "DDSSharedLocalCopy.h"
#include "DDSNodeState.h"

thread_local DDSNodeState * g_CurrentNode = nullptr;
thread_local bool g_ExportObjectsAsFull = true;

void * DDSGetSharedLocalCopyPtr(DDSNodeState * node_state, DDSKey shared_local_copy_key, int data_gen, std::unique_ptr<DDSBaseSharedLocalCopyData>(*CreateFunc)())
{
  return node_state->m_SharedLocalCopyDatabase.GetSharedLocalCopy(shared_local_copy_key, CreateFunc)->GetVersion(data_gen);
}

void DDSSetSharedLocalCopyVersion(DDSSharedLocalCopyPtrBase & ptr, int data_gen, std::unique_ptr<DDSBaseSharedLocalCopyData>(*CreateFunc)())
{
  if (ptr.m_SharedLocalCopyKey == 0)
  {
    return;
  }

  ptr.m_CachedPtr = nullptr;

  auto slc = ptr.m_NodeState->m_SharedLocalCopyDatabase.GetSharedLocalCopy(ptr.m_SharedLocalCopyKey);
  if (slc == nullptr)
  {
    return;
  }

  if (data_gen != 0)
  {
    slc->AddRef(data_gen);
  }

  if (ptr.m_DataGen != 0)
  {
    slc->DecRef(ptr.m_DataGen);
  }

  ptr.m_DataGen = data_gen;
}

void DDSApplySharedLocalCopyChangePacketImpl(DDSSharedLocalCopyPtrBase & ptr, 
  const std::string & change_packet, int data_gen, bool create_new_change_packet, std::unique_ptr<DDSBaseSharedLocalCopyData>(*CreateFunc)())
{
  DDSSetSharedLocalCopyVersion(ptr, data_gen, CreateFunc);

  if (create_new_change_packet && (ptr.m_ReflectionInfo.m_Flags & (int)StormDataParentInfoFlags::kParentHasCallback) != 0)
  {
    ReflectionChangeNotification change_info;
    StormDataParseChangePacket(change_info, change_packet.data());

    FinishChangeNotification(&ptr.m_ReflectionInfo, change_info);
  }
}


DDSSharedLocalCopyPtrBase::DDSSharedLocalCopyPtrBase()
{
  m_NodeState = g_CurrentNode;
  m_SharedLocalCopyKey = 0;
  m_DataGen = 0;
  m_CachedPtr = nullptr;
}

DDSSharedLocalCopyPtrBase::DDSSharedLocalCopyPtrBase(const DDSSharedLocalCopyPtrBase & rhs) noexcept
{
  m_NodeState = rhs.m_NodeState;
  m_SharedLocalCopyKey = rhs.m_SharedLocalCopyKey;
  m_DataGen = 0;

  DDSSetSharedLocalCopyVersion(*this, rhs.m_DataGen, nullptr);
}

DDSSharedLocalCopyPtrBase::DDSSharedLocalCopyPtrBase(DDSSharedLocalCopyPtrBase && rhs) noexcept
{
  m_ReflectionInfo = rhs.m_ReflectionInfo;
  m_NodeState = rhs.m_NodeState;
  m_SharedLocalCopyKey = rhs.m_SharedLocalCopyKey;
  m_DataGen = rhs.m_DataGen;
  m_CachedPtr = rhs.m_CachedPtr;

  rhs.m_SharedLocalCopyKey = 0;
  rhs.m_DataGen = 0;
  rhs.m_ReflectionInfo = {};
  rhs.m_CachedPtr = nullptr;
}

DDSSharedLocalCopyPtrBase::DDSSharedLocalCopyPtrBase(DDSSharedLocalCopyPtrBase && rhs, StormReflectionParentInfo * new_parent)
{
  m_ReflectionInfo = rhs.m_ReflectionInfo;
  m_ReflectionInfo.m_ParentInfo = new_parent;
  m_NodeState = rhs.m_NodeState;
  m_SharedLocalCopyKey = rhs.m_SharedLocalCopyKey;
  m_DataGen = rhs.m_DataGen;
  m_CachedPtr = rhs.m_CachedPtr;

  rhs.m_SharedLocalCopyKey = 0;
  rhs.m_DataGen = 0;
  rhs.m_ReflectionInfo = {};
  rhs.m_CachedPtr = nullptr;
}

DDSSharedLocalCopyPtrBase & DDSSharedLocalCopyPtrBase::operator = (const DDSSharedLocalCopyPtrBase & rhs)
{
  if (m_NodeState != rhs.m_NodeState || m_SharedLocalCopyKey != rhs.m_SharedLocalCopyKey)
  {
    DDSLog::LogError("Invalid shared local copy assign");
    return *this;
  }

  if (m_DataGen != rhs.m_DataGen)
  {
    DDSSetSharedLocalCopyVersion(*this, rhs.m_DataGen, nullptr);
    Set();
  }

  return *this;
}

DDSSharedLocalCopyPtrBase & DDSSharedLocalCopyPtrBase::operator = (DDSSharedLocalCopyPtrBase && rhs) noexcept
{
  if (m_NodeState != rhs.m_NodeState || m_SharedLocalCopyKey != rhs.m_SharedLocalCopyKey)
  {
    DDSLog::LogError("Invalid shared local copy assign");
    return *this;
  }

  if (m_DataGen != rhs.m_DataGen)
  {
    DDSSetSharedLocalCopyVersion(*this, rhs.m_DataGen, nullptr);
    Set();
  }

  return *this;
}

DDSSharedLocalCopyPtrBase::~DDSSharedLocalCopyPtrBase()
{
  DDSSetSharedLocalCopyVersion(*this, 0, nullptr);
}

void DDSSharedLocalCopyPtrBase::SetRaw(const DDSSharedLocalCopyPtrBase & rhs)
{
  if (m_NodeState != rhs.m_NodeState || m_SharedLocalCopyKey != rhs.m_SharedLocalCopyKey)
  {
    DDSLog::LogError("Invalid shared local copy assign");
    return;
  }

  if (m_DataGen != rhs.m_DataGen)
  {
    DDSSetSharedLocalCopyVersion(*this, rhs.m_DataGen, nullptr);
  }
}

void DDSSharedLocalCopyPtrBase::UpdateCachedPointer(std::unique_ptr<DDSBaseSharedLocalCopyData>(*CreateFunc)()) const // technically not const
{
  if (m_CachedPtr == nullptr)
  {
    DDSSharedLocalCopyPtrBase * p_this = (DDSSharedLocalCopyPtrBase *)this;
    p_this->m_CachedPtr = DDSGetSharedLocalCopyPtr(m_NodeState, m_SharedLocalCopyKey, m_DataGen, CreateFunc);
  }
}

void DDSSharedLocalCopyPtrBase::Set()
{
  if (DoNotifyCallback(m_ReflectionInfo) == false)
  {
    return;
  }

  ReflectionNotifySetObject(m_ReflectionInfo, SerializeFull());
}
