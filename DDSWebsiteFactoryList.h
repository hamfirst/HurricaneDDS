#pragma once

#include <vector>
#include <utility>

#include "DDSWebsiteFactory.h"
#include "DDSWebsiteFactoryStaticContent.h"

#include <StormSockets\StormSocketServerTypes.h>

class DDSEndpointFactoryBase;

template <typename WebsiteType, typename ... Args>
class DDSCreateWebsiteType
{
public:
  using IntSeqence = std::index_sequence_for<Args...>;

  DDSCreateWebsiteType(const StormSockets::StormSocketServerFrontendHttpSettings & settings)
  {
    m_Settings = settings;
  }

  auto operator()(DDSNodeState & node_state,
    std::vector<std::unique_ptr<DDSEndpointFactoryBase>> & endpoint_list, std::vector<std::unique_ptr<DDSWebsiteFactoryBase>> & website_list) const
  {
    using WebsiteFactoryType = DDSWebsiteFactory<WebsiteType>;
    website_list.push_back(std::make_unique<WebsiteFactoryType>(node_state, m_Settings));
  }

private:

  StormSockets::StormSocketServerFrontendHttpSettings m_Settings;
};

class DDSCreateWebsiteStaticContentType
{
public:
  DDSCreateWebsiteStaticContentType(const StormSockets::StormSocketServerFrontendHttpSettings & settings, const DDSWebsiteFilesystemBuilder & fs) :
    m_Settings(settings), m_Filesystem(fs)
  {
    m_Settings = settings;
  }

  auto operator()(DDSNodeState & node_state,
    std::vector<std::unique_ptr<DDSEndpointFactoryBase>> & endpoint_list, std::vector<std::unique_ptr<DDSWebsiteFactoryBase>> & website_list) const
  {
    website_list.push_back(std::make_unique<DDSWebsiteFactoryStaticContent>(node_state, m_Settings, m_Filesystem));
  }

private:

  StormSockets::StormSocketServerFrontendHttpSettings m_Settings;
  const DDSWebsiteFilesystemBuilder & m_Filesystem;
};
