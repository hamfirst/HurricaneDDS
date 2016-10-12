#pragma once

#include <asio\asio.hpp>

#include <map>

#include "DDSResolverRequest.h"

class DDSResolverBackend
{
public:
  DDSResolverBackend();
  ~DDSResolverBackend();

  void Update();
  int RequestResolve(const char * hostname, DDSResolverRequest * request);
  void CancelResolve(int id);

private:
  asio::io_service m_IoService;
  asio::ip::tcp::resolver m_Resolver;

  std::map<int, DDSResolverRequest *> m_OutputMap;
};

