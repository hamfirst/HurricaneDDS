#pragma once

#include <StormRefl\StormRefl.h>

#include <string>
#include <vector>

#include "DDSNodeId.h"
#include "DDSKey.h"

#include "DDSResponder.refl.h"

enum STORM_REFL_ENUM class DDSServerToServerMessageType
{
  kHandshakeRequest,
  kHandshakeResponse,
  kHandshakeFinalize,
  kDataObjectListSync,
  kResponderCall,
  kTargetedMessage,
  kTargetedMessageResponder,
};

struct DDSServerToServerHandshakeRequest
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kHandshakeRequest;

  int m_Version;
  DDSNodeId m_NodeId;
  unsigned long long m_Secret;
  unsigned long long m_Challenge;
};

struct DDSServerToServerHandshakeResponse
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kHandshakeResponse;

  DDSNodeId m_NodeId;
  unsigned long long m_Secret;
  unsigned long long m_Challenge;
  unsigned long long m_ChallengeResponse;
};

struct DDSServerToServerHandshakeFinalize
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kHandshakeFinalize;

  unsigned long long m_Challenge;
};

struct DDSExportedMessage
{
  STORM_REFL;
  std::string m_Message;
  DDSResponderData m_Responder;
};

struct DDSExportedObject
{
  STORM_REFL;
  DDSKey m_Key;
  std::string m_ActiveObject;
  std::string m_DatabaseObject;

  std::vector<DDSExportedMessage> m_PendingMessages;
  std::vector<DDSExportedMessage> m_PendingQueries;
};

struct DDSDataObjectListSync
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kDataObjectListSync;

  int m_DataObjectType;
  int m_RoutingTableGen;
  DDSKey m_KeyRangeMin;
  DDSKey m_KeyRangeMax;

  std::vector<DDSExportedObject> m_Objects;
};

struct DDSResponderCallData
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kResponderCall;
  DDSKey m_Key;
  int m_ObjectType;

  int m_MethodId;
  std::string m_MethodArgs;
};

struct DDSTargetedMessage
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kTargetedMessage;
  DDSKey m_Key;
  int m_ObjectType;

  int m_MethodId;
  std::string m_MethodArgs;
};

struct DDSTargetedMessageWithResponder
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kTargetedMessageResponder;
  DDSKey m_Key;
  int m_ObjectType;

  int m_MethodId;
  std::string m_MethodArgs;

  DDSKey m_ResponderKey;
  int m_ResponderObjectType;
  int m_ResponderMethodId;

  std::string m_ReturnArg;
};


