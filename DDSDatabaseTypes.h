#pragma once

struct DDSDatabaseSettings
{
  const char * DatabaseHostName = "localhost";
  int DatabasePort = 27017;

  const char * DatabaseName = "dds";
  int NumThreads = 4;
};
