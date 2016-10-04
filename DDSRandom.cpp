
#include <random>
#include <chrono>

#include "DDSRandom.h"

static std::default_random_engine s_RandomEngine((unsigned)std::chrono::steady_clock::now().time_since_epoch().count());

uint32_t DDSGetRandomNumber()
{
  return s_RandomEngine();
}
