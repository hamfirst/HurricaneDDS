#pragma once

#include <StormRefl/StormRefl.h>
#include <StormData/StormDataTypes.h>
#include <StormData/StormDataJson.h>

#include "DDSKey.h"
#include "DDSNodeInterface.h"
#include "DDSSharedObjectInterface.h"

enum class DDSDataObjectPriority
{
  kHigh,
  kMedium,
  kLow,
  kCount
};

#define DDS_DATA_OBJECT(Priority) \
  STORM_REFL; \
  STORM_REFL_FUNCS; \
  STORM_REFL_NODEFAULT; \
  STORM_CHANGE_NOTIFIER_INFO; \
  static constexpr DDSDataObjectPriority GetPriority() { return Priority; }

#define DDS_DATABASE_OBJECT(CollectionName) \
  STORM_REFL; \
  STORM_CHANGE_NOTIFIER_INFO; \
  static constexpr const char * Collection() { return #CollectionName; } \

#define DDS_TEMPORARY_OBJECT(AllowImplicitCreate, Priority) \
  STORM_REFL; \
  STORM_REFL_FUNCS; \
  STORM_REFL_NODEFAULT; \
  STORM_CHANGE_NOTIFIER_INFO; \
  static constexpr bool AllowsImplicitCreate() { return AllowImplicitCreate; } \
  static constexpr DDSDataObjectPriority GetPriority() { return Priority; }

#define DDS_SHARED_OBJECT \
  STORM_REFL; \
  STORM_REFL_FUNCS; \
  STORM_REFL_NODEFAULT; \
  STORM_CHANGE_NOTIFIER_INFO; \

using RKey = RNumber<DDSKey>;

