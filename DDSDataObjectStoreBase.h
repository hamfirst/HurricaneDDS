#pragma once

#include <vector>

#include "DDSKey.h"
#include "DDSResponder.h"
#include "DDSDataObject.h"
#include "DDSServerToServerMessages.refl.h"

class DDSDataObjectStoreBase
{
public:
  ~DDSDataObjectStoreBase() {}

  virtual uint32_t GetDataClassNameHash() const = 0;
  virtual uint32_t GetDatabaseClassNameHash() const = 0;
  virtual int GetDataTypeId() const = 0;
  virtual DDSKey GetUnusedKeyInRange(DDSKeyRange range) = 0;

  virtual DDSDataObjectPriority GetPriority() = 0;

  virtual void SpawnNewNonDatabaseBackedType(DDSKey key) = 0;
  virtual bool Destroy(DDSKey key) = 0;
  virtual void * GetDataObjectForKey(DDSKey key) = 0;

  virtual void HandleMessage(DDSKey key, DDSServerToServerMessageType message_type, const char * msg) = 0;
  virtual void HandleLoadResult(DDSKey key, const char * data, int ec) = 0;
  virtual void FinalizeObjectLoad(DDSKey key) = 0;

  virtual void BeginObjectModification(DDSKey key) = 0;
  virtual void EndObjectModification() = 0;
  virtual void LockObject(DDSKey key) = 0;

  virtual void AssignRequestedSubscription(DDSKey key, const DDSExportedRequestedSubscription & requested_sub) = 0;
  virtual void RemoveRequestedSubscription(DDSKey key, DDSKey subscription_id) = 0;

  virtual void AssignRequestedAggregateSubscription(DDSKey key, const DDSExportedAggregateRequestedSubscription & requested_sub) = 0;
  virtual void RemoveRequestedAggregateSubscription(DDSKey key, DDSKey shared_local_copy_key, DDSKey subscription_id) = 0;

  virtual void HandleAllClear(int routing_table_gen) = 0;

  virtual void PrepareObjectsForMove(DDSKeyRange requested_range) = 0;
  virtual bool ExportObjectsInRange(DDSKeyRange requested_range, DDSKeyRange & output_range, DDSKeyRange & remainder_range, int max_objects, std::vector<DDSExportedObject> & output) = 0;
  virtual void ProcessExportedObjects(std::vector<DDSExportedObject> & object_list, int routing_table_gen) = 0;

  virtual std::string MemoryReport() = 0;
};

