#pragma once

#include <string>

#include <StormRefl/StormReflMetaCallJson.h>

#include "DDSNodeState.h"
#include "DDSResponder.h"

class DDSNodeState;

template <class ... Args>
void DDSResponderCall(DDSResponder & responder, Args && ... args)
{
  DDSResponderCallDataBase call_data;

  call_data.m_Key = responder.m_Data.m_Key;
  call_data.m_ObjectType = responder.m_Data.m_ObjectType;

  call_data.m_MethodArgs = '[';
  call_data.m_MethodArgs += std::to_string(responder.m_ReturnMethodId);
  StormReflMetaHelpers::StormReflCallSerializeJsonParameterPack(call_data.m_MethodArgs, std::forward<Args>(args)...);
  call_data.m_MethodArgs += ']';
  
  DDSResponderCallFinalize(responder, call_data);
}


