#pragma once

#include <memory>
#include <vector>

#include <StormSockets/StormSocketServerTypes.h>

#include "DDSDeferredCallbackSystem.h"
#include "DDSHttpRequest.h"

class DDSNetworkBackend;

namespace StormSockets
{
  class StormSocketClientFrontendHttp;
}

struct DDSHttpClientData
{
  StormSockets::StormSocketConnectionId m_ConnectionId;
  std::vector<char> m_OutputHeaders;
  std::vector<char> m_OutputBody;
  bool m_Success = false;
  bool m_Complete = false;

  bool operator < (const DDSHttpClientData & rhs) const
  {
    return m_ConnectionId.m_Index.Raw < rhs.m_ConnectionId.m_Index.Raw;
  }
};

class DDSNodeState;

class DDSHttpClient : public DDSDeferredCallbackSystem<const DDSHttpRequest &, DDSHttpClientData, bool, const std::string &, const std::string &>
{
public:
  DDSHttpClient(const StormSockets::StormSocketClientFrontendHttpSettings & settings, DDSNetworkBackend & backend);
  ~DDSHttpClient();

  void Update() override;

private:

  bool CompleteCallback(const DDSHttpClientData & callback_data, const std::function<void(bool, const std::string &, const std::string &)> & callback) override;
  DDSHttpClientData GetCallbackData(const DDSHttpRequest & request) override;

  std::unique_ptr<StormSockets::StormSocketClientFrontendHttp> m_HttpClient;
};

