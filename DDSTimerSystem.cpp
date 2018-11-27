
#include "DDSTimerSystem.h"

bool DDSTimerSystem::CompleteCallback(const std::chrono::system_clock::time_point & callback_data, const std::function<void()> & callback)
{
  if (std::chrono::system_clock::now() >= callback_data)
  {
    callback();
    return true;
  }

  return false;
}

std::chrono::system_clock::time_point DDSTimerSystem::GetCallbackData(std::chrono::system_clock::duration creation_data)
{
  return std::chrono::system_clock::now() + creation_data;
}
