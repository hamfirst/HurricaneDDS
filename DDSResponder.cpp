
#include "DDSResponder.h"
#include "DDSObjectInterface.h"
#include "DDSServerMessage.h"
#include "DDSLog.h"

#include "DDSServerToServerMessages.refl.meta.h"

#include <StormRefl/StormReflJsonStd.h>


DDSResponder CreateEmptyResponder(DDSObjectInterface & iface)
{
  return DDSResponder { iface,{ 0, -1, -1, -1 } };
}

void DDSResponderCallFinalize(const DDSResponder & responder, const DDSResponderCallBase & call_data)
{
  if (call_data.m_MethodId == -1)
  {
    return;
  }

  responder.m_Interface.SendResponderCall(call_data);
}
