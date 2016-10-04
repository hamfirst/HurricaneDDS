
#include "DDSCoordinator.h"
#include "DDSCoordinatorState.h"
#include "DDSCoordinatorServerProtocol.h"

#include <StormSockets\StormSocketClientFrontendWebsocket.h>
#include <StormSockets\StormSocketServerFrontendWebsocket.h>

DDSCoordinator::DDSCoordinator(const StormSockets::StormSocketInitSettings & backend_settings,
  const StormSockets::StormSocketServerFrontendWebsocketSettings & server_settings)
{
  m_CoordinatorState = new DDSCoordinatorState(backend_settings, server_settings);
}

DDSCoordinator::DDSCoordinator(DDSCoordinator && rhs)
{
  m_CoordinatorState = rhs.m_CoordinatorState;
  rhs.m_CoordinatorState = nullptr;
}

DDSCoordinator & DDSCoordinator::operator = (DDSCoordinator && rhs)
{
  m_CoordinatorState = rhs.m_CoordinatorState;
  rhs.m_CoordinatorState = nullptr;
  return *this;
}

DDSCoordinator::~DDSCoordinator()
{
  if (m_CoordinatorState)
  {
    delete m_CoordinatorState;
  }
}

void DDSCoordinator::ProcessEvents()
{
  m_CoordinatorState->ProcessEvents();
}
