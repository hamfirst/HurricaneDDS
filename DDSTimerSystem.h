#pragma once

#include <set>

#include <chrono>


#include "DDSDeferredCallbackSystem.h"

class DDSTimerSystem : public DDSDeferredCallbackSystem<std::chrono::system_clock::duration, std::chrono::system_clock::time_point>
{
public:

  bool CompleteCallback(const std::chrono::system_clock::time_point & callback_data, const std::function<void()> & callback) override;
  std::chrono::system_clock::time_point GetCallbackData(std::chrono::system_clock::duration creation_data) override;
};

