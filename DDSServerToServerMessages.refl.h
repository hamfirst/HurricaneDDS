#pragma once

#include <StormRefl/StormRefl.h>

#include <string>
#include <vector>

#include "DDSNodeId.h"
#include "DDSKey.h"

#include "DDSResponder.refl.h"
#include "DDSSharedMessages.refl.h"

enum STORM_REFL_ENUM class DDSServerToServerMessageType
{
  kHandshakeRequest,
  kHandshakeResponse,
  kHandshakeFinalize,
  kDataObjectListSync,
  kUnlockObject,
  kResponderCall,
  kTargetedMessage,
  kTargetedMessageResponder,
  kCreateSubscription,
  kDestroySubscription,
  kSubscriptionDeleted,
  kValidateTokenRequest,
  kValidateTokenResponse,
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
  DDSServerToServerMessageType m_Type;
  std::string m_Message;
};

enum STORM_REFL_ENUM class DDSExportedObjectState
{
  kNotLoaded,
  kLoaded,
  kLocked,
};

struct DDSExportedObject
{
  STORM_REFL;
  DDSKey m_Key;
  DDSExportedObjectState m_State;
  std::string m_ActiveObject;
  std::string m_DatabaseObject;

  std::vector<DDSExportedMessage> m_PendingMessages;
  std::vector<DDSExportedSubscription> m_Subscriptions;
  std::vector<DDSExportedRequestedSubscription> m_RequestedSubscriptions;

  std::vector<std::pair<int, std::vector<DDSExportedSubscription>>> m_SharedSubscriptions;
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

struct DDSUnlockObject
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kUnlockObject;
  DDSKey m_Key;
  int m_ObjectType;
  std::string m_Data;
};

struct DDSResponderCallData : public DDSResponderCallBase
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kResponderCall;
};

struct DDSTargetedMessage : public DDSTargetedMessageBase
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kTargetedMessage;
};

struct DDSTargetedMessageWithResponder : public DDSTargetedMessageWithResponderBase
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kTargetedMessageResponder;
};

struct DDSCreateSubscription : public DDSCreateSubscriptionBase
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kCreateSubscription;
};

struct DDSDestroySubscription : public DDSDestroySubscriptionBase
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kDestroySubscription;
};

struct DDSSubscriptionDeleted : public DDSSubscriptionDeletedBase
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kSubscriptionDeleted;
};

struct DDSValidateTokenRequest : public DDSValidateTokenRequestBase
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kValidateTokenRequest;
};

struct DDSValidateTokenResponse : public DDSValidateTokenResponseBase
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kValidateTokenResponse;
};
