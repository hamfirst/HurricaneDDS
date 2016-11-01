#pragma once

#include <string>

#include <StormRefl/StormReflMetaCallJson.h>

#include "DDSNodeState.h"
#include "DDSResponder.h"
#include "DDSSharedMessages.refl.h"

class DDSNodeState;

template <class ... Args>
void DDSResponderCall(DDSResponder & responder, Args && ... args)
{
  DDSResponderCallBase call_data;

  call_data.m_Key = responder.m_Data.m_Key;
  call_data.m_ObjectType = responder.m_Data.m_ObjectType;
  call_data.m_MethodId = responder.m_Data.m_ReturnMethodId;
  call_data.m_ResponderArgs = responder.m_Data.m_ReturnArg;

  call_data.m_MethodArgs = '[';
  StormReflMetaHelpers::StormReflCallSerializeJsonParameterPack(call_data.m_MethodArgs, std::forward<Args>(args)...);
  call_data.m_MethodArgs += ']';
  
  DDSResponderCallFinalize(responder, call_data);
}


