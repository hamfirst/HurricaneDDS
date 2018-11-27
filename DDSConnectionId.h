#pragma once

class DDSEndpointFactoryBase;

struct DDSConnectionId
{
  DDSEndpointFactoryBase * m_EndpointFactory;
  int m_ConnectionId;
};

