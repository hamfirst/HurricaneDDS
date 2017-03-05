

#include <StormSockets/StormSocketBackend.h>

#include "DDSNetworkBackend.h"

DDSNetworkBackend::DDSNetworkBackend(const StormSockets::StormSocketInitSettings & settings)
  : m_Backend(std::make_unique<StormSockets::StormSocketBackend>(settings))
{

}

DDSNetworkBackend::~DDSNetworkBackend()
{

}

std::string DDSNetworkBackend::GetMemoryReport()
{
  std::string report;
  for (auto & val : m_Backend->GetMallocReport())
  {
    report += std::to_string(val) + " ";
  }

  return report;
}
