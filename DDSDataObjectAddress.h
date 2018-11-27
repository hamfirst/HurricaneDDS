#pragma once

#include <cstddef>

#include <hash/Hash64.h>

#include "DDSKey.h"

struct DDSDataObjectAddress
{
  int m_ObjectType;
  DDSKey m_ObjectKey;

  bool operator == (const DDSDataObjectAddress & rhs) const
  {
    return m_ObjectType == rhs.m_ObjectType && m_ObjectKey == rhs.m_ObjectKey;
  }

  bool operator < (const DDSDataObjectAddress & rhs) const
  {
    if (m_ObjectKey < rhs.m_ObjectKey)
    {
      return true;
    }

    if (m_ObjectKey > rhs.m_ObjectKey)
    {
      return false;
    }

    return m_ObjectType < rhs.m_ObjectType;
  }
};

struct DDSDataObjectMethodAddress
{
  int m_ObjectType;
  DDSKey m_ObjectKey;

  int m_MethodId;

  bool operator == (const DDSDataObjectMethodAddress & rhs) const
  {
    return m_ObjectType == rhs.m_ObjectType && m_ObjectKey == rhs.m_ObjectKey && m_MethodId == rhs.m_MethodId;
  }

  bool operator < (const DDSDataObjectMethodAddress & rhs) const
  {
    if (m_ObjectKey < rhs.m_ObjectKey)
    {
      return true;
    }

    if (m_ObjectType < rhs.m_ObjectType)
    {
      return true;
    }

    return m_MethodId < rhs.m_MethodId;
  }
};
