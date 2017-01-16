#pragma once

#include <StormRefl/StormRefl.h>

#include <time.h>

class DDSThrottle
{
public:
  STORM_REFL;

  DDSThrottle();
  DDSThrottle(int max, float rate);

  bool GrabCredits(time_t current_network_time, int credit_req);
  bool HasCredits(time_t current_network_time, int credit_req);
  void SubCredits(int credit_req);

  void SetReboundTime(time_t current_network_time, int seconds);

private:

  void UpdateCredits(time_t current_network_time);

public:

  float m_Credits = 0.0f;
  float m_Rate = 1.0f;
  float m_Max = 0.0f;

  time_t m_CreditStart = 0;
};
