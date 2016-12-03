
#include "DDSTokenBroker.h"


uint32_t DDSTokenBroker::GetToken(std::string && token_data, int type, int timeout_seconds)
{
  uint32_t token = DDSGetRandomNumber();
  m_Tokens.emplace(std::make_pair(token, TokenInfo{ token_data, type }));

  m_Timeouts.emplace(TimeoutInfo{ std::chrono::system_clock::now() + std::chrono::seconds(timeout_seconds), token });
  return token;
}

bool DDSTokenBroker::ValidateToken(uint32_t token, int type, std::string & out_token_data)
{
  auto itr = m_Tokens.find(token);
  if (itr == m_Tokens.end())
  {
    return false;
  }

  if (itr->second.m_Type != type)
  {
    return false;
  }

  out_token_data = std::move(itr->second.m_Data);
  m_Tokens.erase(itr);
  return true;
}

void DDSTokenBroker::Update()
{
  while (m_Timeouts.size() > 0)
  {
    if (m_Timeouts.top().m_Expire >= std::chrono::system_clock::now())
    {
      break;
    }

    m_Tokens.erase(m_Timeouts.top().m_Key);
    m_Timeouts.pop();
  }
}