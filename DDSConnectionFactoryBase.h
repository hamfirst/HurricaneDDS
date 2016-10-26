#pragma once

#include <StormSockets/StormSocketConnectionId.h>
#include <StormSockets/StormSocketServerTypes.h>

class DDSConnectionFactoryBase
{
public:

  virtual void ForceDisconnect(StormSockets::StormSocketConnectionId connection_id) = 0;
  virtual bool IsValidConnectionId(StormSockets::StormSocketConnectionId connection_id) = 0;
};

