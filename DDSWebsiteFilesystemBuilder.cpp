
#include <experimental/filesystem>

#include "DDSWebsiteFilesystemBuilder.h"

namespace fs = std::experimental::filesystem;

void DDSWebsiteFilesystemBuilder::AddDirectory(const char * dir_path, const char * base_url)
{
  for (auto & file : fs::directory_iterator(dir_path))
  {
    if (fs::is_directory(file))
    {
      auto file_path = file.path();
      std::string stem = file_path.filename().string();

      if (stem[0] == '.')
      {
        continue;
      }

      std::string sub_url = base_url;
      sub_url += stem;
      sub_url += '/';

      AddDirectory(file_path.string().data(), sub_url.data());
    }
    else if (fs::is_regular_file(file))
    {
      auto file_path = file.path();
      std::string stem = file_path.filename().string();

      if (stem[0] == '.')
      {
        continue;
      }

      std::string sub_url = base_url;
      sub_url += stem;

      AddFile(file_path.string().data(), sub_url.data());
    }
  }
}

void DDSWebsiteFilesystemBuilder::AddFile(const char * file_path, const char * url)
{
  FILE * fp = fopen(file_path, "rb");
  if (fp == nullptr)
  {
    return;
  }

  fseek(fp, 0, SEEK_END);
  std::size_t len = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  std::vector<char> buffer(len);
  fread(buffer.data(), len, 1, fp);
  fclose(fp);

  m_MappedFiles.emplace(std::make_pair(url, buffer));
}

void DDSWebsiteFilesystemBuilder::AddMemFile(const char * url, const void * data, std::size_t len)
{
  std::vector<char> buffer(len);
  memcpy(buffer.data(), data, len);

  m_MappedFiles.emplace(std::make_pair(url, buffer));
}
