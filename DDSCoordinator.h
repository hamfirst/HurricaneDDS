#pragma once

#include <StormSockets\StormSocketServerTypes.h>

class DDSCoordinatorState;

class DDSCoordinator
{
public:
  DDSCoordinator(const StormSockets::StormSocketInitSettings & backend_settings,
    const StormSockets::StormSocketServerFrontendWebsocketSettings & server_settings);
  DDSCoordinator(const DDSCoordinator & rhs) = delete;
  DDSCoordinator(DDSCoordinator && rhs);

  DDSCoordinator & operator = (const DDSCoordinator & rhs) = delete;
  DDSCoordinator & operator = (DDSCoordinator && rhs);

  ~DDSCoordinator();

  void ProcessEvents();

private:

  DDSCoordinatorState * m_CoordinatorState;
};

