
#include "DDSResolver.h"
#include "DDSResolverBackend.h"

DDSResolver::DDSResolver() :
  m_Backend(std::make_unique<DDSResolverBackend>())
{

}

DDSResolver::~DDSResolver()
{

}

void DDSResolver::Update()
{
  m_Backend->Update();

  DDSDeferredCallbackSystem<std::pair<const char *, bool>, std::unique_ptr<DDSResolverRequest>, const DDSResolverRequest &>::Update();
}

bool DDSResolver::CompleteCallback(const std::unique_ptr<DDSResolverRequest> & callback_data, const std::function<void(const DDSResolverRequest &)> & callback)
{
  if (callback_data->m_Complete)
  {
    callback(*callback_data);
    return true;
  }

  return false;
}

std::unique_ptr<DDSResolverRequest> DDSResolver::GetCallbackData(std::pair<const char *, bool> creation_data)
{
  std::unique_ptr<DDSResolverRequest> request = std::make_unique<DDSResolverRequest>();
  m_Backend->RequestResolve(creation_data.first, creation_data.second, request.get());

  return std::move(request);
}

