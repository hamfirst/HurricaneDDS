#pragma once

#include <unordered_map>
#include <queue>
#include <chrono>

#include <StormRefl/StormReflJsonStd.h>

#include "DDSRandom.h"

class DDSTokenBroker
{
public:

  uint32_t GetToken(std::string && token_data, int type, int timeout_seconds);
  bool ValidateToken(uint32_t token, int type, std::string & out_token_data);

  void Update();

private:

  struct TimeoutInfo
  {
    std::chrono::system_clock::time_point m_Expire;
    uint32_t m_Key;

    bool operator < (const TimeoutInfo & rhs) const
    {
      return m_Expire < rhs.m_Expire;
    }
  };

  struct TokenInfo
  {
    std::string m_Data;
    int m_Type;
  };

  std::priority_queue<TimeoutInfo> m_Timeouts;
  std::unordered_map<uint32_t, TokenInfo> m_Tokens;
};

