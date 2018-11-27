
#include <cmath>
#include <cstring>
#include <algorithm>

#include "DDSDatabaseSetup.h"

#include <mongoc/mongoc.h>
#include <libbson/bson.h>


void DDSDatabaseInit()
{
  mongoc_init();
}

void DDSDatabaseCleanup()
{
  mongoc_cleanup();
}
