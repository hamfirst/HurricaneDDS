#pragma once

#include <string>

#include <StormRefl/StormReflJson.h>

#include "DDSServerToServerMessages.refl.meta.h"

template <class T>
std::string DDSGetServerMessage(const T & t)
{
  std::string send_buffer = StormReflGetEnumAsString(T::Type);
  send_buffer += ' ';
  StormReflEncodeJson(t, send_buffer);
  return send_buffer;
}

inline std::string DDSGetServerMessage(DDSServerToServerMessageType type, const char * data)
{
  return std::string(StormReflGetEnumAsString(type)) + " " + data;
}


