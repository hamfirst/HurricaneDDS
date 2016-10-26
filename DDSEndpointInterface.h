#pragma once

#include <tuple>
#include <string>
#include <chrono>

#include "DDSKey.h"
#include "DDSConnectionId.h"
#include "DDSDeferredCallback.h"
#include "DDSResolverRequest.h"
#include "DDSConnectionInterface.h"

#include <StormRefl/StormReflJsonStd.h>
#include <StormRefl/StormReflMetaCallJson.h>
#include <StormSockets/StormSocketConnectionId.h>

class DDSEndpointFactoryBase;

class DDSEndpointInterface : public DDSConnectionInterface
{
public:
  DDSEndpointInterface(DDSNodeState & node_state, DDSEndpointFactoryBase & endpoint_factory, 
    StormSockets::StormSocketConnectionId connection_id, uint32_t remote_ip, uint16_t remote_port);

  DDSEndpointInterface(const DDSEndpointInterface & rhs) = default;
  DDSEndpointInterface(DDSEndpointInterface && rhs) = default;

  template <typename TargetObject>
  bool ConnectToLocalObject(void (TargetObject::*target_func)(DDSConnectionId connection_id), DDSKey target_key)
  {
    int target_object_type = GetObjectType(StormReflTypeInfo<TargetObject>::GetNameHash());

    TargetObject * data_obj = static_cast<TargetObject *>(GetLocalObject(target_object_type, target_key));
    if (data_obj == nullptr)
    {
      return false;
    }

    (data_obj->*target_func)(DDSConnectionId{ &m_EndpointFactory, m_ConnectionId });
    FinalizeLocalObject(target_object_type, target_key);
    return true;
  }

  template<typename MessageType>
  bool Send(const MessageType & msg_data)
  {
    return SendData(StormReflEncodeJson(msg_data));
  }

  bool SendData(const std::string & data);

protected:
  DDSEndpointFactoryBase & m_EndpointFactory;
};

