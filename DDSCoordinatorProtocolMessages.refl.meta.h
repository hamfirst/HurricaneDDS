#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "DDSCoordinatorProtocolMessages.refl.h"
#include "DDSSharedMessages.refl.meta.h"
#include "StormData\StormDataChangeType.refl.meta.h"


template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>
{
  static constexpr int elems_n = 16;
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
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<6>
{
  static constexpr auto GetName() { return "kSharedObjectDelta"; }
  static constexpr auto GetNameHash() { return 0x91EF90EE; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kSharedObjectDelta; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<7>
{
  static constexpr auto GetName() { return "kResponderCall"; }
  static constexpr auto GetNameHash() { return 0x5055B576; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kResponderCall; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<8>
{
  static constexpr auto GetName() { return "kTargetedMessage"; }
  static constexpr auto GetNameHash() { return 0x3440F0A6; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kTargetedMessage; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<9>
{
  static constexpr auto GetName() { return "kTargetedMessageResponder"; }
  static constexpr auto GetNameHash() { return 0x2460C571; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kTargetedMessageResponder; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<10>
{
  static constexpr auto GetName() { return "kCreateSubscription"; }
  static constexpr auto GetNameHash() { return 0x6587A6A6; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kCreateSubscription; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<11>
{
  static constexpr auto GetName() { return "kCreateDataSubscription"; }
  static constexpr auto GetNameHash() { return 0x1B0ACF16; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kCreateDataSubscription; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<12>
{
  static constexpr auto GetName() { return "kCreateExistSubscription"; }
  static constexpr auto GetNameHash() { return 0xF5D37338; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kCreateExistSubscription; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<13>
{
  static constexpr auto GetName() { return "kCreateDataExistSubscription"; }
  static constexpr auto GetNameHash() { return 0x620781BB; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kCreateDataExistSubscription; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<14>
{
  static constexpr auto GetName() { return "kDestroySubscription"; }
  static constexpr auto GetNameHash() { return 0xF053A8EC; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kDestroySubscription; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<15>
{
  static constexpr auto GetName() { return "kSubscriptionDeleted"; }
  static constexpr auto GetNameHash() { return 0xA823DCCA; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kSubscriptionDeleted; }
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
  static constexpr int fields_n = 5;
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

template <>
struct StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data_static<4>
{
  using member_type = std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >;
  static constexpr auto GetName() { return "m_SharedObjects"; }
  static constexpr auto GetType() { return "std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF6FB05AB; }
  static constexpr unsigned GetTypeNameHash() { return 0x89A3A511; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorNodeInitialization::m_SharedObjects; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data<4, Self> : public StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >> & Get() { return self.m_SharedObjects; }
  std::add_const_t<std::remove_reference_t<std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >>> & Get() const { return self.m_SharedObjects; }
  void SetDefault() { self.m_SharedObjects = StormReflTypeInfo<DDSCoordinatorNodeInitialization>::GetDefault().m_SharedObjects; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>
{
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSCoordinatorSharedObjectDeltaMessage"; }
  static constexpr auto GetNameHash() { return 0xCB12480F; }
  static DDSCoordinatorSharedObjectDeltaMessage & GetDefault() { static DDSCoordinatorSharedObjectDeltaMessage def; return def; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::field_data_static<0>
{
  using member_type = ReflectionNotifyChangeType;
  static constexpr auto GetName() { return "m_Type"; }
  static constexpr auto GetType() { return "ReflectionNotifyChangeType"; }
  static constexpr unsigned GetFieldNameHash() { return 0x70F58FB9; }
  static constexpr unsigned GetTypeNameHash() { return 0x93A22823; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorSharedObjectDeltaMessage::m_Type; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::field_data<0, Self> : public StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, ReflectionNotifyChangeType> & Get() { return self.m_Type; }
  std::add_const_t<std::remove_reference_t<ReflectionNotifyChangeType>> & Get() const { return self.m_Type; }
  void SetDefault() { self.m_Type = StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::GetDefault().m_Type; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::field_data_static<1>
{
  using member_type = std::basic_string<char, std::char_traits<char>, std::allocator<char> >;
  static constexpr auto GetName() { return "m_Path"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7E0D518E; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorSharedObjectDeltaMessage::m_Path; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::field_data<1, Self> : public StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::basic_string<char, std::char_traits<char>, std::allocator<char> >> & Get() { return self.m_Path; }
  std::add_const_t<std::remove_reference_t<std::basic_string<char, std::char_traits<char>, std::allocator<char> >>> & Get() const { return self.m_Path; }
  void SetDefault() { self.m_Path = StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::GetDefault().m_Path; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::field_data_static<2>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_Index"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x333B1BA6; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorSharedObjectDeltaMessage::m_Index; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::field_data<2, Self> : public StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_Index; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_Index; }
  void SetDefault() { self.m_Index = StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::GetDefault().m_Index; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::field_data_static<3>
{
  using member_type = std::basic_string<char, std::char_traits<char>, std::allocator<char> >;
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDCF873D6; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorSharedObjectDeltaMessage::m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::field_data<3, Self> : public StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::basic_string<char, std::char_traits<char>, std::allocator<char> >> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<std::basic_string<char, std::char_traits<char>, std::allocator<char> >>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDelta>
{
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSCoordinatorSharedObjectDelta"; }
  static constexpr auto GetNameHash() { return 0xA44A093C; }
  static DDSCoordinatorSharedObjectDelta & GetDefault() { static DDSCoordinatorSharedObjectDelta def; return def; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDelta>::field_data_static<0>
{
  using member_type = int;
  static constexpr auto GetName() { return "m_SharedObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x87CF2170; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorSharedObjectDelta::m_SharedObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDelta>::field_data<0, Self> : public StormReflTypeInfo<DDSCoordinatorSharedObjectDelta>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_SharedObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_SharedObjectType; }
  void SetDefault() { self.m_SharedObjectType = StormReflTypeInfo<DDSCoordinatorSharedObjectDelta>::GetDefault().m_SharedObjectType; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDelta>::field_data_static<1>
{
  using member_type = std::vector<DDSCoordinatorSharedObjectDeltaMessage, std::allocator<DDSCoordinatorSharedObjectDeltaMessage> >;
  static constexpr auto GetName() { return "m_Deltas"; }
  static constexpr auto GetType() { return "std::vector<DDSCoordinatorSharedObjectDeltaMessage, std::allocator<DDSCoordinatorSharedObjectDeltaMessage> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x776270B2; }
  static constexpr unsigned GetTypeNameHash() { return 0xB773D52D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorSharedObjectDelta::m_Deltas; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDelta>::field_data<1, Self> : public StormReflTypeInfo<DDSCoordinatorSharedObjectDelta>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSCoordinatorSharedObjectDeltaMessage, std::allocator<DDSCoordinatorSharedObjectDeltaMessage> >> & Get() { return self.m_Deltas; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSCoordinatorSharedObjectDeltaMessage, std::allocator<DDSCoordinatorSharedObjectDeltaMessage> >>> & Get() const { return self.m_Deltas; }
  void SetDefault() { self.m_Deltas = StormReflTypeInfo<DDSCoordinatorSharedObjectDelta>::GetDefault().m_Deltas; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorResponderCallData>
{
  using MyBase = DDSResponderCallBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSCoordinatorResponderCallData"; }
  static constexpr auto GetNameHash() { return 0x5DB4F5CF; }
  static DDSCoordinatorResponderCallData & GetDefault() { static DDSCoordinatorResponderCallData def; return def; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorTargetedMessage>
{
  using MyBase = DDSTargetedMessageBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSCoordinatorTargetedMessage"; }
  static constexpr auto GetNameHash() { return 0xDF126A5C; }
  static DDSCoordinatorTargetedMessage & GetDefault() { static DDSCoordinatorTargetedMessage def; return def; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorTargetedMessageWithResponder>
{
  using MyBase = DDSTargetedMessageWithResponderBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSCoordinatorTargetedMessageWithResponder"; }
  static constexpr auto GetNameHash() { return 0x0FA24459; }
  static DDSCoordinatorTargetedMessageWithResponder & GetDefault() { static DDSCoordinatorTargetedMessageWithResponder def; return def; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorCreateSubscription>
{
  using MyBase = DDSCreateSubscriptionBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSCoordinatorCreateSubscription"; }
  static constexpr auto GetNameHash() { return 0xEC6128DF; }
  static DDSCoordinatorCreateSubscription & GetDefault() { static DDSCoordinatorCreateSubscription def; return def; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorCreateDataSubscription>
{
  using MyBase = DDSCreateDataSubscriptionBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSCoordinatorCreateDataSubscription"; }
  static constexpr auto GetNameHash() { return 0x641666E1; }
  static DDSCoordinatorCreateDataSubscription & GetDefault() { static DDSCoordinatorCreateDataSubscription def; return def; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorDestroySubscription>
{
  using MyBase = DDSDestroySubscriptionBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSCoordinatorDestroySubscription"; }
  static constexpr auto GetNameHash() { return 0xFADAE045; }
  static DDSCoordinatorDestroySubscription & GetDefault() { static DDSCoordinatorDestroySubscription def; return def; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorCreateExistSubscription>
{
  using MyBase = DDSCreateExistSubscriptionBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSCoordinatorCreateExistSubscription"; }
  static constexpr auto GetNameHash() { return 0x5AA674DD; }
  static DDSCoordinatorCreateExistSubscription & GetDefault() { static DDSCoordinatorCreateExistSubscription def; return def; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorCreateDataExistSubscription>
{
  using MyBase = DDSCreateDataExistSubscriptionBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSCoordinatorCreateDataExistSubscription"; }
  static constexpr auto GetNameHash() { return 0x6BF3DF9C; }
  static DDSCoordinatorCreateDataExistSubscription & GetDefault() { static DDSCoordinatorCreateDataExistSubscription def; return def; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorSubscriptionDeleted>
{
  using MyBase = DDSSubscriptionDeletedBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSCoordinatorSubscriptionDeleted"; }
  static constexpr auto GetNameHash() { return 0xA2AA9463; }
  static DDSCoordinatorSubscriptionDeleted & GetDefault() { static DDSCoordinatorSubscriptionDeleted def; return def; }
};

namespace StormReflFileInfo
{
  struct DDSCoordinatorProtocolMessages
  {
    static const int types_n = 15;
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

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<4>
  {
    using type = ::DDSCoordinatorSharedObjectDeltaMessage;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<5>
  {
    using type = ::DDSCoordinatorSharedObjectDelta;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<6>
  {
    using type = ::DDSCoordinatorResponderCallData;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<7>
  {
    using type = ::DDSCoordinatorTargetedMessage;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<8>
  {
    using type = ::DDSCoordinatorTargetedMessageWithResponder;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<9>
  {
    using type = ::DDSCoordinatorCreateSubscription;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<10>
  {
    using type = ::DDSCoordinatorCreateDataSubscription;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<11>
  {
    using type = ::DDSCoordinatorDestroySubscription;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<12>
  {
    using type = ::DDSCoordinatorCreateExistSubscription;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<13>
  {
    using type = ::DDSCoordinatorCreateDataExistSubscription;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<14>
  {
    using type = ::DDSCoordinatorSubscriptionDeleted;
  };

}

