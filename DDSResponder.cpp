
#include "DDSResponder.h"
#include "DDSObjectInterface.h"
#include "DDSServerMessage.h"
#include "DDSLog.h"

#include "DDSServerToServerMessages.refl.meta.h"

#include <StormRefl/StormReflJsonStd.h>

void DDSResponderCallFinalize(const DDSResponder & responder, const DDSResponderCallBase & call_data)
{
  if (call_data.m_MethodId == -1)
  {
    DDSLog::LogError("Invalid responder call being sent");
    return;
  }

  responder.m_Interface.SendResponderCall(call_data);
}
