
#include "DDSHttpRequest.h"

DDSHttpRequest::DDSHttpRequest(const char * url)
{
  StormSockets::ParseURI(url, m_Uri);
}


DDSHttpRequest::DDSHttpRequest(const std::string & url) :
  DDSHttpRequest(url.data())
{

}

DDSHttpRequest::DDSHttpRequest(const char * url, const char * body) :
  DDSHttpRequest(url)
{
  m_Body = body;
}

DDSHttpRequest::DDSHttpRequest(const std::string & url, const std::string & body) :
  DDSHttpRequest(url)
{
  m_Body = body;
}

DDSHttpRequest::DDSHttpRequest(const char * url, const char * body, const char * headers) :
  DDSHttpRequest(url, body)
{
  m_Headers = headers;
}

DDSHttpRequest::DDSHttpRequest(const std::string & url, const std::string & body, const std::string & headers) :
  DDSHttpRequest(url, body)
{
  m_Headers = headers;
}
