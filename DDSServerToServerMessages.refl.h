#pragma once

#include <StormRefl/StormRefl.h>

#include <string>
#include <vector>
#include <map>

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
  kCreateSharedLocalCopySubscription,
  kDestroySharedLocalCopySubscription,
  kSharedLocalCopyInit,
  kSharedLocalCopyHostDestroyed,
  kSharedLocalCopyChange,
  kSharedLocalCopyFastForward,
  kSharedLocalCopyAck,
  kSharedLocalCopyDatabaseDump,
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

struct DDSExportedAggregateSubscriptionChange
{
  STORM_REFL;
  std::string m_Change;
  int m_DataGen;
  std::vector<std::pair<DDSNodeId, DDSKey>> m_PendingAckNodes;
  int m_WaitForAllClearGen;
};

struct DDSExportedAggregateSubscription
{
  STORM_REFL;

  DDSKey m_SharedLocalCopyKey;

  std::vector<DDSExportedAggregateSubscriptionChange> m_Changes;
  std::vector<std::pair<DDSNodeId, DDSKey>> m_SubscribedNodes;

  std::string m_DataPath;

  bool m_HasChangesWaiting;
  bool m_DataSubscription;
};

struct DDSExportedObject
{
  STORM_REFL;
  DDSKey m_Key;
  DDSExportedObjectState m_State;
  std::string m_ActiveObject;
  std::string m_DatabaseObject;

  int m_ObjectDataGen;
  int m_DatabaseDataGen;

  std::vector<DDSExportedMessage> m_PendingMessages;
  std::vector<DDSExportedSubscription> m_Subscriptions;
  std::vector<DDSExportedRequestedSubscription> m_RequestedSubscriptions;

  std::vector<DDSExportedAggregateSubscription> m_AggregateSubscriptions;
  std::vector<DDSExportedAggregateRequestedSubscription> m_RequestedAggregateSubscriptions;

  std::vector<std::pair<int, std::vector<DDSExportedSubscription>>> m_SharedSubscriptions;
};

struct DDSDataObjectListSync
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kDataObjectListSync;

  DDSNodeId m_TargetNode;
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

struct DDSCreateSharedLocalCopySubscription
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kCreateSharedLocalCopySubscription;

  DDSKey m_Key;
  int m_ObjectType;
  DDSKey m_SharedLocalCopyKey;
  DDSKey m_SubscriptionId;
  std::string m_DataPath;
  bool m_DataSubscription;
  int m_DataGen;
  DDSNodeId m_ReturnNode;
};

struct DDSDestroySharedLocalCopySubscription
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kDestroySharedLocalCopySubscription;

  DDSKey m_Key;
  int m_ObjectType;
  DDSKey m_SharedLocalCopyKey;
  DDSKey m_SubscriptionId;
};

struct DDSSharedLocalCopyInit
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kSharedLocalCopyInit;

  DDSKey m_SharedLocalCopyKey;
  DDSKey m_SubscriptionId;
  std::string m_Data;
  int m_DataGen;
};


struct DDSSharedLocalCopyHostDestroyed
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kSharedLocalCopyHostDestroyed;

  DDSKey m_SharedLocalCopy;
  DDSKey m_SubscriptionId;
};

struct DDSSharedLocalCopyChange
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kSharedLocalCopyChange;

  DDSKey m_SharedLocalCopy;
  DDSKey m_SubscriptionId;
  std::string m_Change;
  int m_DataGen;
};

struct DDSSharedLocalCopyFastForward
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kSharedLocalCopyFastForward;

  DDSKey m_SharedLocalCopy;
  DDSKey m_SubscriptionId;
  std::vector<std::pair<int, std::string>> m_Changes;
  int m_DataGen;
};

struct DDSSharedLocalCopyAck
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kSharedLocalCopyAck;

  DDSKey m_Key;
  int m_ObjectType;
  DDSKey m_SharedLocalCopy;
  DDSKey m_SubscriptionId;
  DDSNodeId m_NodeId;
  int m_DataGen;
  int m_RoutingTableGen;
};

struct DDSSharedLocalCopyDatabaseElem
{
  STORM_REFL;
  int m_DataGen;
  std::string m_Data;
  bool m_DataSub;
  bool m_DataValid;

  DDSKey m_Key;
  int m_ObjectType;
  std::string m_Path;
};

struct DDSSharedLocalCopyDatabaseDump
{
  STORM_REFL;
  static const DDSServerToServerMessageType Type = DDSServerToServerMessageType::kSharedLocalCopyDatabaseDump;

  std::map<DDSKey, DDSSharedLocalCopyDatabaseElem> m_Copies;
};
