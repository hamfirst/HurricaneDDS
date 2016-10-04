#pragma once

#include <cstddef>

#include <hash\Hash64.h>

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

    return m_ObjectType < rhs.m_ObjectType;
  }
};

struct DDSDataObjectAddressHash
{
  std::size_t operator()(const DDSDataObjectAddress & addr) const
  {
    return (std::size_t)addr.m_ObjectKey ^ crc64_table[addr.m_ObjectType & 0xFF];
  }
};
