#pragma once

#include <string>

class DDSLog
{
public:
  static void LogInfo(const char * fmt, ...);
  static void LogVerbose(const char * fmt, ...);
  static void LogVerbose(const std::string & str);

  static void LogError(const char * fmt, ...);
};


