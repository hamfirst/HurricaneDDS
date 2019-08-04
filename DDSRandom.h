#pragma once

#include <cstdint>

uint32_t DDSGetRandomNumber();
uint32_t DDSGetRandomNumberRange(uint32_t low, uint32_t high);
uint64_t DDSGetRandomNumber64();
uint64_t DDSGetRandomNumberRange64(uint64_t low, uint64_t high);

struct DDSRandomGenerator
{
  using result_type = uint32_t;
  static uint32_t min() { return 0; }
  static uint32_t max() { return UINT32_MAX; }
  uint32_t operator ()() { return DDSGetRandomNumber(); }
};

struct DDSRandomGenerator64
{
  using result_type = uint64_t;
  static uint64_t min() { return 0; }
  static uint64_t max() { return UINT64_MAX; }
  uint64_t operator ()() { return DDSGetRandomNumber64(); }
};
