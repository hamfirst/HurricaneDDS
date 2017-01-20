#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "DDSServerToServerMessages.refl.h"
#include "DDSResponder.refl.meta.h"
#include "DDSSharedMessages.refl.meta.h"


template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>
{
  static constexpr int elems_n = 13;
  static constexpr auto GetName() { return "DDSServerToServerMessageType"; }
  static constexpr auto GetNameHash() { return 0xF571F29B; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<0>
{
  static constexpr auto GetName() { return "kHandshakeRequest"; }
  static constexpr auto GetNameHash() { return 0x88B9BC9A; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kHandshakeRequest; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<1>
{
  static constexpr auto GetName() { return "kHandshakeResponse"; }
  static constexpr auto GetNameHash() { return 0x4EA2D147; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kHandshakeResponse; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<2>
{
  static constexpr auto GetName() { return "kHandshakeFinalize"; }
  static constexpr auto GetNameHash() { return 0x550329B7; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kHandshakeFinalize; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<3>
{
  static constexpr auto GetName() { return "kDataObjectListSync"; }
  static constexpr auto GetNameHash() { return 0xEFD94FC6; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kDataObjectListSync; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<4>
{
  static constexpr auto GetName() { return "kUnlockObject"; }
  static constexpr auto GetNameHash() { return 0xC123A9E8; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kUnlockObject; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<5>
{
  static constexpr auto GetName() { return "kResponderCall"; }
  static constexpr auto GetNameHash() { return 0xF561031B; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kResponderCall; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<6>
{
  static constexpr auto GetName() { return "kTargetedMessage"; }
  static constexpr auto GetNameHash() { return 0x646CED86; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kTargetedMessage; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<7>
{
  static constexpr auto GetName() { return "kTargetedMessageResponder"; }
  static constexpr auto GetNameHash() { return 0x0F29BAFC; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kTargetedMessageResponder; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<8>
{
  static constexpr auto GetName() { return "kCreateSubscription"; }
  static constexpr auto GetNameHash() { return 0x6310D904; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kCreateSubscription; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<9>
{
  static constexpr auto GetName() { return "kDestroySubscription"; }
  static constexpr auto GetNameHash() { return 0x005B8D36; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kDestroySubscription; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<10>
{
  static constexpr auto GetName() { return "kSubscriptionDeleted"; }
  static constexpr auto GetNameHash() { return 0xFA6CC738; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kSubscriptionDeleted; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<11>
{
  static constexpr auto GetName() { return "kValidateTokenRequest"; }
  static constexpr auto GetNameHash() { return 0xE1FC2131; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kValidateTokenRequest; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<12>
{
  static constexpr auto GetName() { return "kValidateTokenResponse"; }
  static constexpr auto GetNameHash() { return 0x0FCFEEBA; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kValidateTokenResponse; }
};

template <>
struct StormReflEnumInfo<DDSExportedObjectState>
{
  static constexpr int elems_n = 3;
  static constexpr auto GetName() { return "DDSExportedObjectState"; }
  static constexpr auto GetNameHash() { return 0xF6059719; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<DDSExportedObjectState>::elems<0>
{
  static constexpr auto GetName() { return "kNotLoaded"; }
  static constexpr auto GetNameHash() { return 0x30D8EAF9; }
  static constexpr auto GetValue() { return DDSExportedObjectState::kNotLoaded; }
};

template <>
struct StormReflEnumInfo<DDSExportedObjectState>::elems<1>
{
  static constexpr auto GetName() { return "kLoaded"; }
  static constexpr auto GetNameHash() { return 0xE93424D3; }
  static constexpr auto GetValue() { return DDSExportedObjectState::kLoaded; }
};

template <>
struct StormReflEnumInfo<DDSExportedObjectState>::elems<2>
{
  static constexpr auto GetName() { return "kLocked"; }
  static constexpr auto GetNameHash() { return 0x4861AB65; }
  static constexpr auto GetValue() { return DDSExportedObjectState::kLocked; }
};

template <>
struct StormReflTypeInfo<DDSServerToServerHandshakeRequest>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSServerToServerHandshakeRequest"; }
  static constexpr auto GetNameHash() { return 0xE5C15768; }
  static DDSServerToServerHandshakeRequest & GetDefault() { static DDSServerToServerHandshakeRequest def; return def; }
};

template <>
struct StormReflTypeInfo<DDSServerToServerHandshakeRequest>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Version"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2AEEA616; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
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
  using member_type = DDSNodeId; // unsigned int
  static constexpr auto GetName() { return "m_NodeId"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x445D404F; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSServerToServerHandshakeRequest::m_NodeId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSServerToServerHandshakeRequest>::field_data<1, Self> : public StormReflTypeInfo<DDSServerToServerHandshakeRequest>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSNodeId> & Get() { return self.m_NodeId; }
  std::add_const_t<std::remove_reference_t<DDSNodeId>> & Get() const { return self.m_NodeId; }
  void SetDefault() { self.m_NodeId = StormReflTypeInfo<DDSServerToServerHandshakeRequest>::GetDefault().m_NodeId; }
};

template <>
struct StormReflTypeInfo<DDSServerToServerHandshakeRequest>::field_data_static<2>
{
  using member_type = unsigned long long; // unsigned long long
  static constexpr auto GetName() { return "m_Secret"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x119DBF2D; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
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
  using member_type = unsigned long long; // unsigned long long
  static constexpr auto GetName() { return "m_Challenge"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0B29A84A; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
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
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSServerToServerHandshakeResponse"; }
  static constexpr auto GetNameHash() { return 0x1D7C3A9C; }
  static DDSServerToServerHandshakeResponse & GetDefault() { static DDSServerToServerHandshakeResponse def; return def; }
};

template <>
struct StormReflTypeInfo<DDSServerToServerHandshakeResponse>::field_data_static<0>
{
  using member_type = DDSNodeId; // unsigned int
  static constexpr auto GetName() { return "m_NodeId"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x445D404F; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSServerToServerHandshakeResponse::m_NodeId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSServerToServerHandshakeResponse>::field_data<0, Self> : public StormReflTypeInfo<DDSServerToServerHandshakeResponse>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSNodeId> & Get() { return self.m_NodeId; }
  std::add_const_t<std::remove_reference_t<DDSNodeId>> & Get() const { return self.m_NodeId; }
  void SetDefault() { self.m_NodeId = StormReflTypeInfo<DDSServerToServerHandshakeResponse>::GetDefault().m_NodeId; }
};

template <>
struct StormReflTypeInfo<DDSServerToServerHandshakeResponse>::field_data_static<1>
{
  using member_type = unsigned long long; // unsigned long long
  static constexpr auto GetName() { return "m_Secret"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x119DBF2D; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
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
  using member_type = unsigned long long; // unsigned long long
  static constexpr auto GetName() { return "m_Challenge"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0B29A84A; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
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
  using member_type = unsigned long long; // unsigned long long
  static constexpr auto GetName() { return "m_ChallengeResponse"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5C674F6E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
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
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSServerToServerHandshakeFinalize"; }
  static constexpr auto GetNameHash() { return 0x06DDC26C; }
  static DDSServerToServerHandshakeFinalize & GetDefault() { static DDSServerToServerHandshakeFinalize def; return def; }
};

template <>
struct StormReflTypeInfo<DDSServerToServerHandshakeFinalize>::field_data_static<0>
{
  using member_type = unsigned long long; // unsigned long long
  static constexpr auto GetName() { return "m_Challenge"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0B29A84A; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
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
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSExportedMessage"; }
  static constexpr auto GetNameHash() { return 0x264CC319; }
  static DDSExportedMessage & GetDefault() { static DDSExportedMessage def; return def; }
};

template <>
struct StormReflTypeInfo<DDSExportedMessage>::field_data_static<0>
{
  using member_type = DDSServerToServerMessageType; // DDSServerToServerMessageType
  static constexpr auto GetName() { return "m_Type"; }
  static constexpr auto GetType() { return "DDSServerToServerMessageType"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB243C236; }
  static constexpr unsigned GetTypeNameHash() { return 0xF571F29B; }
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
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Message"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x234F45AA; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSExportedMessage::m_Message; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedMessage>::field_data<1, Self> : public StormReflTypeInfo<DDSExportedMessage>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Message; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Message; }
  void SetDefault() { self.m_Message = StormReflTypeInfo<DDSExportedMessage>::GetDefault().m_Message; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>
{
  using MyBase = void;
  static constexpr int fields_n = 8;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSExportedObject"; }
  static constexpr auto GetNameHash() { return 0xE6435CE3; }
  static DDSExportedObject & GetDefault() { static DDSExportedObject def; return def; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x79726F4E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_Key; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<0, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<1>
{
  using member_type = DDSExportedObjectState; // DDSExportedObjectState
  static constexpr auto GetName() { return "m_State"; }
  static constexpr auto GetType() { return "DDSExportedObjectState"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2EA5429B; }
  static constexpr unsigned GetTypeNameHash() { return 0xF6059719; }
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
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ActiveObject"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x04868966; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_ActiveObject; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<2, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ActiveObject; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ActiveObject; }
  void SetDefault() { self.m_ActiveObject = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_ActiveObject; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_DatabaseObject"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x405F9084; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_DatabaseObject; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<3, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_DatabaseObject; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_DatabaseObject; }
  void SetDefault() { self.m_DatabaseObject = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_DatabaseObject; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<4>
{
  using member_type = std::vector<DDSExportedMessage>; // std::vector<DDSExportedMessage, std::allocator<DDSExportedMessage> >
  static constexpr auto GetName() { return "m_PendingMessages"; }
  static constexpr auto GetType() { return "std::vector<DDSExportedMessage, std::allocator<DDSExportedMessage> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2C42FDAA; }
  static constexpr unsigned GetTypeNameHash() { return 0x6C768773; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_PendingMessages; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<4, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSExportedMessage>> & Get() { return self.m_PendingMessages; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSExportedMessage>>> & Get() const { return self.m_PendingMessages; }
  void SetDefault() { self.m_PendingMessages = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_PendingMessages; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<5>
{
  using member_type = std::vector<DDSExportedSubscription>; // std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> >
  static constexpr auto GetName() { return "m_Subscriptions"; }
  static constexpr auto GetType() { return "std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA001CC15; }
  static constexpr unsigned GetTypeNameHash() { return 0x1CD204EB; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_Subscriptions; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<5, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSExportedSubscription>> & Get() { return self.m_Subscriptions; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSExportedSubscription>>> & Get() const { return self.m_Subscriptions; }
  void SetDefault() { self.m_Subscriptions = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_Subscriptions; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<6>
{
  using member_type = std::vector<DDSExportedRequestedSubscription>; // std::vector<DDSExportedRequestedSubscription, std::allocator<DDSExportedRequestedSubscription> >
  static constexpr auto GetName() { return "m_RequestedSubscriptions"; }
  static constexpr auto GetType() { return "std::vector<DDSExportedRequestedSubscription, std::allocator<DDSExportedRequestedSubscription> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1FA2F1D7; }
  static constexpr unsigned GetTypeNameHash() { return 0xC0089DA6; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_RequestedSubscriptions; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<6, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSExportedRequestedSubscription>> & Get() { return self.m_RequestedSubscriptions; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSExportedRequestedSubscription>>> & Get() const { return self.m_RequestedSubscriptions; }
  void SetDefault() { self.m_RequestedSubscriptions = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_RequestedSubscriptions; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<7>
{
  using member_type = std::vector<std::pair<int, std::vector<DDSExportedSubscription> > >; // std::vector<std::pair<int, std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> > >, std::allocator<std::pair<int, std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> > > > >
  static constexpr auto GetName() { return "m_SharedSubscriptions"; }
  static constexpr auto GetType() { return "std::vector<std::pair<int, std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> > >, std::allocator<std::pair<int, std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> > > > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDEEB192F; }
  static constexpr unsigned GetTypeNameHash() { return 0x9F2C3407; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_SharedSubscriptions; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<7, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::pair<int, std::vector<DDSExportedSubscription> > >> & Get() { return self.m_SharedSubscriptions; }
  std::add_const_t<std::remove_reference_t<std::vector<std::pair<int, std::vector<DDSExportedSubscription> > >>> & Get() const { return self.m_SharedSubscriptions; }
  void SetDefault() { self.m_SharedSubscriptions = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_SharedSubscriptions; }
};

template <>
struct StormReflTypeInfo<DDSDataObjectListSync>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSDataObjectListSync"; }
  static constexpr auto GetNameHash() { return 0xD5BF11BC; }
  static DDSDataObjectListSync & GetDefault() { static DDSDataObjectListSync def; return def; }
};

template <>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DataObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x31DC1DA8; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
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
  using member_type = int; // int
  static constexpr auto GetName() { return "m_RoutingTableGen"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x608D0035; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
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
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_KeyRangeMin"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDF42EE40; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSDataObjectListSync::m_KeyRangeMin; }
};

template <typename Self>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data<2, Self> : public StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_KeyRangeMin; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_KeyRangeMin; }
  void SetDefault() { self.m_KeyRangeMin = StormReflTypeInfo<DDSDataObjectListSync>::GetDefault().m_KeyRangeMin; }
};

template <>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<3>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_KeyRangeMax"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE34FD119; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSDataObjectListSync::m_KeyRangeMax; }
};

template <typename Self>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data<3, Self> : public StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_KeyRangeMax; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_KeyRangeMax; }
  void SetDefault() { self.m_KeyRangeMax = StormReflTypeInfo<DDSDataObjectListSync>::GetDefault().m_KeyRangeMax; }
};

template <>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<4>
{
  using member_type = std::vector<DDSExportedObject>; // std::vector<DDSExportedObject, std::allocator<DDSExportedObject> >
  static constexpr auto GetName() { return "m_Objects"; }
  static constexpr auto GetType() { return "std::vector<DDSExportedObject, std::allocator<DDSExportedObject> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x27E8B926; }
  static constexpr unsigned GetTypeNameHash() { return 0x88B81936; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSDataObjectListSync::m_Objects; }
};

template <typename Self>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data<4, Self> : public StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSExportedObject>> & Get() { return self.m_Objects; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSExportedObject>>> & Get() const { return self.m_Objects; }
  void SetDefault() { self.m_Objects = StormReflTypeInfo<DDSDataObjectListSync>::GetDefault().m_Objects; }
};

template <>
struct StormReflTypeInfo<DDSUnlockObject>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSUnlockObject"; }
  static constexpr auto GetNameHash() { return 0x5C6CB43B; }
  static DDSUnlockObject & GetDefault() { static DDSUnlockObject def; return def; }
};

template <>
struct StormReflTypeInfo<DDSUnlockObject>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x79726F4E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSUnlockObject::m_Key; }
};

template <typename Self>
struct StormReflTypeInfo<DDSUnlockObject>::field_data<0, Self> : public StormReflTypeInfo<DDSUnlockObject>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSUnlockObject>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSUnlockObject>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2C75B4A5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
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
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSUnlockObject::m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<DDSUnlockObject>::field_data<2, Self> : public StormReflTypeInfo<DDSUnlockObject>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Data; }
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
  static constexpr auto GetNameHash() { return 0xEAA1DA8E; }
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
  static constexpr auto GetNameHash() { return 0xF2AC566F; }
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
  static constexpr auto GetNameHash() { return 0x6C6F4C91; }
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
  static constexpr auto GetNameHash() { return 0x5976877E; }
  static DDSCreateSubscription & GetDefault() { static DDSCreateSubscription def; return def; }
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
  static constexpr auto GetNameHash() { return 0xB0B1734A; }
  static DDSDestroySubscription & GetDefault() { static DDSDestroySubscription def; return def; }
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
  static constexpr auto GetNameHash() { return 0x4A863944; }
  static DDSSubscriptionDeleted & GetDefault() { static DDSSubscriptionDeleted def; return def; }
};

template <>
struct StormReflTypeInfo<DDSValidateTokenRequest>
{
  using MyBase = DDSValidateTokenRequestBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSValidateTokenRequest"; }
  static constexpr auto GetNameHash() { return 0xB8FFF6D8; }
  static DDSValidateTokenRequest & GetDefault() { static DDSValidateTokenRequest def; return def; }
};

template <>
struct StormReflTypeInfo<DDSValidateTokenResponse>
{
  using MyBase = DDSValidateTokenResponseBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSValidateTokenResponse"; }
  static constexpr auto GetNameHash() { return 0xD640B7B1; }
  static DDSValidateTokenResponse & GetDefault() { static DDSValidateTokenResponse def; return def; }
};

namespace StormReflFileInfo
{
  struct DDSServerToServerMessages
  {
    static const int types_n = 15;
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
    using type = ::DDSExportedObject;
  };

  template <>
  struct DDSServerToServerMessages::type_info<5>
  {
    using type = ::DDSDataObjectListSync;
  };

  template <>
  struct DDSServerToServerMessages::type_info<6>
  {
    using type = ::DDSUnlockObject;
  };

  template <>
  struct DDSServerToServerMessages::type_info<7>
  {
    using type = ::DDSResponderCallData;
  };

  template <>
  struct DDSServerToServerMessages::type_info<8>
  {
    using type = ::DDSTargetedMessage;
  };

  template <>
  struct DDSServerToServerMessages::type_info<9>
  {
    using type = ::DDSTargetedMessageWithResponder;
  };

  template <>
  struct DDSServerToServerMessages::type_info<10>
  {
    using type = ::DDSCreateSubscription;
  };

  template <>
  struct DDSServerToServerMessages::type_info<11>
  {
    using type = ::DDSDestroySubscription;
  };

  template <>
  struct DDSServerToServerMessages::type_info<12>
  {
    using type = ::DDSSubscriptionDeleted;
  };

  template <>
  struct DDSServerToServerMessages::type_info<13>
  {
    using type = ::DDSValidateTokenRequest;
  };

  template <>
  struct DDSServerToServerMessages::type_info<14>
  {
    using type = ::DDSValidateTokenResponse;
  };

}

