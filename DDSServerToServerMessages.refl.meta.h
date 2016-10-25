#pragma once

#include <StormRefl\StormReflMetaInfoBase.h>

#include "DDSServerToServerMessages.refl.h"
#include "DDSResponder.refl.meta.h"
#include "DDSSharedMessages.refl.meta.h"


template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>
{
  static constexpr int elems_n = 14;
  static constexpr auto GetName() { return "DDSServerToServerMessageType"; }
  static constexpr auto GetNameHash() { return 0xBBFBB085; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<0>
{
  static constexpr auto GetName() { return "kHandshakeRequest"; }
  static constexpr auto GetNameHash() { return 0x2D003D50; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kHandshakeRequest; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<1>
{
  static constexpr auto GetName() { return "kHandshakeResponse"; }
  static constexpr auto GetNameHash() { return 0x6B81B797; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kHandshakeResponse; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<2>
{
  static constexpr auto GetName() { return "kHandshakeFinalize"; }
  static constexpr auto GetNameHash() { return 0xA8E749CB; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kHandshakeFinalize; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<3>
{
  static constexpr auto GetName() { return "kDataObjectListSync"; }
  static constexpr auto GetNameHash() { return 0x1B30D71B; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kDataObjectListSync; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<4>
{
  static constexpr auto GetName() { return "kUnlockObject"; }
  static constexpr auto GetNameHash() { return 0xF4594365; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kUnlockObject; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<5>
{
  static constexpr auto GetName() { return "kResponderCall"; }
  static constexpr auto GetNameHash() { return 0x5055B576; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kResponderCall; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<6>
{
  static constexpr auto GetName() { return "kTargetedMessage"; }
  static constexpr auto GetNameHash() { return 0x3440F0A6; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kTargetedMessage; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<7>
{
  static constexpr auto GetName() { return "kTargetedMessageResponder"; }
  static constexpr auto GetNameHash() { return 0x2460C571; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kTargetedMessageResponder; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<8>
{
  static constexpr auto GetName() { return "kCreateSubscription"; }
  static constexpr auto GetNameHash() { return 0x6587A6A6; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kCreateSubscription; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<9>
{
  static constexpr auto GetName() { return "kCreateDataSubscription"; }
  static constexpr auto GetNameHash() { return 0x1B0ACF16; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kCreateDataSubscription; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<10>
{
  static constexpr auto GetName() { return "kCreateExistSubscription"; }
  static constexpr auto GetNameHash() { return 0xF5D37338; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kCreateExistSubscription; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<11>
{
  static constexpr auto GetName() { return "kCreateDataExistSubscription"; }
  static constexpr auto GetNameHash() { return 0x620781BB; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kCreateDataExistSubscription; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<12>
{
  static constexpr auto GetName() { return "kDestroySubscription"; }
  static constexpr auto GetNameHash() { return 0xF053A8EC; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kDestroySubscription; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<13>
{
  static constexpr auto GetName() { return "kSubscriptionDeleted"; }
  static constexpr auto GetNameHash() { return 0xA823DCCA; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kSubscriptionDeleted; }
};

template <>
struct StormReflEnumInfo<DDSExportedObjectState>
{
  static constexpr int elems_n = 3;
  static constexpr auto GetName() { return "DDSExportedObjectState"; }
  static constexpr auto GetNameHash() { return 0x06539669; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<DDSExportedObjectState>::elems<0>
{
  static constexpr auto GetName() { return "kNotLoaded"; }
  static constexpr auto GetNameHash() { return 0xD4D9EBB3; }
  static constexpr auto GetValue() { return DDSExportedObjectState::kNotLoaded; }
};

template <>
struct StormReflEnumInfo<DDSExportedObjectState>::elems<1>
{
  static constexpr auto GetName() { return "kLoaded"; }
  static constexpr auto GetNameHash() { return 0xA4F50A39; }
  static constexpr auto GetValue() { return DDSExportedObjectState::kLoaded; }
};

template <>
struct StormReflEnumInfo<DDSExportedObjectState>::elems<2>
{
  static constexpr auto GetName() { return "kLocked"; }
  static constexpr auto GetNameHash() { return 0x38647454; }
  static constexpr auto GetValue() { return DDSExportedObjectState::kLocked; }
};

template <>
struct StormReflTypeInfo<DDSServerToServerHandshakeRequest>
{
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSServerToServerHandshakeRequest"; }
  static constexpr auto GetNameHash() { return 0x1874AB82; }
  static DDSServerToServerHandshakeRequest & GetDefault() { static DDSServerToServerHandshakeRequest def; return def; }
};

template <>
struct StormReflTypeInfo<DDSServerToServerHandshakeRequest>::field_data_static<0>
{
  using member_type = int;
  static constexpr auto GetName() { return "m_Version"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB7B5D57D; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSServerToServerHandshakeRequest::m_Version; }
};

template <typename Self>
struct StormReflTypeInfo<DDSServerToServerHandshakeRequest>::field_data<0, Self> : public StormReflTypeInfo<DDSServerToServerHandshakeRequest>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Version; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Version; }
  void SetDefault() { self.m_Version = StormReflTypeInfo<DDSServerToServerHandshakeRequest>::GetDefault().m_Version; }
};

template <>
struct StormReflTypeInfo<DDSServerToServerHandshakeRequest>::field_data_static<1>
{
  using member_type = unsigned int;
  static constexpr auto GetName() { return "m_NodeId"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF341CF68; }
  static constexpr unsigned GetTypeNameHash() { return 0xB306EEF4; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSServerToServerHandshakeRequest::m_NodeId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSServerToServerHandshakeRequest>::field_data<1, Self> : public StormReflTypeInfo<DDSServerToServerHandshakeRequest>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned int> & Get() { return self.m_NodeId; }
  std::add_const_t<std::remove_reference_t<unsigned int>> & Get() const { return self.m_NodeId; }
  void SetDefault() { self.m_NodeId = StormReflTypeInfo<DDSServerToServerHandshakeRequest>::GetDefault().m_NodeId; }
};

template <>
struct StormReflTypeInfo<DDSServerToServerHandshakeRequest>::field_data_static<2>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_Secret"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xADEEEE0E; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSServerToServerHandshakeRequest::m_Secret; }
};

template <typename Self>
struct StormReflTypeInfo<DDSServerToServerHandshakeRequest>::field_data<2, Self> : public StormReflTypeInfo<DDSServerToServerHandshakeRequest>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_Secret; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_Secret; }
  void SetDefault() { self.m_Secret = StormReflTypeInfo<DDSServerToServerHandshakeRequest>::GetDefault().m_Secret; }
};

template <>
struct StormReflTypeInfo<DDSServerToServerHandshakeRequest>::field_data_static<3>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_Challenge"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAAD47102; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSServerToServerHandshakeRequest::m_Challenge; }
};

template <typename Self>
struct StormReflTypeInfo<DDSServerToServerHandshakeRequest>::field_data<3, Self> : public StormReflTypeInfo<DDSServerToServerHandshakeRequest>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_Challenge; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_Challenge; }
  void SetDefault() { self.m_Challenge = StormReflTypeInfo<DDSServerToServerHandshakeRequest>::GetDefault().m_Challenge; }
};

template <>
struct StormReflTypeInfo<DDSServerToServerHandshakeResponse>
{
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSServerToServerHandshakeResponse"; }
  static constexpr auto GetNameHash() { return 0x72D8F570; }
  static DDSServerToServerHandshakeResponse & GetDefault() { static DDSServerToServerHandshakeResponse def; return def; }
};

template <>
struct StormReflTypeInfo<DDSServerToServerHandshakeResponse>::field_data_static<0>
{
  using member_type = unsigned int;
  static constexpr auto GetName() { return "m_NodeId"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF341CF68; }
  static constexpr unsigned GetTypeNameHash() { return 0xB306EEF4; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSServerToServerHandshakeResponse::m_NodeId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSServerToServerHandshakeResponse>::field_data<0, Self> : public StormReflTypeInfo<DDSServerToServerHandshakeResponse>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned int> & Get() { return self.m_NodeId; }
  std::add_const_t<std::remove_reference_t<unsigned int>> & Get() const { return self.m_NodeId; }
  void SetDefault() { self.m_NodeId = StormReflTypeInfo<DDSServerToServerHandshakeResponse>::GetDefault().m_NodeId; }
};

template <>
struct StormReflTypeInfo<DDSServerToServerHandshakeResponse>::field_data_static<1>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_Secret"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xADEEEE0E; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSServerToServerHandshakeResponse::m_Secret; }
};

template <typename Self>
struct StormReflTypeInfo<DDSServerToServerHandshakeResponse>::field_data<1, Self> : public StormReflTypeInfo<DDSServerToServerHandshakeResponse>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_Secret; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_Secret; }
  void SetDefault() { self.m_Secret = StormReflTypeInfo<DDSServerToServerHandshakeResponse>::GetDefault().m_Secret; }
};

template <>
struct StormReflTypeInfo<DDSServerToServerHandshakeResponse>::field_data_static<2>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_Challenge"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAAD47102; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSServerToServerHandshakeResponse::m_Challenge; }
};

template <typename Self>
struct StormReflTypeInfo<DDSServerToServerHandshakeResponse>::field_data<2, Self> : public StormReflTypeInfo<DDSServerToServerHandshakeResponse>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_Challenge; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_Challenge; }
  void SetDefault() { self.m_Challenge = StormReflTypeInfo<DDSServerToServerHandshakeResponse>::GetDefault().m_Challenge; }
};

template <>
struct StormReflTypeInfo<DDSServerToServerHandshakeResponse>::field_data_static<3>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_ChallengeResponse"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC11383A6; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSServerToServerHandshakeResponse::m_ChallengeResponse; }
};

template <typename Self>
struct StormReflTypeInfo<DDSServerToServerHandshakeResponse>::field_data<3, Self> : public StormReflTypeInfo<DDSServerToServerHandshakeResponse>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_ChallengeResponse; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_ChallengeResponse; }
  void SetDefault() { self.m_ChallengeResponse = StormReflTypeInfo<DDSServerToServerHandshakeResponse>::GetDefault().m_ChallengeResponse; }
};

template <>
struct StormReflTypeInfo<DDSServerToServerHandshakeFinalize>
{
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSServerToServerHandshakeFinalize"; }
  static constexpr auto GetNameHash() { return 0xB1BE0B2C; }
  static DDSServerToServerHandshakeFinalize & GetDefault() { static DDSServerToServerHandshakeFinalize def; return def; }
};

template <>
struct StormReflTypeInfo<DDSServerToServerHandshakeFinalize>::field_data_static<0>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_Challenge"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xAAD47102; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSServerToServerHandshakeFinalize::m_Challenge; }
};

template <typename Self>
struct StormReflTypeInfo<DDSServerToServerHandshakeFinalize>::field_data<0, Self> : public StormReflTypeInfo<DDSServerToServerHandshakeFinalize>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_Challenge; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_Challenge; }
  void SetDefault() { self.m_Challenge = StormReflTypeInfo<DDSServerToServerHandshakeFinalize>::GetDefault().m_Challenge; }
};

template <>
struct StormReflTypeInfo<DDSExportedMessage>
{
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSExportedMessage"; }
  static constexpr auto GetNameHash() { return 0xD53B7AF5; }
  static DDSExportedMessage & GetDefault() { static DDSExportedMessage def; return def; }
};

template <>
struct StormReflTypeInfo<DDSExportedMessage>::field_data_static<0>
{
  using member_type = DDSServerToServerMessageType;
  static constexpr auto GetName() { return "m_Type"; }
  static constexpr auto GetType() { return "DDSServerToServerMessageType"; }
  static constexpr unsigned GetFieldNameHash() { return 0x70F58FB9; }
  static constexpr unsigned GetTypeNameHash() { return 0xBBFBB085; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSExportedMessage::m_Type; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedMessage>::field_data<0, Self> : public StormReflTypeInfo<DDSExportedMessage>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSServerToServerMessageType> & Get() { return self.m_Type; }
  std::add_const_t<std::remove_reference_t<DDSServerToServerMessageType>> & Get() const { return self.m_Type; }
  void SetDefault() { self.m_Type = StormReflTypeInfo<DDSExportedMessage>::GetDefault().m_Type; }
};

template <>
struct StormReflTypeInfo<DDSExportedMessage>::field_data_static<1>
{
  using member_type = std::basic_string<char, std::char_traits<char>, std::allocator<char> >;
  static constexpr auto GetName() { return "m_Message"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD2BD02E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSExportedMessage::m_Message; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedMessage>::field_data<1, Self> : public StormReflTypeInfo<DDSExportedMessage>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::basic_string<char, std::char_traits<char>, std::allocator<char> >> & Get() { return self.m_Message; }
  std::add_const_t<std::remove_reference_t<std::basic_string<char, std::char_traits<char>, std::allocator<char> >>> & Get() const { return self.m_Message; }
  void SetDefault() { self.m_Message = StormReflTypeInfo<DDSExportedMessage>::GetDefault().m_Message; }
};

template <>
struct StormReflTypeInfo<DDSExportedSubscription>
{
  static constexpr int fields_n = 8;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSExportedSubscription"; }
  static constexpr auto GetNameHash() { return 0x37AB8B23; }
  static DDSExportedSubscription & GetDefault() { static DDSExportedSubscription def; return def; }
};

template <>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data_static<0>
{
  using member_type = std::basic_string<char, std::char_traits<char>, std::allocator<char> >;
  static constexpr auto GetName() { return "m_DataPath"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8780827D; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSExportedSubscription::m_DataPath; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data<0, Self> : public StormReflTypeInfo<DDSExportedSubscription>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::basic_string<char, std::char_traits<char>, std::allocator<char> >> & Get() { return self.m_DataPath; }
  std::add_const_t<std::remove_reference_t<std::basic_string<char, std::char_traits<char>, std::allocator<char> >>> & Get() const { return self.m_DataPath; }
  void SetDefault() { self.m_DataPath = StormReflTypeInfo<DDSExportedSubscription>::GetDefault().m_DataPath; }
};

template <>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data_static<1>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_SubscriptionId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x01DAA775; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSExportedSubscription::m_SubscriptionId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data<1, Self> : public StormReflTypeInfo<DDSExportedSubscription>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_SubscriptionId; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_SubscriptionId; }
  void SetDefault() { self.m_SubscriptionId = StormReflTypeInfo<DDSExportedSubscription>::GetDefault().m_SubscriptionId; }
};

template <>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data_static<2>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_ResponderKey"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x47BF66BE; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSExportedSubscription::m_ResponderKey; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data<2, Self> : public StormReflTypeInfo<DDSExportedSubscription>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_ResponderKey; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_ResponderKey; }
  void SetDefault() { self.m_ResponderKey = StormReflTypeInfo<DDSExportedSubscription>::GetDefault().m_ResponderKey; }
};

template <>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data_static<3>
{
  using member_type = int;
  static constexpr auto GetName() { return "m_ResponderObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6ECD8D43; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSExportedSubscription::m_ResponderObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data<3, Self> : public StormReflTypeInfo<DDSExportedSubscription>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ResponderObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ResponderObjectType; }
  void SetDefault() { self.m_ResponderObjectType = StormReflTypeInfo<DDSExportedSubscription>::GetDefault().m_ResponderObjectType; }
};

template <>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data_static<4>
{
  using member_type = int;
  static constexpr auto GetName() { return "m_ResponderMethodId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x28424F94; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSExportedSubscription::m_ResponderMethodId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data<4, Self> : public StormReflTypeInfo<DDSExportedSubscription>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ResponderMethodId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ResponderMethodId; }
  void SetDefault() { self.m_ResponderMethodId = StormReflTypeInfo<DDSExportedSubscription>::GetDefault().m_ResponderMethodId; }
};

template <>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data_static<5>
{
  using member_type = std::basic_string<char, std::char_traits<char>, std::allocator<char> >;
  static constexpr auto GetName() { return "m_ResponderArgs"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEE5C340B; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &DDSExportedSubscription::m_ResponderArgs; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data<5, Self> : public StormReflTypeInfo<DDSExportedSubscription>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::basic_string<char, std::char_traits<char>, std::allocator<char> >> & Get() { return self.m_ResponderArgs; }
  std::add_const_t<std::remove_reference_t<std::basic_string<char, std::char_traits<char>, std::allocator<char> >>> & Get() const { return self.m_ResponderArgs; }
  void SetDefault() { self.m_ResponderArgs = StormReflTypeInfo<DDSExportedSubscription>::GetDefault().m_ResponderArgs; }
};

template <>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data_static<6>
{
  using member_type = bool;
  static constexpr auto GetName() { return "m_IsDataSubscription"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDD36DB9E; }
  static constexpr unsigned GetTypeNameHash() { return 0xA1B914E5; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &DDSExportedSubscription::m_IsDataSubscription; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data<6, Self> : public StormReflTypeInfo<DDSExportedSubscription>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_IsDataSubscription; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_IsDataSubscription; }
  void SetDefault() { self.m_IsDataSubscription = StormReflTypeInfo<DDSExportedSubscription>::GetDefault().m_IsDataSubscription; }
};

template <>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data_static<7>
{
  using member_type = bool;
  static constexpr auto GetName() { return "m_DeltaOnly"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB3B163F9; }
  static constexpr unsigned GetTypeNameHash() { return 0xA1B914E5; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &DDSExportedSubscription::m_DeltaOnly; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data<7, Self> : public StormReflTypeInfo<DDSExportedSubscription>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_DeltaOnly; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_DeltaOnly; }
  void SetDefault() { self.m_DeltaOnly = StormReflTypeInfo<DDSExportedSubscription>::GetDefault().m_DeltaOnly; }
};

template <>
struct StormReflTypeInfo<DDSExportedRequestedSubscription>
{
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSExportedRequestedSubscription"; }
  static constexpr auto GetNameHash() { return 0x3F684543; }
  static DDSExportedRequestedSubscription & GetDefault() { static DDSExportedRequestedSubscription def; return def; }
};

template <>
struct StormReflTypeInfo<DDSExportedRequestedSubscription>::field_data_static<0>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDC126BCE; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSExportedRequestedSubscription::m_Key; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedRequestedSubscription>::field_data<0, Self> : public StormReflTypeInfo<DDSExportedRequestedSubscription>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSExportedRequestedSubscription>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSExportedRequestedSubscription>::field_data_static<1>
{
  using member_type = int;
  static constexpr auto GetName() { return "m_ObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD2FBD4E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSExportedRequestedSubscription::m_ObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedRequestedSubscription>::field_data<1, Self> : public StormReflTypeInfo<DDSExportedRequestedSubscription>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ObjectType; }
  void SetDefault() { self.m_ObjectType = StormReflTypeInfo<DDSExportedRequestedSubscription>::GetDefault().m_ObjectType; }
};

template <>
struct StormReflTypeInfo<DDSExportedRequestedSubscription>::field_data_static<2>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_SubscriptionId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x01DAA775; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSExportedRequestedSubscription::m_SubscriptionId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedRequestedSubscription>::field_data<2, Self> : public StormReflTypeInfo<DDSExportedRequestedSubscription>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_SubscriptionId; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_SubscriptionId; }
  void SetDefault() { self.m_SubscriptionId = StormReflTypeInfo<DDSExportedRequestedSubscription>::GetDefault().m_SubscriptionId; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>
{
  static constexpr int fields_n = 8;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSExportedObject"; }
  static constexpr auto GetNameHash() { return 0x4444973D; }
  static DDSExportedObject & GetDefault() { static DDSExportedObject def; return def; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<0>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDC126BCE; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_Key; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<0, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<1>
{
  using member_type = DDSExportedObjectState;
  static constexpr auto GetName() { return "m_State"; }
  static constexpr auto GetType() { return "DDSExportedObjectState"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB52C29BF; }
  static constexpr unsigned GetTypeNameHash() { return 0x06539669; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_State; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<1, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSExportedObjectState> & Get() { return self.m_State; }
  std::add_const_t<std::remove_reference_t<DDSExportedObjectState>> & Get() const { return self.m_State; }
  void SetDefault() { self.m_State = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_State; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<2>
{
  using member_type = std::basic_string<char, std::char_traits<char>, std::allocator<char> >;
  static constexpr auto GetName() { return "m_ActiveObject"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6353F0E6; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_ActiveObject; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<2, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::basic_string<char, std::char_traits<char>, std::allocator<char> >> & Get() { return self.m_ActiveObject; }
  std::add_const_t<std::remove_reference_t<std::basic_string<char, std::char_traits<char>, std::allocator<char> >>> & Get() const { return self.m_ActiveObject; }
  void SetDefault() { self.m_ActiveObject = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_ActiveObject; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<3>
{
  using member_type = std::basic_string<char, std::char_traits<char>, std::allocator<char> >;
  static constexpr auto GetName() { return "m_DatabaseObject"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x133A1F6C; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_DatabaseObject; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<3, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::basic_string<char, std::char_traits<char>, std::allocator<char> >> & Get() { return self.m_DatabaseObject; }
  std::add_const_t<std::remove_reference_t<std::basic_string<char, std::char_traits<char>, std::allocator<char> >>> & Get() const { return self.m_DatabaseObject; }
  void SetDefault() { self.m_DatabaseObject = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_DatabaseObject; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<4>
{
  using member_type = std::vector<DDSExportedMessage, std::allocator<DDSExportedMessage> >;
  static constexpr auto GetName() { return "m_PendingMessages"; }
  static constexpr auto GetType() { return "std::vector<DDSExportedMessage, std::allocator<DDSExportedMessage> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA4A0AC2E; }
  static constexpr unsigned GetTypeNameHash() { return 0x877BFA2B; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_PendingMessages; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<4, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSExportedMessage, std::allocator<DDSExportedMessage> >> & Get() { return self.m_PendingMessages; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSExportedMessage, std::allocator<DDSExportedMessage> >>> & Get() const { return self.m_PendingMessages; }
  void SetDefault() { self.m_PendingMessages = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_PendingMessages; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<5>
{
  using member_type = std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> >;
  static constexpr auto GetName() { return "m_Subscriptions"; }
  static constexpr auto GetType() { return "std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC8B0DA97; }
  static constexpr unsigned GetTypeNameHash() { return 0x5C9F12D7; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_Subscriptions; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<5, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> >> & Get() { return self.m_Subscriptions; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> >>> & Get() const { return self.m_Subscriptions; }
  void SetDefault() { self.m_Subscriptions = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_Subscriptions; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<6>
{
  using member_type = std::vector<DDSExportedRequestedSubscription, std::allocator<DDSExportedRequestedSubscription> >;
  static constexpr auto GetName() { return "m_RequestedSubscriptions"; }
  static constexpr auto GetType() { return "std::vector<DDSExportedRequestedSubscription, std::allocator<DDSExportedRequestedSubscription> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEA664398; }
  static constexpr unsigned GetTypeNameHash() { return 0xA1B612B7; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_RequestedSubscriptions; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<6, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSExportedRequestedSubscription, std::allocator<DDSExportedRequestedSubscription> >> & Get() { return self.m_RequestedSubscriptions; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSExportedRequestedSubscription, std::allocator<DDSExportedRequestedSubscription> >>> & Get() const { return self.m_RequestedSubscriptions; }
  void SetDefault() { self.m_RequestedSubscriptions = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_RequestedSubscriptions; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<7>
{
  using member_type = std::vector<std::pair<int, std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> > >, std::allocator<std::pair<int, std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> > > > >;
  static constexpr auto GetName() { return "m_SharedSubscriptions"; }
  static constexpr auto GetType() { return "std::vector<std::pair<int, std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> > >, std::allocator<std::pair<int, std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> > > > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD7A2432A; }
  static constexpr unsigned GetTypeNameHash() { return 0x53439FAA; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_SharedSubscriptions; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<7, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::pair<int, std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> > >, std::allocator<std::pair<int, std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> > > > >> & Get() { return self.m_SharedSubscriptions; }
  std::add_const_t<std::remove_reference_t<std::vector<std::pair<int, std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> > >, std::allocator<std::pair<int, std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> > > > >>> & Get() const { return self.m_SharedSubscriptions; }
  void SetDefault() { self.m_SharedSubscriptions = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_SharedSubscriptions; }
};

template <>
struct StormReflTypeInfo<DDSDataObjectListSync>
{
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSDataObjectListSync"; }
  static constexpr auto GetNameHash() { return 0x70C9BDBF; }
  static DDSDataObjectListSync & GetDefault() { static DDSDataObjectListSync def; return def; }
};

template <>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<0>
{
  using member_type = int;
  static constexpr auto GetName() { return "m_DataObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x43C90631; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSDataObjectListSync::m_DataObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data<0, Self> : public StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DataObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DataObjectType; }
  void SetDefault() { self.m_DataObjectType = StormReflTypeInfo<DDSDataObjectListSync>::GetDefault().m_DataObjectType; }
};

template <>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<1>
{
  using member_type = int;
  static constexpr auto GetName() { return "m_RoutingTableGen"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4C32C247; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSDataObjectListSync::m_RoutingTableGen; }
};

template <typename Self>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data<1, Self> : public StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_RoutingTableGen; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_RoutingTableGen; }
  void SetDefault() { self.m_RoutingTableGen = StormReflTypeInfo<DDSDataObjectListSync>::GetDefault().m_RoutingTableGen; }
};

template <>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<2>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_KeyRangeMin"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8E81805C; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSDataObjectListSync::m_KeyRangeMin; }
};

template <typename Self>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data<2, Self> : public StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_KeyRangeMin; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_KeyRangeMin; }
  void SetDefault() { self.m_KeyRangeMin = StormReflTypeInfo<DDSDataObjectListSync>::GetDefault().m_KeyRangeMin; }
};

template <>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<3>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_KeyRangeMax"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9938E597; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSDataObjectListSync::m_KeyRangeMax; }
};

template <typename Self>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data<3, Self> : public StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_KeyRangeMax; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_KeyRangeMax; }
  void SetDefault() { self.m_KeyRangeMax = StormReflTypeInfo<DDSDataObjectListSync>::GetDefault().m_KeyRangeMax; }
};

template <>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<4>
{
  using member_type = std::vector<DDSExportedObject, std::allocator<DDSExportedObject> >;
  static constexpr auto GetName() { return "m_Objects"; }
  static constexpr auto GetType() { return "std::vector<DDSExportedObject, std::allocator<DDSExportedObject> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x72A7F566; }
  static constexpr unsigned GetTypeNameHash() { return 0x24EC0D3D; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSDataObjectListSync::m_Objects; }
};

template <typename Self>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data<4, Self> : public StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSExportedObject, std::allocator<DDSExportedObject> >> & Get() { return self.m_Objects; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSExportedObject, std::allocator<DDSExportedObject> >>> & Get() const { return self.m_Objects; }
  void SetDefault() { self.m_Objects = StormReflTypeInfo<DDSDataObjectListSync>::GetDefault().m_Objects; }
};

template <>
struct StormReflTypeInfo<DDSUnlockObject>
{
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSUnlockObject"; }
  static constexpr auto GetNameHash() { return 0xEBC8E0D8; }
  static DDSUnlockObject & GetDefault() { static DDSUnlockObject def; return def; }
};

template <>
struct StormReflTypeInfo<DDSUnlockObject>::field_data_static<0>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDC126BCE; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSUnlockObject::m_Key; }
};

template <typename Self>
struct StormReflTypeInfo<DDSUnlockObject>::field_data<0, Self> : public StormReflTypeInfo<DDSUnlockObject>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSUnlockObject>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSUnlockObject>::field_data_static<1>
{
  using member_type = int;
  static constexpr auto GetName() { return "m_ObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD2FBD4E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSUnlockObject::m_ObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSUnlockObject>::field_data<1, Self> : public StormReflTypeInfo<DDSUnlockObject>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ObjectType; }
  void SetDefault() { self.m_ObjectType = StormReflTypeInfo<DDSUnlockObject>::GetDefault().m_ObjectType; }
};

template <>
struct StormReflTypeInfo<DDSUnlockObject>::field_data_static<2>
{
  using member_type = std::basic_string<char, std::char_traits<char>, std::allocator<char> >;
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDCF873D6; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSUnlockObject::m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<DDSUnlockObject>::field_data<2, Self> : public StormReflTypeInfo<DDSUnlockObject>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::basic_string<char, std::char_traits<char>, std::allocator<char> >> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<std::basic_string<char, std::char_traits<char>, std::allocator<char> >>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<DDSUnlockObject>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<DDSResponderCallData>
{
  using MyBase = DDSResponderCallBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSResponderCallData"; }
  static constexpr auto GetNameHash() { return 0xFA2A3C4A; }
  static DDSResponderCallData & GetDefault() { static DDSResponderCallData def; return def; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessage>
{
  using MyBase = DDSTargetedMessageBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSTargetedMessage"; }
  static constexpr auto GetNameHash() { return 0x8929F64A; }
  static DDSTargetedMessage & GetDefault() { static DDSTargetedMessage def; return def; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageWithResponder>
{
  using MyBase = DDSTargetedMessageWithResponderBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSTargetedMessageWithResponder"; }
  static constexpr auto GetNameHash() { return 0x8AC22CD3; }
  static DDSTargetedMessageWithResponder & GetDefault() { static DDSTargetedMessageWithResponder def; return def; }
};

template <>
struct StormReflTypeInfo<DDSCreateSubscription>
{
  using MyBase = DDSCreateSubscriptionBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSCreateSubscription"; }
  static constexpr auto GetNameHash() { return 0x0E7ECC02; }
  static DDSCreateSubscription & GetDefault() { static DDSCreateSubscription def; return def; }
};

template <>
struct StormReflTypeInfo<DDSCreateDataSubscription>
{
  using MyBase = DDSCreateDataSubscriptionBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSCreateDataSubscription"; }
  static constexpr auto GetNameHash() { return 0x050377EC; }
  static DDSCreateDataSubscription & GetDefault() { static DDSCreateDataSubscription def; return def; }
};

template <>
struct StormReflTypeInfo<DDSDestroySubscription>
{
  using MyBase = DDSDestroySubscriptionBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSDestroySubscription"; }
  static constexpr auto GetNameHash() { return 0x5D5FD9C0; }
  static DDSDestroySubscription & GetDefault() { static DDSDestroySubscription def; return def; }
};

template <>
struct StormReflTypeInfo<DDSCreateExistSubscription>
{
  using MyBase = DDSCreateExistSubscriptionBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSCreateExistSubscription"; }
  static constexpr auto GetNameHash() { return 0x3077413E; }
  static DDSCreateExistSubscription & GetDefault() { static DDSCreateExistSubscription def; return def; }
};

template <>
struct StormReflTypeInfo<DDSCreateDataExistSubscription>
{
  using MyBase = DDSCreateDataExistSubscriptionBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSCreateDataExistSubscription"; }
  static constexpr auto GetNameHash() { return 0x6EAB8D48; }
  static DDSCreateDataExistSubscription & GetDefault() { static DDSCreateDataExistSubscription def; return def; }
};

template <>
struct StormReflTypeInfo<DDSSubscriptionDeleted>
{
  using MyBase = DDSSubscriptionDeletedBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSSubscriptionDeleted"; }
  static constexpr auto GetNameHash() { return 0x052FADE6; }
  static DDSSubscriptionDeleted & GetDefault() { static DDSSubscriptionDeleted def; return def; }
};

namespace StormReflFileInfo
{
  struct DDSServerToServerMessages
  {
    static const int types_n = 18;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct DDSServerToServerMessages::type_info<0>
  {
    using type = ::DDSServerToServerHandshakeRequest;
  };

  template <>
  struct DDSServerToServerMessages::type_info<1>
  {
    using type = ::DDSServerToServerHandshakeResponse;
  };

  template <>
  struct DDSServerToServerMessages::type_info<2>
  {
    using type = ::DDSServerToServerHandshakeFinalize;
  };

  template <>
  struct DDSServerToServerMessages::type_info<3>
  {
    using type = ::DDSExportedMessage;
  };

  template <>
  struct DDSServerToServerMessages::type_info<4>
  {
    using type = ::DDSExportedSubscription;
  };

  template <>
  struct DDSServerToServerMessages::type_info<5>
  {
    using type = ::DDSExportedRequestedSubscription;
  };

  template <>
  struct DDSServerToServerMessages::type_info<6>
  {
    using type = ::DDSExportedObject;
  };

  template <>
  struct DDSServerToServerMessages::type_info<7>
  {
    using type = ::DDSDataObjectListSync;
  };

  template <>
  struct DDSServerToServerMessages::type_info<8>
  {
    using type = ::DDSUnlockObject;
  };

  template <>
  struct DDSServerToServerMessages::type_info<9>
  {
    using type = ::DDSResponderCallData;
  };

  template <>
  struct DDSServerToServerMessages::type_info<10>
  {
    using type = ::DDSTargetedMessage;
  };

  template <>
  struct DDSServerToServerMessages::type_info<11>
  {
    using type = ::DDSTargetedMessageWithResponder;
  };

  template <>
  struct DDSServerToServerMessages::type_info<12>
  {
    using type = ::DDSCreateSubscription;
  };

  template <>
  struct DDSServerToServerMessages::type_info<13>
  {
    using type = ::DDSCreateDataSubscription;
  };

  template <>
  struct DDSServerToServerMessages::type_info<14>
  {
    using type = ::DDSDestroySubscription;
  };

  template <>
  struct DDSServerToServerMessages::type_info<15>
  {
    using type = ::DDSCreateExistSubscription;
  };

  template <>
  struct DDSServerToServerMessages::type_info<16>
  {
    using type = ::DDSCreateDataExistSubscription;
  };

  template <>
  struct DDSServerToServerMessages::type_info<17>
  {
    using type = ::DDSSubscriptionDeleted;
  };

}

