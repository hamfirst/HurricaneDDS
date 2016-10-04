#pragma once

#include <StormRefl\StormReflMetaInfoBase.h>

#include "DDSServerToServerMessages.refl.h"
#include "DDSResponder.refl.meta.h"


template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>
{
  static constexpr int elems_n = 7;
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
  static constexpr auto GetName() { return "kResponderCall"; }
  static constexpr auto GetNameHash() { return 0x5055B576; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kResponderCall; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<5>
{
  static constexpr auto GetName() { return "kTargetedMessage"; }
  static constexpr auto GetNameHash() { return 0x3440F0A6; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kTargetedMessage; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<6>
{
  static constexpr auto GetName() { return "kTargetedMessageResponder"; }
  static constexpr auto GetNameHash() { return 0x2460C571; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kTargetedMessageResponder; }
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
  using member_type = std::basic_string<char, std::char_traits<char>, std::allocator<char> >;
  static constexpr auto GetName() { return "m_Message"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD2BD02E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSExportedMessage::m_Message; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedMessage>::field_data<0, Self> : public StormReflTypeInfo<DDSExportedMessage>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::basic_string<char, std::char_traits<char>, std::allocator<char> >> & Get() { return self.m_Message; }
  std::add_const_t<std::remove_reference_t<std::basic_string<char, std::char_traits<char>, std::allocator<char> >>> & Get() const { return self.m_Message; }
  void SetDefault() { self.m_Message = StormReflTypeInfo<DDSExportedMessage>::GetDefault().m_Message; }
};

template <>
struct StormReflTypeInfo<DDSExportedMessage>::field_data_static<1>
{
  using member_type = DDSResponderData;
  static constexpr auto GetName() { return "m_Responder"; }
  static constexpr auto GetType() { return "DDSResponderData"; }
  static constexpr unsigned GetFieldNameHash() { return 0x9679CCE0; }
  static constexpr unsigned GetTypeNameHash() { return 0xA9791E88; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSExportedMessage::m_Responder; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedMessage>::field_data<1, Self> : public StormReflTypeInfo<DDSExportedMessage>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSResponderData> & Get() { return self.m_Responder; }
  std::add_const_t<std::remove_reference_t<DDSResponderData>> & Get() const { return self.m_Responder; }
  void SetDefault() { self.m_Responder = StormReflTypeInfo<DDSExportedMessage>::GetDefault().m_Responder; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>
{
  static constexpr int fields_n = 5;
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
  using member_type = std::basic_string<char, std::char_traits<char>, std::allocator<char> >;
  static constexpr auto GetName() { return "m_ActiveObject"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6353F0E6; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_ActiveObject; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<1, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::basic_string<char, std::char_traits<char>, std::allocator<char> >> & Get() { return self.m_ActiveObject; }
  std::add_const_t<std::remove_reference_t<std::basic_string<char, std::char_traits<char>, std::allocator<char> >>> & Get() const { return self.m_ActiveObject; }
  void SetDefault() { self.m_ActiveObject = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_ActiveObject; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<2>
{
  using member_type = std::basic_string<char, std::char_traits<char>, std::allocator<char> >;
  static constexpr auto GetName() { return "m_DatabaseObject"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x133A1F6C; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_DatabaseObject; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<2, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::basic_string<char, std::char_traits<char>, std::allocator<char> >> & Get() { return self.m_DatabaseObject; }
  std::add_const_t<std::remove_reference_t<std::basic_string<char, std::char_traits<char>, std::allocator<char> >>> & Get() const { return self.m_DatabaseObject; }
  void SetDefault() { self.m_DatabaseObject = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_DatabaseObject; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<3>
{
  using member_type = std::vector<DDSExportedMessage, std::allocator<DDSExportedMessage> >;
  static constexpr auto GetName() { return "m_PendingMessages"; }
  static constexpr auto GetType() { return "std::vector<DDSExportedMessage, std::allocator<DDSExportedMessage> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA4A0AC2E; }
  static constexpr unsigned GetTypeNameHash() { return 0x877BFA2B; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_PendingMessages; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<3, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSExportedMessage, std::allocator<DDSExportedMessage> >> & Get() { return self.m_PendingMessages; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSExportedMessage, std::allocator<DDSExportedMessage> >>> & Get() const { return self.m_PendingMessages; }
  void SetDefault() { self.m_PendingMessages = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_PendingMessages; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<4>
{
  using member_type = std::vector<DDSExportedMessage, std::allocator<DDSExportedMessage> >;
  static constexpr auto GetName() { return "m_PendingQueries"; }
  static constexpr auto GetType() { return "std::vector<DDSExportedMessage, std::allocator<DDSExportedMessage> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB065DE7D; }
  static constexpr unsigned GetTypeNameHash() { return 0x877BFA2B; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_PendingQueries; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<4, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSExportedMessage, std::allocator<DDSExportedMessage> >> & Get() { return self.m_PendingQueries; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSExportedMessage, std::allocator<DDSExportedMessage> >>> & Get() const { return self.m_PendingQueries; }
  void SetDefault() { self.m_PendingQueries = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_PendingQueries; }
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
struct StormReflTypeInfo<DDSResponderCallData>
{
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSResponderCallData"; }
  static constexpr auto GetNameHash() { return 0xFA2A3C4A; }
  static DDSResponderCallData & GetDefault() { static DDSResponderCallData def; return def; }
};

template <>
struct StormReflTypeInfo<DDSResponderCallData>::field_data_static<0>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDC126BCE; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSResponderCallData::m_Key; }
};

template <typename Self>
struct StormReflTypeInfo<DDSResponderCallData>::field_data<0, Self> : public StormReflTypeInfo<DDSResponderCallData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSResponderCallData>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSResponderCallData>::field_data_static<1>
{
  using member_type = int;
  static constexpr auto GetName() { return "m_ObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD2FBD4E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSResponderCallData::m_ObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSResponderCallData>::field_data<1, Self> : public StormReflTypeInfo<DDSResponderCallData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ObjectType; }
  void SetDefault() { self.m_ObjectType = StormReflTypeInfo<DDSResponderCallData>::GetDefault().m_ObjectType; }
};

template <>
struct StormReflTypeInfo<DDSResponderCallData>::field_data_static<2>
{
  using member_type = int;
  static constexpr auto GetName() { return "m_MethodId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF7823FFB; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSResponderCallData::m_MethodId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSResponderCallData>::field_data<2, Self> : public StormReflTypeInfo<DDSResponderCallData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_MethodId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_MethodId; }
  void SetDefault() { self.m_MethodId = StormReflTypeInfo<DDSResponderCallData>::GetDefault().m_MethodId; }
};

template <>
struct StormReflTypeInfo<DDSResponderCallData>::field_data_static<3>
{
  using member_type = std::basic_string<char, std::char_traits<char>, std::allocator<char> >;
  static constexpr auto GetName() { return "m_MethodArgs"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE5505EE5; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSResponderCallData::m_MethodArgs; }
};

template <typename Self>
struct StormReflTypeInfo<DDSResponderCallData>::field_data<3, Self> : public StormReflTypeInfo<DDSResponderCallData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::basic_string<char, std::char_traits<char>, std::allocator<char> >> & Get() { return self.m_MethodArgs; }
  std::add_const_t<std::remove_reference_t<std::basic_string<char, std::char_traits<char>, std::allocator<char> >>> & Get() const { return self.m_MethodArgs; }
  void SetDefault() { self.m_MethodArgs = StormReflTypeInfo<DDSResponderCallData>::GetDefault().m_MethodArgs; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessage>
{
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSTargetedMessage"; }
  static constexpr auto GetNameHash() { return 0x8929F64A; }
  static DDSTargetedMessage & GetDefault() { static DDSTargetedMessage def; return def; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessage>::field_data_static<0>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDC126BCE; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessage::m_Key; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessage>::field_data<0, Self> : public StormReflTypeInfo<DDSTargetedMessage>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSTargetedMessage>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessage>::field_data_static<1>
{
  using member_type = int;
  static constexpr auto GetName() { return "m_ObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD2FBD4E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessage::m_ObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessage>::field_data<1, Self> : public StormReflTypeInfo<DDSTargetedMessage>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ObjectType; }
  void SetDefault() { self.m_ObjectType = StormReflTypeInfo<DDSTargetedMessage>::GetDefault().m_ObjectType; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessage>::field_data_static<2>
{
  using member_type = int;
  static constexpr auto GetName() { return "m_MethodId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF7823FFB; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessage::m_MethodId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessage>::field_data<2, Self> : public StormReflTypeInfo<DDSTargetedMessage>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_MethodId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_MethodId; }
  void SetDefault() { self.m_MethodId = StormReflTypeInfo<DDSTargetedMessage>::GetDefault().m_MethodId; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessage>::field_data_static<3>
{
  using member_type = std::basic_string<char, std::char_traits<char>, std::allocator<char> >;
  static constexpr auto GetName() { return "m_MethodArgs"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE5505EE5; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessage::m_MethodArgs; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessage>::field_data<3, Self> : public StormReflTypeInfo<DDSTargetedMessage>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::basic_string<char, std::char_traits<char>, std::allocator<char> >> & Get() { return self.m_MethodArgs; }
  std::add_const_t<std::remove_reference_t<std::basic_string<char, std::char_traits<char>, std::allocator<char> >>> & Get() const { return self.m_MethodArgs; }
  void SetDefault() { self.m_MethodArgs = StormReflTypeInfo<DDSTargetedMessage>::GetDefault().m_MethodArgs; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageWithResponder>
{
  static constexpr int fields_n = 8;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSTargetedMessageWithResponder"; }
  static constexpr auto GetNameHash() { return 0x8AC22CD3; }
  static DDSTargetedMessageWithResponder & GetDefault() { static DDSTargetedMessageWithResponder def; return def; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data_static<0>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDC126BCE; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponder::m_Key; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data<0, Self> : public StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSTargetedMessageWithResponder>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data_static<1>
{
  using member_type = int;
  static constexpr auto GetName() { return "m_ObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD2FBD4E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponder::m_ObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data<1, Self> : public StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ObjectType; }
  void SetDefault() { self.m_ObjectType = StormReflTypeInfo<DDSTargetedMessageWithResponder>::GetDefault().m_ObjectType; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data_static<2>
{
  using member_type = int;
  static constexpr auto GetName() { return "m_MethodId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF7823FFB; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponder::m_MethodId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data<2, Self> : public StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_MethodId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_MethodId; }
  void SetDefault() { self.m_MethodId = StormReflTypeInfo<DDSTargetedMessageWithResponder>::GetDefault().m_MethodId; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data_static<3>
{
  using member_type = std::basic_string<char, std::char_traits<char>, std::allocator<char> >;
  static constexpr auto GetName() { return "m_MethodArgs"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE5505EE5; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponder::m_MethodArgs; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data<3, Self> : public StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::basic_string<char, std::char_traits<char>, std::allocator<char> >> & Get() { return self.m_MethodArgs; }
  std::add_const_t<std::remove_reference_t<std::basic_string<char, std::char_traits<char>, std::allocator<char> >>> & Get() const { return self.m_MethodArgs; }
  void SetDefault() { self.m_MethodArgs = StormReflTypeInfo<DDSTargetedMessageWithResponder>::GetDefault().m_MethodArgs; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data_static<4>
{
  using member_type = unsigned long long;
  static constexpr auto GetName() { return "m_ResponderKey"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x47BF66BE; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponder::m_ResponderKey; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data<4, Self> : public StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, unsigned long long> & Get() { return self.m_ResponderKey; }
  std::add_const_t<std::remove_reference_t<unsigned long long>> & Get() const { return self.m_ResponderKey; }
  void SetDefault() { self.m_ResponderKey = StormReflTypeInfo<DDSTargetedMessageWithResponder>::GetDefault().m_ResponderKey; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data_static<5>
{
  using member_type = int;
  static constexpr auto GetName() { return "m_ResponderObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6ECD8D43; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponder::m_ResponderObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data<5, Self> : public StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ResponderObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ResponderObjectType; }
  void SetDefault() { self.m_ResponderObjectType = StormReflTypeInfo<DDSTargetedMessageWithResponder>::GetDefault().m_ResponderObjectType; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data_static<6>
{
  using member_type = int;
  static constexpr auto GetName() { return "m_ResponderMethodId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x28424F94; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponder::m_ResponderMethodId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data<6, Self> : public StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ResponderMethodId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ResponderMethodId; }
  void SetDefault() { self.m_ResponderMethodId = StormReflTypeInfo<DDSTargetedMessageWithResponder>::GetDefault().m_ResponderMethodId; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data_static<7>
{
  using member_type = std::basic_string<char, std::char_traits<char>, std::allocator<char> >;
  static constexpr auto GetName() { return "m_ReturnArg"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBA1409C0; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponder::m_ReturnArg; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data<7, Self> : public StormReflTypeInfo<DDSTargetedMessageWithResponder>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::basic_string<char, std::char_traits<char>, std::allocator<char> >> & Get() { return self.m_ReturnArg; }
  std::add_const_t<std::remove_reference_t<std::basic_string<char, std::char_traits<char>, std::allocator<char> >>> & Get() const { return self.m_ReturnArg; }
  void SetDefault() { self.m_ReturnArg = StormReflTypeInfo<DDSTargetedMessageWithResponder>::GetDefault().m_ReturnArg; }
};

