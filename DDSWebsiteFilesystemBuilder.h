#pragma once

#include <unordered_map>
#include <vector>

#include <hash/Hash.h>

class DDSWebsiteFilesystemBuilder
{
public:
  DDSWebsiteFilesystemBuilder();

  void AddDirectory(const char * dir_path, const char * base_url);
  void AddFile(const char * file_path, const char * url);

  void AddMemFile(const char * url, const void * data, std::size_t len);

  const char * GetMimeTimeForFileExtension(const char * file_extension);

private:
  friend class DDSWebsiteFilesystem;

  struct FileData
  {
    std::vector<char> m_Buffer;
    const char * m_MimeType;
  };

  std::unordered_map<std::string, FileData> m_MappedFiles;
  std::unordered_map<uint32_t, const char *> m_MimeTypes;
};

