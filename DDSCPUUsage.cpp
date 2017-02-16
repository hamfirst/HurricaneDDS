

#ifdef _LINUX

#include <stdio.h>

long double a[4];
long double b[4];

#else

#include "Pdh.h"

#pragma comment(lib, "Pdh.lib")

static PDH_HQUERY s_CPUQuery;
static PDH_HCOUNTER s_CPUTotal;

#endif

void DDSCPUUsageInit()
{
#ifdef _LINUX
  auto fp = fopen("/proc/stat", "r");
  fscanf(fp, "%*s %Lf %Lf %Lf %Lf", &a[0], &a[1], &a[2], &a[3]);
  fclose(fp);
#else
  PdhOpenQuery(NULL, NULL, &s_CPUQuery);
  PdhAddCounter(s_CPUQuery, L"\\Processor(_Total)\\% Processor Time", NULL, &s_CPUTotal);
  PdhCollectQueryData(s_CPUQuery);
#endif
}

float DDSGetCPUUsage()
{
#ifdef _LINUX
  auto fp = fopen("/proc/stat", "r");
  fscanf(fp, "%*s %Lf %Lf %Lf %Lf", &b[0], &b[1], &b[2], &b[3]);
  fclose(fp);

  auto loadavg = ((b[0] + b[1] + b[2]) - (a[0] + a[1] + a[2])) / ((b[0] + b[1] + b[2] + b[3]) - (a[0] + a[1] + a[2] + a[3]));
  
  for (int index = 0; index < 4; index++)
  {
    a[index] = b[index];
  }

  return (float)loadavg;
#else
  PDH_FMT_COUNTERVALUE counter_val;

  PdhCollectQueryData(s_CPUQuery);
  PdhGetFormattedCounterValue(s_CPUTotal, PDH_FMT_DOUBLE, NULL, &counter_val);
  return (float)counter_val.doubleValue;
#endif
}

