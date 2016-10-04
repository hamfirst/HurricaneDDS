#pragma once

#include "DDSResponder.refl.h"

class DDSNodeState;
struct DDSResponderCallData;

struct DDSResponder
{
  DDSNodeState & m_NodeState;
  DDSResponderData m_Data;
};

void DDSResponderCallFinalize(const DDSResponder & responder, const DDSResponderCallData & call_data);
