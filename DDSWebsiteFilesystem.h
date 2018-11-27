#pragma once

#include <unordered_map>
#include <hash/Hash.h>

#include <StormSockets/StormHttpResponseWriter.h>

#include <HurricaneDDS/DDSWebsiteInterface.h>

class DDSNetworkBackend;
class DDSWebsiteFilesystemBuilder;
class DDSWebsiteInterface;

class DDSWebsiteFilesystem
{
public:
  DDSWebsiteFilesystem(DDSNetworkBackend & backend, const DDSWebsiteFilesystemBuilder & fs_data);
  ~DDSWebsiteFilesystem();

  DDSWebsiteFilesystem(const DDSWebsiteFilesystem & rhs) = delete;
  DDSWebsiteFilesystem(DDSWebsiteFilesystem && rhs);

  DDSWebsiteFilesystem & operator = (const DDSWebsiteFilesystem & rhs) = delete;
  DDSWebsiteFilesystem & operator = (DDSWebsiteFilesystem && rhs) = delete;

  void ServeFile(const std::string & uri, DDSWebsiteInterface & interface);
private:

  DDSNetworkBackend & m_Backend;
  bool m_Initialized;

  std::unordered_map<Hash, StormSockets::StormHttpResponseWriter> m_Responses;
  StormSockets::StormHttpResponseWriter m_ErrorResponse;
};


