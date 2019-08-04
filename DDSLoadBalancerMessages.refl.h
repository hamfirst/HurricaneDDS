#pragma once

#include <StormRefl/StormRefl.h>

#include <vector>
#include <string>

#include "DDSNodeId.h"
#include "DDSKey.h"


struct DDSLoadBalancerNode
{
  STORM_REFL;

  std::string m_IpAddr;
  int m_Port;
  int m_Cpu;
};

struct DDSLoadBalancerInfo
{
  STORM_REFL;
  std::vector<DDSLoadBalancerNode> m_Nodes;
};

struct DDSLoadBalancerResponse
{
  STORM_REFL;
  std::string host;
  int port;
};
