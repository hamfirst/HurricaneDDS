
#include "DDSTokenValidator.h"
#include "DDSRandom.h"


void DDSTokenValidator::MarkTokenComplete(uint64_t request_id, bool valid, std::string && data)
{
  auto itr = m_Responses.find(request_id);
  if (itr == m_Responses.end())
  {
    return;
  }

  itr->second.m_Complete = true;
  itr->second.m_Valid = valid;
  itr->second.m_Data = std::move(data);
}

bool DDSTokenValidator::CompleteCallback(const uint64_t & callback_id, const std::function<void(bool, const std::string &)> & function)
{
  auto itr = m_Responses.find(callback_id);
  if (itr == m_Responses.end())
  {
    return true;
  }

  if (itr->second.m_Complete == false)
  {
    return false;
  }

  function(itr->second.m_Valid, itr->second.m_Data);
  return true;
}

uint64_t DDSTokenValidator::GetCallbackData(uint64_t token)
{
  uint64_t request_id = DDSGetRandomNumber64();

  m_Responses.emplace(std::make_pair(request_id, ResponseData{}));

  return request_id;
}

