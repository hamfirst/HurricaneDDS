
#include "DDSDeferredCallback.h"
#include "DDSDeferredCallbackSystem.h"


DDSDeferredCallback::DDSDeferredCallback()
{
  m_System = nullptr;
}

DDSDeferredCallback::DDSDeferredCallback(DDSDeferredCallback && rhs)
{
  if (rhs.m_System)
  {
    m_Id = rhs.m_Id;
    m_System = rhs.m_System;

    rhs.m_System = nullptr;

    m_System->MoveCallback(m_Id, this);
  }
  else
  {
    m_System = nullptr;
  }
}

DDSDeferredCallback & DDSDeferredCallback::operator = (DDSDeferredCallback && rhs)
{
  if (rhs.m_System)
  {
    m_Id = rhs.m_Id;
    m_System = rhs.m_System;

    rhs.m_System = nullptr;

    m_System->MoveCallback(m_Id, this);
  }
  else
  {
    m_System = nullptr;
  }

  return *this;
}

DDSDeferredCallback::~DDSDeferredCallback()
{
  Cancel();
}

void DDSDeferredCallback::Cancel()
{
  if (m_System)
  {
    m_System->DestroyCallback(m_Id);
    m_System = nullptr;
  }
}

void DDSDeferredCallback::Unlink()
{
  m_System = nullptr;
}
