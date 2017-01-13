#pragma once

#include <string>

#include "DDSKey.h"

#include <StormRefl/StormRefl.h>

static const int kSubSentValid = 1;
static const int kSubUnsent = 0;
static const int kSubSentInvalid = -1;

struct DDSExportedSubscription
{
  STORM_REFL;
  std::string m_DataPath;
  DDSKey m_SubscriptionId;

  DDSKey m_ResponderKey;
  int m_ResponderObjectType;
  int m_ResponderMethodId;
  int m_ErrorMethodId;
  std::string m_ResponderArgs;

  bool m_IsDataSubscription;
  bool m_DeltaOnly;
  bool m_ForceLoad;
  int m_State;
};

struct DDSExportedRequestedSubscription
{
  STORM_REFL;
  DDSKey m_Key;
  int m_ObjectType;

  DDSKey m_SubscriptionId;
};


struct DDSTargetedMessageBase
{
  STORM_REFL;
  DDSKey m_Key;
  int m_ObjectType;

  int m_MethodId;
  std::string m_MethodArgs;
};

struct DDSTargetedMessageWithResponderBase
{
  STORM_REFL;
  DDSKey m_Key;
  int m_ObjectType;

  int m_MethodId;
  std::string m_MethodArgs;

  int m_ResponderObjectType;
  DDSKey m_ResponderKey;
  int m_ResponderMethodId;
  int m_ErrorMethodId;

  std::string m_ReturnArg;
};

struct DDSResponderCallBase
{
  STORM_REFL;
  DDSKey m_Key;
  int m_ObjectType;

  int m_MethodId;
  std::string m_ResponderArgs;
  std::string m_MethodArgs;
};


struct DDSCreateSubscriptionBase
{
  STORM_REFL;

  std::string m_DataPath;

  DDSKey m_Key;
  int m_ObjectType;
  DDSKey m_SubscriptionId;

  int m_ResponderObjectType;
  DDSKey m_ResponderKey;
  int m_ResponderMethodId;
  int m_ErrorMethodId;
  std::string m_ReturnArg;

  bool m_DataSubscription;
  bool m_DeltaOnly;
  bool m_ForceLoad;
};

struct DDSDestroySubscriptionBase
{
  STORM_REFL;

  DDSKey m_Key;
  int m_ObjectType;
  DDSKey m_SubscriptionId;
};

struct DDSSubscriptionDeletedBase
{
  STORM_REFL;

  DDSKey m_Key;
  int m_ObjectType;
  DDSKey m_SubscriptionId;
};

struct DDSValidateTokenRequestBase
{
  STORM_REFL;
  uint64_t m_RequestId;
  uint32_t m_Token;
  int m_Type;
};

struct DDSValidateTokenResponseBase
{
  STORM_REFL;
  uint64_t m_RequestId;
  bool m_Success;
  std::string m_TokenData;
};
