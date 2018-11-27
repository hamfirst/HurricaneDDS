#pragma once

#include <StormRefl/StormRefl.h>

#include <vector>

#include "DDSNodeId.h"
#include "DDSKey.h"

struct DDSNodeElementBase
{
  STORM_REFL;

  DDSNodeId m_Id;
  DDSNodeAddr m_Addr;
  DDSNodePort m_Port;

  std::vector<DDSNodePort> m_EndpointPorts;
  std::vector<DDSNodePort> m_WebsitePorts;
};

struct DDSNodeElement : public DDSNodeElementBase
{
  STORM_REFL;
  DDSKey m_CentralKey;
};

struct DDSRoutingTable
{
  STORM_REFL;
  std::vector<DDSNodeElement> m_Table;
  std::vector<DDSNodeElementBase> m_Defunct;
  int m_TableGeneration = 0;
};

