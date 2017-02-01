#pragma once

#include "DDSResponder.refl.h"

class DDSObjectInterface;
struct DDSResponderCallBase;

struct DDSResponder
{
  DDSObjectInterface & m_Interface;
  DDSResponderData m_Data;
};

DDSResponder CreateEmptyResponder(DDSObjectInterface & iface);
void DDSResponderCallFinalize(const DDSResponder & responder, const DDSResponderCallBase & call_data);
