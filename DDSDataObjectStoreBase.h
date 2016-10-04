#pragma once

#include <vector>

#include "DDSKey.h"
#include "DDSResponder.h"
#include "DDSServerToServerMessages.refl.h"

class DDSDataObjectStoreBase
{
public:
  ~DDSDataObjectStoreBase() {}

  virtual uint32_t GetDataClassNameHash() = 0;

  virtual void HandleMessage(DDSKey key, DDSResponderData responder, const char * msg) = 0;
  virtual void HandleQuery(DDSKey key, DDSResponderData responder, const char * msg) = 0;

  virtual bool ExportObjectsInRange(DDSKeyRange requested_range, DDSKeyRange & output_range, DDSKeyRange & remainder_range, int max_objects, std::vector<DDSExportedObject> & output) = 0;
  virtual void ProcessExportedObjects(const std::vector<DDSExportedObject> & object_list) = 0;
};

