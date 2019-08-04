#pragma once

#include <string>

#include <StormSockets/StormUrlUtil.h>

class DDSHttpRequest
{
public:
  DDSHttpRequest(const char * url);
  DDSHttpRequest(const std::string & url);

  DDSHttpRequest(const char * url, const char * body);
  DDSHttpRequest(const std::string & url, const std::string & body);

  DDSHttpRequest(const char * url, const char * body, const char * headers);
  DDSHttpRequest(const std::string & url, const std::string & body, const std::string & headers);

  DDSHttpRequest(const DDSHttpRequest & rhs) = default;
  DDSHttpRequest(DDSHttpRequest && rhs) = default;

  DDSHttpRequest & operator = (const DDSHttpRequest & rhs) = default;
  DDSHttpRequest & operator = (DDSHttpRequest && rhs) = default;

  void SetMethod(const char * method);
  void SetMethod(const std::string & method);

public:

  StormSockets::StormURI m_Uri;
  std::string m_Method;
  std::string m_Body;
  std::string m_Headers;
};

