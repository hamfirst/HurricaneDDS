#pragma once

#include <StormRefl/StormRefl.h>

#include "DDSKey.h"

#include <string>

class DDSNodeState;

class DDSResponderData
{
public:
  STORM_REFL;

  DDSKey m_Key;
  int m_ObjectType;

  int m_ReturnMethodId;
  int m_ErrorMethodId;
  std::string m_ReturnArg;
};

