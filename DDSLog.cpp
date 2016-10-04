
#include "DDSLog.h"

#include <cstdio>
#include <cstdarg>

void DDSLog::LogInfo(const char * fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);

  printf("\r\n");
}

void DDSLog::LogVerbose(const char * fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);

  printf("\r\n");
}

void DDSLog::LogVerbose(const std::string & str)
{
  printf("%s\r\n", str.c_str());
}

void DDSLog::LogError(const char * fmt, ...)
{
  char buffer[4096];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);

  throw std::runtime_error(buffer);
}
