#pragma once

#include <cstdint>

#include "DDSNodeId.h"

#include <StormRefl\StormRefl.h>
#include <StormRefl\StormReflJsonStd.h>

enum STORM_REFL_ENUM class DDSCoordinatorProtocolMessageType
{
  kUnknown,
  kHandshakeRequest,
  kHandshakeResponse,
  kHandshakeFinalize,
  kNodeInit,
  kRoutingTable,
};

struct DDSCoordinatorHandshakeRequest
{
  STORM_REFL;
  static const DDSCoordinatorProtocolMessageType Type = DDSCoordinatorProtocolMessageType::kHandshakeRequest;

  uint64_t m_Challenge;
  int m_Version;
};

struct DDSCoordinatorHandshakeResponse
{
  STORM_REFL;
  static const DDSCoordinatorProtocolMessageType Type = DDSCoordinatorProtocolMessageType::kHandshakeResponse;
  uint64_t m_ChallengeResponse;
  uint64_t m_ChallengeRequest;
};

struct DDSCoordinatorHandshakeFinalize
{
  STORM_REFL;
  static const DDSCoordinatorProtocolMessageType Type = DDSCoordinatorProtocolMessageType::kHandshakeFinalize;

  uint64_t m_ChallengeResponse;
  uint32_t m_PublicIp;
  uint16_t m_PublicPort;
};

struct DDSCoordinatorNodeInitialization
{
  STORM_REFL;
  static const DDSCoordinatorProtocolMessageType Type = DDSCoordinatorProtocolMessageType::kNodeInit;

  DDSNodeId m_NodeId;
  uint64_t m_ClientSecret;
  uint64_t m_ServerSecret;
  bool m_InitialNode;
};

