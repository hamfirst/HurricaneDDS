#pragma once

struct DDSDatabaseSettings
{
  const char * DatabaseHostName = "localhost";
  int DatabasePort = 27017;

  int NumThreads = 4;
  const char * DatabaseName = "dds";
};
