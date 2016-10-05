#pragma once

#include <vector>

#include "DDSKey.h"
#include "DDSResponder.h"
#include "DDSServerToServerMessages.refl.h"

class DDSDataObjectStoreBase
{
public:
  ~DDSDataObjectStoreBase() {}

  virtual uint32_t GetDataClassNameHash() const = 0;
  virtual uint32_t GetDatabaseClassNameHash() const = 0;
  virtual DDSKey GetUnusedKeyInRange(DDSKeyRange range) = 0;

  virtual void SpawnNewNonDatabaseBackedType(DDSKey key) = 0;

  virtual void HandleMessage(DDSKey key, DDSServerToServerMessageType message_type, const char * msg) = 0;
  virtual void HandleQuery(DDSKey key, DDSServerToServerMessageType message_type, const char * msg) = 0;

  virtual bool ExportObjectsInRange(DDSKeyRange requested_range, DDSKeyRange & output_range, DDSKeyRange & remainder_range, int max_objects, std::vector<DDSExportedObject> & output) = 0;
  virtual void ProcessExportedObjects(const std::vector<DDSExportedObject> & object_list) = 0;
};

