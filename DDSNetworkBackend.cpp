

#include <StormSockets\StormSocketBackend.h>

#include "DDSNetworkBackend.h"

DDSNetworkBackend::DDSNetworkBackend(const StormSockets::StormSocketInitSettings & settings)
  : m_Backend(std::make_unique<StormSockets::StormSocketBackend>(settings))
{

}

DDSNetworkBackend::~DDSNetworkBackend()
{

}