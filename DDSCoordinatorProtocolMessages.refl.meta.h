#pragma once

#include <StormRefl\StormReflMetaInfoBase.h>

#include "DDSCoordinatorProtocolMessages.refl.h"


template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>
{
  static constexpr int elems_n = 6;
  static constexpr auto GetName() { return "DDSCoordinatorProtocolMessageType"; }
  static constexpr auto GetNameHash() { return 0xD880A841; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<0>
{
  static constexpr auto GetName() { return "kUnknown"; }
  static constexpr auto GetNameHash() { return 0x3821395E; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kUnknown; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<1>
{
  static constexpr auto GetName() { return "kHandshakeRequest"; }
  static constexpr auto GetNameHash() { return 0x2D003D50; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kHandshakeRequest; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<2>
{
  static constexpr auto GetName() { return "kHandshakeResponse"; }
  static constexpr auto GetNameHash() { return 0x6B81B797; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kHandshakeResponse; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<3>
{
  static constexpr auto GetName() { return "kHandshakeFinalize"; }
  static constexpr auto GetNameHash() { return 0xA8E749CB; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kHandshakeFinalize; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<4>
{
  static constexpr auto GetName() { return "kNodeInit"; }
  static constexpr auto GetNameHash() { return 0xC5B8CE24; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kNodeInit; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<5>
{
  static constexpr auto GetName() { return "kRoutingTable"; }
  static constexpr auto GetNameHash() { return 0x32EF9EFC; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kRoutingTable; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorHandshakeRequest>
{
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSCoordinatorHandshakeRequest"; }
  static constexpr auto GetNameHash() { return 0x3D311590; }
  static DDSCoordinatorHandshakeRequest & GetDefault() { static DDSCoordinatorHandshakeRequest def; return def; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorHandshakeRequest>::field_data_static<0>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_Challenge"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAAD47102; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorHandshakeRequest::m_Challenge; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorHandshakeRequest>::field_data<0, Self> : public StormReflTypeInfo<DDSCoordinatorHandshakeRequest>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_Challenge; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_Challenge; }
  void SetDefault() { self.m_Challenge = StormReflTypeInfo<DDSCoordinatorHandshakeRequest>::GetDefault().m_Challenge; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorHandshakeRequest>::field_data_static<1>
{
  using member_type = int;
  static constexpr auto GetName() { return "m_Version"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB7B5D57D; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorHandshakeRequest::m_Version; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorHandshakeRequest>::field_data<1, Self> : public StormReflTypeInfo<DDSCoordinatorHandshakeRequest>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Version; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Version; }
  void SetDefault() { self.m_Version = StormReflTypeInfo<DDSCoordinatorHandshakeRequest>::GetDefault().m_Version; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorHandshakeResponse>
{
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSCoordinatorHandshakeResponse"; }
  static constexpr auto GetNameHash() { return 0x5E242E45; }
  static DDSCoordinatorHandshakeResponse & GetDefault() { static DDSCoordinatorHandshakeResponse def; return def; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorHandshakeResponse>::field_data_static<0>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_ChallengeResponse"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC11383A6; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorHandshakeResponse::m_ChallengeResponse; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorHandshakeResponse>::field_data<0, Self> : public StormReflTypeInfo<DDSCoordinatorHandshakeResponse>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_ChallengeResponse; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_ChallengeResponse; }
  void SetDefault() { self.m_ChallengeResponse = StormReflTypeInfo<DDSCoordinatorHandshakeResponse>::GetDefault().m_ChallengeResponse; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorHandshakeResponse>::field_data_static<1>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_ChallengeRequest"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB57853AE; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorHandshakeResponse::m_ChallengeRequest; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorHandshakeResponse>::field_data<1, Self> : public StormReflTypeInfo<DDSCoordinatorHandshakeResponse>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_ChallengeRequest; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_ChallengeRequest; }
  void SetDefault() { self.m_ChallengeRequest = StormReflTypeInfo<DDSCoordinatorHandshakeResponse>::GetDefault().m_ChallengeRequest; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>
{
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSCoordinatorHandshakeFinalize"; }
  static constexpr auto GetNameHash() { return 0x9D42D019; }
  static DDSCoordinatorHandshakeFinalize & GetDefault() { static DDSCoordinatorHandshakeFinalize def; return def; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data_static<0>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_ChallengeResponse"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC11383A6; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorHandshakeFinalize::m_ChallengeResponse; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data<0, Self> : public StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_ChallengeResponse; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_ChallengeResponse; }
  void SetDefault() { self.m_ChallengeResponse = StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::GetDefault().m_ChallengeResponse; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data_static<1>
{
  using member_type = unsigned int;
  static constexpr auto GetName() { return "m_PublicIp"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x58C48A0A; }
  static constexpr unsigned GetTypeNameHash() { return 0xB306EEF4; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorHandshakeFinalize::m_PublicIp; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data<1, Self> : public StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned int> & Get() { return self.m_PublicIp; }
  std::add_const_t<std::remove_reference_t<unsigned int>> & Get() const { return self.m_PublicIp; }
  void SetDefault() { self.m_PublicIp = StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::GetDefault().m_PublicIp; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data_static<2>
{
  using member_type = unsigned short;
  static constexpr auto GetName() { return "m_PublicPort"; }
  static constexpr auto GetType() { return "unsigned short"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFBB22218; }
  static constexpr unsigned GetTypeNameHash() { return 0xFB128F18; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorHandshakeFinalize::m_PublicPort; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data<2, Self> : public StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned short> & Get() { return self.m_PublicPort; }
  std::add_const_t<std::remove_reference_t<unsigned short>> & Get() const { return self.m_PublicPort; }
  void SetDefault() { self.m_PublicPort = StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::GetDefault().m_PublicPort; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorNodeInitialization>
{
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSCoordinatorNodeInitialization"; }
  static constexpr auto GetNameHash() { return 0xEA3D5885; }
  static DDSCoordinatorNodeInitialization & GetDefault() { static DDSCoordinatorNodeInitialization def; return def; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data_static<0>
{
  using member_type = unsigned int;
  static constexpr auto GetName() { return "m_NodeId"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF341CF68; }
  static constexpr unsigned GetTypeNameHash() { return 0xB306EEF4; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorNodeInitialization::m_NodeId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data<0, Self> : public StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned int> & Get() { return self.m_NodeId; }
  std::add_const_t<std::remove_reference_t<unsigned int>> & Get() const { return self.m_NodeId; }
  void SetDefault() { self.m_NodeId = StormReflTypeInfo<DDSCoordinatorNodeInitialization>::GetDefault().m_NodeId; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data_static<1>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_ClientSecret"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4B40A040; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorNodeInitialization::m_ClientSecret; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data<1, Self> : public StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_ClientSecret; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_ClientSecret; }
  void SetDefault() { self.m_ClientSecret = StormReflTypeInfo<DDSCoordinatorNodeInitialization>::GetDefault().m_ClientSecret; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data_static<2>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_ServerSecret"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7C920E5B; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorNodeInitialization::m_ServerSecret; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data<2, Self> : public StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_ServerSecret; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_ServerSecret; }
  void SetDefault() { self.m_ServerSecret = StormReflTypeInfo<DDSCoordinatorNodeInitialization>::GetDefault().m_ServerSecret; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data_static<3>
{
  using member_type = bool;
  static constexpr auto GetName() { return "m_InitialNode"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB5C864BF; }
  static constexpr unsigned GetTypeNameHash() { return 0xA1B914E5; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorNodeInitialization::m_InitialNode; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data<3, Self> : public StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_InitialNode; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_InitialNode; }
  void SetDefault() { self.m_InitialNode = StormReflTypeInfo<DDSCoordinatorNodeInitialization>::GetDefault().m_InitialNode; }
};

namespace StormReflFileInfo
{
  struct DDSCoordinatorProtocolMessages
  {
    static const int types_n = 4;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<0>
  {
    using type = ::DDSCoordinatorHandshakeRequest;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<1>
  {
    using type = ::DDSCoordinatorHandshakeResponse;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<2>
  {
    using type = ::DDSCoordinatorHandshakeFinalize;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<3>
  {
    using type = ::DDSCoordinatorNodeInitialization;
  };

}

