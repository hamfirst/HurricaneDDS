#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>
#include <StormData/StormDataJson.h>

#include "DDSKey.h"
#include "DDSNodeInterface.h"
#include "DDSSharedObjectInterface.h"

#define DDS_DATA_OBJECT \
  STORM_REFL; \
  STORM_REFL_FUNCS; \
  STORM_REFL_NODEFAULT; \
  STORM_CHANGE_NOTIFIER_INFO; \

#define DDS_DATABASE_OBJECT(CollectionName) \
  STORM_REFL; \
  STORM_CHANGE_NOTIFIER_INFO; \
  static constexpr const char * Collection() { return #CollectionName; } \

#define DDS_TEMPORARY_OBJECT(AllowImplicitCreate) \
  STORM_REFL; \
  STORM_REFL_FUNCS; \
  STORM_REFL_NODEFAULT; \
  STORM_CHANGE_NOTIFIER_INFO; \
  static constexpr bool AllowsImplicitCreate() { return AllowImplicitCreate; } \

#define DDS_SHARED_OBJECT \
  STORM_REFL; \
  STORM_REFL_FUNCS; \
  STORM_REFL_NODEFAULT; \
  STORM_CHANGE_NOTIFIER_INFO; \

using RKey = RNumber<DDSKey>;

