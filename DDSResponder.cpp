
#include "DDSResponder.h"
#include "DDSNodeState.h"

#include "DDSServerToServerMessages.refl.meta.h"

#include <StormRefl\StormReflJsonStd.h>

void DDSResponderCallFinalize(const DDSResponder & responder, const DDSResponderCallData & call_data)
{
  responder.m_NodeState.SendTargetedMessage(DDSDataObjectAddress{ responder.m_Data.m_ObjectType, responder.m_Data.m_Key }, 
    DDSServerToServerMessageType::kResponderCall, StormReflEncodeJson(call_data));
}
