
#include "DDSWebsiteFilesystem.h"
#include "DDSWebsiteFilesystemBuilder.h"
#include "DDSNetworkBackend.h"

#include <StormSockets/StormSocketBackend.h>

static const char * error_msg = "<!DOCTYPE HTML PUBLIC \" -//IETF//DTD HTML 2.0//EN\"><html><head><title>404 Not Found</title></head>"
  "<body><h1>Not Found</h1><p>The requested URL was not found on this server.</p></body></html>";

DDSWebsiteFilesystem::DDSWebsiteFilesystem(DDSNetworkBackend & backend, const DDSWebsiteFilesystemBuilder & fs_data)
  : m_Backend(backend), m_Initialized(true), m_ErrorResponse(m_Backend.m_Backend->CreateHttpResponseWriter(404, "Not Found"))
{
  for (auto & file_info : fs_data.m_MappedFiles)
  {
    auto writer = m_Backend.m_Backend->CreateHttpResponseWriter(200, "OK");
    writer.WriteBody(file_info.second.data(), (int)file_info.second.size());
    writer.FinalizeHeaders();

    m_Responses.emplace(std::make_pair(crc32(file_info.first), writer));
  }

  auto index_itr = m_Responses.find(crc32("/index.html"));
  if (index_itr != m_Responses.end())
  {
    m_Responses.emplace(std::make_pair(crc32("/"), index_itr->second));

    m_Backend.m_Backend->ReferenceOutgoingHttpResponse(index_itr->second);
  }

  auto not_found_itr = m_Responses.find(crc32("/404.html"));
  if (not_found_itr != m_Responses.end())
  {
    m_Backend.m_Backend->FreeOutgoingHttpResponse(m_ErrorResponse);
    m_ErrorResponse = not_found_itr->second;

    m_Backend.m_Backend->ReferenceOutgoingHttpResponse(m_ErrorResponse);
  }
  else
  {
    m_ErrorResponse.WriteBody(error_msg, strlen(error_msg));
    m_ErrorResponse.WriteHeader("Connection: Closed");
    m_ErrorResponse.FinalizeHeaders();
  }
}


DDSWebsiteFilesystem::DDSWebsiteFilesystem(DDSWebsiteFilesystem && rhs)
  : m_Backend(rhs.m_Backend), m_Initialized(true), m_Responses(rhs.m_Responses), m_ErrorResponse(rhs.m_ErrorResponse)
{
  rhs.m_Initialized = false;
}

DDSWebsiteFilesystem::~DDSWebsiteFilesystem()
{
  if (m_Initialized)
  {
    for (auto & response : m_Responses)
    {
      m_Backend.m_Backend->FreeOutgoingHttpResponse(response.second);
    }

    m_Backend.m_Backend->FreeOutgoingHttpResponse(m_ErrorResponse);
  }
}

void DDSWebsiteFilesystem::ServeFile(const std::string & uri, DDSWebsiteInterface & interface)
{
  Hash hash = crc32(uri);
  auto itr = m_Responses.find(hash);
  if (itr == m_Responses.end())
  {
    interface.SendResponse(m_ErrorResponse);
    return;
  }

  interface.SendResponse(itr->second);
}

