#pragma once

#include "DDSKey.h"
#include "DDSResponder.h"
#include "DDSNodeSharedObjectResolver.h"
#include "DDSCoordinatorProtocolMessages.refl.h"

class DDSSharedObjectBase
{
public:
  virtual uint32_t GetObjectClassNameHash() = 0;
  virtual int GetObjectTypeId() = 0;

  virtual const void * GetSharedObjectPointer() = 0;

  virtual void ProcessMessage(DDSCoordinatorProtocolMessageType message_type, const char * message) = 0;

  virtual void AssignRequestedSubscription(const DDSExportedRequestedSubscription & requested_sub) = 0;
  virtual void RemoveRequestedSubscription(DDSKey subscription_id) = 0;
};

class DDSSharedObjectCopyBase
{
public:
  virtual uint32_t GetObjectClassNameHash() = 0;
  virtual int GetObjectTypeId() = 0;

  virtual const void * GetSharedObjectPointer() = 0;

  virtual void ProcessDelta(const DDSCoordinatorSharedObjectDelta & delta) = 0;

  virtual void CreateSubscription(DDSExportedSubscription && sub_data) = 0;
  virtual void DestroySubscription(DDSDataObjectAddress addr, DDSKey subscription_id) = 0;

  virtual void ExportSubscriptions(DDSDataObjectAddress addr, std::vector<std::pair<int, std::vector<DDSExportedSubscription>>> & exported_list) = 0;
  virtual void ImportSubscriptions(DDSDataObjectAddress addr, std::vector<DDSExportedSubscription> && subs, DDSNodeSharedObjectResolver & resolver, int table_gen) = 0;
};

