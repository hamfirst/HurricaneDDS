#pragma once

#include <string>

class DDSLog
{
public:
  enum LogLevel
  {
    kVerbose,
    kInfo,
    kNone,
  };

  static void SetLogLevel(LogLevel level);

  static void LogInfo(const char * fmt, ...);
  static void LogVerbose(const char * fmt, ...);
  static void LogVerbose(const std::string & str);

  static void LogError(const char * fmt, ...);
};


