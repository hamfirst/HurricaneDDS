
#include "DDSShutdown.h"
#include "DDSNodeState.h"
#include "DDSCoordinatorState.h"

#include <sb/vector.h>

#include <signal.h>
#include <thread>

static std::vector<DDSNodeState *> s_Nodes;
static DDSCoordinatorState * s_CoordinatorState;
static volatile bool s_WantsShutdown = false;
static volatile bool s_IsShutDown;

void DDSSignalHandler(int signal)
{
  s_WantsShutdown = true;

#ifndef _LINUX
  while (s_IsShutDown == false)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
#endif
}

void DDSSetupShutdownSignalHandler()
{
  signal(SIGINT, DDSSignalHandler);
  signal(SIGTERM, DDSSignalHandler);

#ifndef _LINUX
  signal(SIGBREAK, DDSSignalHandler);
#endif
}

bool DDSWantsShutdown()
{
  return s_WantsShutdown;
}

void DDSShutdown()
{
  for (auto & node_ptr : s_Nodes)
  {
    node_ptr->Shutdown();
  }

  while (true)
  {
    bool all_shutdown = true;
    for (auto & node_ptr : s_Nodes)
    {
      node_ptr->ProcessEvents();
      if (node_ptr->IsFullyShutdown() == false)
      {
        all_shutdown = false;
      }
    }

    if (s_CoordinatorState)
    {
      s_CoordinatorState->ProcessEvents();
    }

    if (all_shutdown)
    {
      break;
    }
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  s_IsShutDown = true;
}

void DDSShutdownRegisterNode(DDSNodeState * node)
{
  s_Nodes.push_back(node);
}

void DDSShutdownUnregisterNode(DDSNodeState * node)
{
  vremove_quick(s_Nodes, node);
}

void DDSShutdownRegisterCoordinator(DDSCoordinatorState * coordinator)
{
  s_CoordinatorState = coordinator;
}

void DDSShutdownUnregisterCoordinator(DDSCoordinatorState * coordinator)
{
  s_CoordinatorState = nullptr;
}
