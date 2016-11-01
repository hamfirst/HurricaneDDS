#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "DDSResponder.refl.h"


template <>
struct StormReflTypeInfo<DDSResponderData>
{
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSResponderData"; }
  static constexpr auto GetNameHash() { return 0xA9791E88; }
  static DDSResponderData & GetDefault() { static DDSResponderData def; return def; }
};

template <>
struct StormReflTypeInfo<DDSResponderData>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDC126BCE; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSResponderData::m_Key; }
};

template <typename Self>
struct StormReflTypeInfo<DDSResponderData>::field_data<0, Self> : public StormReflTypeInfo<DDSResponderData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSResponderData>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSResponderData>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD2FBD4E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSResponderData::m_ObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSResponderData>::field_data<1, Self> : public StormReflTypeInfo<DDSResponderData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ObjectType; }
  void SetDefault() { self.m_ObjectType = StormReflTypeInfo<DDSResponderData>::GetDefault().m_ObjectType; }
};

template <>
struct StormReflTypeInfo<DDSResponderData>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ReturnMethodId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x51B94839; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSResponderData::m_ReturnMethodId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSResponderData>::field_data<2, Self> : public StormReflTypeInfo<DDSResponderData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ReturnMethodId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ReturnMethodId; }
  void SetDefault() { self.m_ReturnMethodId = StormReflTypeInfo<DDSResponderData>::GetDefault().m_ReturnMethodId; }
};

template <>
struct StormReflTypeInfo<DDSResponderData>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ReturnArg"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBA1409C0; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSResponderData::m_ReturnArg; }
};

template <typename Self>
struct StormReflTypeInfo<DDSResponderData>::field_data<3, Self> : public StormReflTypeInfo<DDSResponderData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ReturnArg; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ReturnArg; }
  void SetDefault() { self.m_ReturnArg = StormReflTypeInfo<DDSResponderData>::GetDefault().m_ReturnArg; }
};

namespace StormReflFileInfo
{
  struct DDSResponder
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct DDSResponder::type_info<0>
  {
    using type = ::DDSResponderData;
  };

}

