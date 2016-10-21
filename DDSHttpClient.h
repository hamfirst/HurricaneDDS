#pragma once

#include <memory>
#include <vector>

#include <StormSockets\StormSocketServerTypes.h>

#include "DDSDeferredCallbackSystem.h"

class DDSNetworkBackend;

namespace StormSockets
{
  class StormSocketClientFrontendHttp;
}

struct DDSHttpClientData
{
  StormSockets::StormSocketConnectionId m_ConnectionId;
  std::vector<char> m_OutputData;
  bool m_Success = false;
  bool m_Complete = false;

  bool operator < (const DDSHttpClientData & rhs) const
  {
    return m_ConnectionId.m_Index.Raw < rhs.m_ConnectionId.m_Index.Raw;
  }
};

class DDSNodeState;

class DDSHttpClient : public DDSDeferredCallbackSystem<const char *, DDSHttpClientData, bool, const std::string &>
{
public:
  DDSHttpClient(const StormSockets::StormSocketClientFrontendHttpSettings & settings, DDSNetworkBackend & backend);
  ~DDSHttpClient();

  void Update() override;

private:

  bool CompleteCallback(const DDSHttpClientData & callback_data, const std::function<void(bool, const std::string &)> & callback) override;
  DDSHttpClientData GetCallbackData(const char * url) override;

  std::unique_ptr<StormSockets::StormSocketClientFrontendHttp> m_HttpClient;
};

