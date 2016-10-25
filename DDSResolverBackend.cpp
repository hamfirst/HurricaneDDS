
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

int DDSResolverBackend::RequestResolve(const char * addr, bool reverse_lookup, DDSResolverRequest * request)
{
  int query_id = (int)DDSGetRandomNumber();

  while (m_OutputMap.find(query_id) != m_OutputMap.end())
  {
    query_id = (int)DDSGetRandomNumber();
  }

  m_OutputMap.emplace(std::make_pair(query_id, request));

  auto resolver_callback = [this, query_id, reverse_lookup](asio::error_code ec, asio::ip::tcp::resolver::iterator itr)
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
        if (reverse_lookup)
        {
          elem->second->m_Result = itr->host_name();
          break;
        }
        else
        {
          asio::ip::tcp::endpoint ep = *itr;
          if (ep.protocol() == ep.protocol().v4())
          {
            elem->second->m_Result = ep.address().to_string();
            break;
          }
        }

        ++itr;
      }
    }
    else
    {
      elem->second->m_Result = ec.message();
    }

    m_OutputMap.erase(elem);
  };

  if (reverse_lookup)
  {
    asio::ip::address_v4 ipa = asio::ip::address_v4::from_string(addr);
    asio::ip::tcp::endpoint ep;
    ep.address(ipa);

    m_Resolver.async_resolve(ep, resolver_callback);
  }
  else
  {
    asio::ip::tcp::resolver::query resolver_query(addr);
    m_Resolver.async_resolve(resolver_query, resolver_callback);
  }
  return query_id;
}

void DDSResolverBackend::CancelResolve(int id)
{
  m_OutputMap.erase(id);
}
