#pragma once

#include "DDSResponder.refl.h"

class DDSInterface;
struct DDSResponderCallBase;

struct DDSResponder
{
  DDSInterface & m_Interface;
  DDSResponderData m_Data;
};

void DDSResponderCallFinalize(const DDSResponder & responder, const DDSResponderCallBase & call_data);
