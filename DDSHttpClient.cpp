
#include "DDSHttpClient.h"
#include "DDSNodeState.h"
#include "DDSLog.h"

#include <StormSockets\StormSocketClientFrontendHttp.h>

DDSHttpClient::DDSHttpClient(const StormSockets::StormSocketClientFrontendHttpSettings & settings, DDSNetworkBackend & backend) :
  m_HttpClient(std::make_unique<StormSockets::StormSocketClientFrontendHttp>(settings, backend.m_Backend.get()))
{

}

DDSHttpClient::~DDSHttpClient()
{

}

void DDSHttpClient::Update()
{
  StormSockets::StormSocketEventInfo event_info;
  while (m_HttpClient->GetEvent(event_info))
  {
    switch (event_info.Type)
    {
    case StormSockets::StormSocketEventType::Data:
      for (auto & callback : m_PendingCallbacks)
      {
        if (callback.m_CallbackData.m_ConnectionId == event_info.ConnectionId)
        {
          auto & client_data = const_cast<DDSHttpClientData &>(callback.m_CallbackData);
          client_data.m_Complete = true;
          client_data.m_Success = true;

          auto & reader = event_info.GetHttpResponseReader();
          client_data.m_OutputData.resize(reader.GetBodyReader().GetRemainingLength() + 1);
          reader.GetBodyReader().ReadByteBlock(client_data.m_OutputData.data(), reader.GetBodyReader().GetRemainingLength());
          client_data.m_OutputData[reader.GetBodyReader().GetRemainingLength()] = 0;
          break;
        }
      }
      break;
    case StormSockets::StormSocketEventType::Disconnected:
      for (auto & callback : m_PendingCallbacks)
      {
        if (callback.m_CallbackData.m_ConnectionId == event_info.ConnectionId)
        {
          auto & client_data = const_cast<DDSHttpClientData &>(callback.m_CallbackData);
          client_data.m_Complete = true;
          break;
        }
      }

      m_HttpClient->FinalizeConnection(event_info.ConnectionId);
      break;
    }
  }

  DDSDeferredCallbackSystem<const char *, DDSHttpClientData, bool, const std::string &>::Update();
}

bool DDSHttpClient::CompleteCallback(const DDSHttpClientData & callback_data, const std::function<void(bool, const std::string &)> & callback)
{
  if (callback_data.m_Complete)
  {
    callback(callback_data.m_Success, callback_data.m_OutputData.data());
    return true;
  }

  return false;
}

DDSHttpClientData DDSHttpClient::GetCallbackData(const char * url)
{
  auto connection_id = m_HttpClient->RequestConnect(url);
  if (connection_id == StormSockets::StormSocketConnectionId::InvalidConnectionId)
  {
    DDSLog::LogError("Invalid url");
  }

  DDSHttpClientData data;
  data.m_ConnectionId = connection_id;
  return data;
}
