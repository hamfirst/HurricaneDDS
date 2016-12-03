#pragma once

#include <unordered_map>

#include "DDSDeferredCallbackSystem.h"


class DDSTokenValidator : public DDSDeferredCallbackSystem<uint64_t, uint64_t, bool, const std::string &>
{
public:

  void MarkTokenComplete(uint64_t request_id, bool valid, std::string && data);

protected:
  bool CompleteCallback(const uint64_t & callback_id, const std::function<void(bool, const std::string &)> & function) override;
  uint64_t GetCallbackData(uint64_t token) override;

private:
  struct ResponseData
  {
    bool m_Complete;
    bool m_Valid;
    std::string m_Data;
  };

  std::unordered_map<uint64_t, ResponseData> m_Responses;
};
