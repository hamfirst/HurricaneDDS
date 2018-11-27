
#include "DDSThrottle.refl.h"


DDSThrottle::DDSThrottle()
{

}

DDSThrottle::DDSThrottle(int max, float rate) :
  m_Credits((float)max),
  m_Rate(rate),
  m_Max((float)max)
{

}

bool DDSThrottle::GrabCredits(time_t current_network_time, int credit_req)
{
  UpdateCredits(current_network_time);

  if (m_Credits >= credit_req)
  {
    m_Credits -= credit_req;
    return true;
  }

  return false;
}

bool DDSThrottle::HasCredits(time_t current_network_time, int credit_req)
{
  UpdateCredits(current_network_time);
  return m_Credits >= credit_req;
}

void DDSThrottle::SubCredits(int credit_req)
{
  m_Credits -= credit_req;
  if (m_Credits < 0)
  {
    m_Credits = 0;
  }
}

void DDSThrottle::SetReboundTime(time_t current_network_time, int seconds)
{
  UpdateCredits(current_network_time);
  m_CreditStart = current_network_time + seconds;
}

void DDSThrottle::UpdateCredits(time_t current_network_time)
{
  float time_passed = (float)(current_network_time - m_CreditStart);

  m_CreditStart = current_network_time;
  if (time_passed < 0)
  {
    return;
  }

  m_Credits += (time_passed * m_Rate);
  if (m_Credits > m_Max)
  {
    m_Credits = m_Max;
  }
}
