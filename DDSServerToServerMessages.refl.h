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
  kCreateSubscription,
  kCreateDataSubscription,
  kDestroySubscription,
  kSubscriptionDeleted
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

struct DDSExportedSubscription
{
  STORM_REFL;
  std::string m_DataPath;
  DDSKey m_SubscriptionId;

  DDSKey m_ResponderKey;
  int m_ResponderObjectType;
  int m_ResponderMethodId;
  std::string m_ResponderArgs;

  bool m_IsDataSubscription;
  bool m_DeltaOnly;
};

struct DDSExportedRequestedSubscription
{
  STORM_REFL;
  DDSKey m_Key;
  int m_ObjectType;

  DDSKey m_SubscriptionId;
};

struct DDSExportedObject
{
  STORM_REFL;
  DDSKey m_Key;
  bool m_IsLoaded;
  std::string m_ActiveObject;
  std::string m_DatabaseObject;

  std::vector<DDSExportedMessage> m_PendingMessages;
  std::vector<DDSExportedSubscription> m_Subscriptions;
  std::vector<DDSExportedRequestedSubscription> m_RequestedSubscriptions;
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
  std::string m_ResponderArgs;
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

  int m_ResponderObjectType;
  DDSKey m_ResponderKey;
  int m_ResponderMethodId;

  std::string m_ReturnArg;
};

struct DDSCreateSubscription
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kCreateSubscription;

  std::string m_DataPath;

  DDSKey m_Key;
  int m_ObjectType;
  DDSKey m_SubscriptionId;
  
  int m_ResponderObjectType;
  DDSKey m_ResponderKey;
  int m_ResponderMethodId;
  std::string m_ReturnArg;

  bool m_DeltaOnly;
};

struct DDSCreateDataSubscription : public DDSCreateSubscription
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kCreateDataSubscription;
};

struct DDSDestroySubscription
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kDestroySubscription;

  DDSKey m_Key;
  int m_ObjectType;
  DDSKey m_SubscriptionId;
};

struct DDSSubscriptionDeleted
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kSubscriptionDeleted;

  int m_ResponderObjectType;
  DDSKey m_ResponderKey;
  int m_ResponderMethodId;
  DDSKey m_SubscriptionId;
};

