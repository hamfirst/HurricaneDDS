#pragma once

#include <StormRefl\StormRefl.h>

#include "DDSKey.h"

class DDSNodeState;

class DDSResponderData
{
public:
  STORM_REFL;

  DDSKey m_Key;
  int m_ObjectType;

  int m_ReturnMethodId;
};
