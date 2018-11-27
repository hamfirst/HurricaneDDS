#pragma once

#include <string>

struct DDSResolverRequest
{
  volatile bool m_Complete;
  volatile bool m_Success;
  std::string m_Result;
};

