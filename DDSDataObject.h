#pragma once

#include <StormRefl\StormRefl.h>

#include "DDSNodeInterface.h"

#define DDS_DATA_OBJECT \
  STORM_REFL; \
  STORM_REFL_FUNCS; \
  STORM_REFL_NODEFAULT; \

#define DDS_DATABASE_OBJECT(CollectionName) \
  STORM_REFL; \
  static constexpr const char * Collection() { return #CollectionName; } \

