#pragma once

#include <string>

#include "DDSKey.h"

#include <StormRefl/StormRefl.h>


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
  std::string m_ReturnArg;

  bool m_DeltaOnly;
};

struct DDSCreateDataSubscriptionBase : public DDSCreateSubscriptionBase
{
  STORM_REFL;
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

  int m_ResponderObjectType;
  DDSKey m_ResponderKey;
  int m_ResponderMethodId;
  DDSKey m_SubscriptionId;
};


struct DDSCreateExistSubscriptionBase
{
  STORM_REFL;

  DDSKey m_Key;
  int m_ObjectType;
  DDSKey m_SubscriptionId;

  int m_ResponderObjectType;
  DDSKey m_ResponderKey;
  int m_ResponderMethodId;
  std::string m_ReturnArg;
};

struct DDSCreateDataExistSubscriptionBase : public DDSCreateExistSubscriptionBase
{
  STORM_REFL;
};

