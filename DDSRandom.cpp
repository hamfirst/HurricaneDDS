
#include <random>
#include <chrono>

#include "DDSRandom.h"

static std::default_random_engine s_RandomEngine((unsigned)std::chrono::steady_clock::now().time_since_epoch().count());

uint32_t DDSGetRandomNumber()
{
  return s_RandomEngine();
}


uint64_t DDSGetRandomNumber64()
{
  uint64_t val = s_RandomEngine();
  val <<= 32;
  val |= s_RandomEngine();
  return val;
}
