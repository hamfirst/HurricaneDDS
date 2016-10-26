#pragma once

#include <unordered_map>
#include <vector>

#include <hash/Hash.h>

class DDSWebsiteFilesystemBuilder
{
public:
  void AddDirectory(const char * dir_path, const char * base_url);
  void AddFile(const char * file_path, const char * url);

  void AddMemFile(const char * url, const void * data, std::size_t len);

private:
  friend class DDSWebsiteFilesystem;

  std::unordered_map<std::string, std::vector<char>> m_MappedFiles;
};

