#pragma once

#include <string>

#include <StormRefl\StormReflJson.h>

template <class T>
std::string DDSGetServerMessage(const T & t)
{
  std::string send_buffer = StormReflGetEnumAsString(T::Type);
  send_buffer += ' ';
  StormReflEncodeJson(t, send_buffer);
  return send_buffer;
}

