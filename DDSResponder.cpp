
#include "DDSResponder.h"
#include "DDSObjectInterface.h"
#include "DDSServerMessage.h"

#include "DDSServerToServerMessages.refl.meta.h"

#include <StormRefl/StormReflJsonStd.h>

void DDSResponderCallFinalize(const DDSResponder & responder, const DDSResponderCallBase & call_data)
{
  responder.m_Interface.SendResponderCall(call_data);
}
