#pragma once

#include <StormRefl\StormRefl.h>
#include <StormData\StormDataNumber.h>
#include <StormData\StormDataEnum.h>
#include <StormData\StormDataString.h>
#include <StormData\StormDataList.h>
#include <StormData\StormDataMap.h>
#include <StormData\StormDataJson.h>
#include <StormData\StormData.h>

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

#define DDS_SHARED_OBJECT \
  STORM_REFL; \
  STORM_REFL_FUNCS; \
  STORM_REFL_NODEFAULT; \
  STORM_CHANGE_NOTIFIER_INFO; \

using RKey = RNumber<DDSKey>;

