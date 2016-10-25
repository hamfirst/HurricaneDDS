#pragma once

#include <vector>

#include "DDSEndpointFactory.h"

#include <StormSockets\StormSocketServerTypes.h>

class DDSWebsiteFactoryBase;

template <typename EndpointType>
struct DDSCreateEndpointType
{
  DDSCreateEndpointType(const StormSockets::StormSocketServerFrontendWebsocketSettings & settings)
  {
    m_Settings = settings;
  }

  auto operator()(DDSNodeState & node_state, 
    std::vector<std::unique_ptr<DDSEndpointFactoryBase>> & endpoint_list, std::vector<std::unique_ptr<DDSWebsiteFactoryBase>> & website_list) const
  {
    using EndpointFactoryType = DDSEndpointFactory<EndpointType>;
    endpoint_list.push_back(std::make_unique<EndpointFactoryType>(node_state, m_Settings));
  }

  StormSockets::StormSocketServerFrontendWebsocketSettings m_Settings;
};
