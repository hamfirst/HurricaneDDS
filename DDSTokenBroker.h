#pragma once

#include <unordered_map>
#include <queue>
#include <chrono>

#include "DDSRandom.h"

template <typename TokenData, int ExpirationTimeSeconds>
class DDSTokenBroker
{
public:

  uint64_t GetToken(const TokenData & token_data)
  {
    uint64_t token = DDSGetRandomNumber64();
    m_Tokens.emplace(std::make_pair(token, token_data));

    m_Timeouts.emplace(std::make_pair(std::chrono::system_clock::now() + std::chrono::seconds(ExpirationTimeSeconds), token));
    return token;
  }

  bool ValidateToken(uint64_t token, TokenData & out_token_data)
  {
    auto itr = m_Tokens.find(token);
    if (itr == m_Tokens.end())
    {
      return false;
    }

    out_token_data = itr->second;
    m_Tokens.erase(itr);
    return true;
  }

  void Update()
  {
    while (m_Timeouts.size() > 0)
    {
      if (m_Timeouts.back().first >= std::chrono::system_clock::now())
      {
        break;
      }

      m_Tokens.erase(m_Timeouts.back().second);
      m_Timeouts.pop();
    }
  }

private:
  std::queue<std::pair<std::chrono::system_clock::time_point, uint64_t>> m_Timeouts;
  std::unordered_map<uint64_t, TokenData> m_Tokens;
};

