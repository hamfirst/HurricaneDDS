
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

  DDSDeferredCallbackSystem<const char *, std::unique_ptr<DDSResolverRequest>, const DDSResolverRequest &>::Update();
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

std::unique_ptr<DDSResolverRequest> DDSResolver::GetCallbackData(const char * creation_data)
{
  std::unique_ptr<DDSResolverRequest> request = std::make_unique<DDSResolverRequest>();
  m_Backend->RequestResolve(creation_data, request.get());

  return std::move(request);
}

