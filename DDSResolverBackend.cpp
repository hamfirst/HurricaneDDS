
#include "DDSResolverBackend.h"
#include "DDSRandom.h"

DDSResolverBackend::DDSResolverBackend() :
  m_Resolver(m_IoService)
{

}

DDSResolverBackend::~DDSResolverBackend()
{

}

void DDSResolverBackend::Update()
{
  m_IoService.poll();
}

int DDSResolverBackend::RequestResolve(const char * hostname, DDSResolverRequest * request)
{
  asio::ip::tcp::resolver::query resolver_query(hostname);
  int query_id = (int)DDSGetRandomNumber();

  while (m_OutputMap.find(query_id) != m_OutputMap.end())
  {
    query_id = (int)DDSGetRandomNumber();
  }

  auto resolver_callback = [this, query_id](asio::error_code ec, asio::ip::tcp::resolver::iterator itr)
  {
    auto elem = m_OutputMap.find(query_id);
    if (elem == m_OutputMap.end())
    {
      return;
    }

    elem->second->m_Complete = true;

    if (!ec)
    {
      elem->second->m_Success = true;
      while (itr != asio::ip::tcp::resolver::iterator())
      {
        asio::ip::tcp::endpoint ep = *itr;

        if (ep.protocol() == ep.protocol().v4())
        {
          elem->second->m_Result = ep.address().to_string();
          break;
        }

        ++itr;
      }
    }

    m_OutputMap.erase(elem);
  };

  m_Resolver.async_resolve(resolver_query, resolver_callback);
  return query_id;
}

void DDSResolverBackend::CancelResolve(int id)
{
  m_OutputMap.erase(id);
}
