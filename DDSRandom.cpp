
#include <random>
#include <chrono>

#include "DDSRandom.h"

static std::default_random_engine s_RandomEngine(std::random_device{}());
static std::mt19937_64 s_RandomEngine64(std::random_device{}());

uint32_t DDSGetRandomNumber()
{
  return s_RandomEngine();
}


uint32_t DDSGetRandomNumberRange(uint32_t low, uint32_t high)
{
  std::uniform_int_distribution<uint32_t> dist(low, high);
  return dist(s_RandomEngine);
}

uint64_t DDSGetRandomNumber64()
{
  return s_RandomEngine64();
}

uint64_t DDSGetRandomNumberRange64(uint64_t low, uint64_t high)
{
  std::uniform_int_distribution<uint64_t> dist(low, high);
  return dist(s_RandomEngine64);
}
