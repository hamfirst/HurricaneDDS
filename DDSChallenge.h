#pragma once

#include <string>
#include <hash/Hash64.h>

inline uint64_t DDSCalculateChallengeResponse(uint64_t challenge)
{
  std::string str = std::to_string(challenge);
  return crc64(str);
}

