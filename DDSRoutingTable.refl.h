#pragma once

#include <StormRefl/StormRefl.h>

#include <vector>

#include "DDSNodeId.h"
#include "DDSKey.h"

struct DDSNodeElement
{
  STORM_REFL;

  DDSNodeId m_Id;
  DDSNodeAddr m_Addr;
  DDSNodePort m_Port;
  DDSKey m_CentralKey;
};

struct DDSRoutingTable
{
  STORM_REFL;
  std::vector<DDSNodeElement> m_Table;
  int m_TableGeneration = 0;
};

