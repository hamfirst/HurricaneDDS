#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "DDSSharedMessages.refl.h"


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
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
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
  match_const_t<Self, std::string> & Get() { return self.m_DataPath; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_DataPath; }
  void SetDefault() { self.m_DataPath = StormReflTypeInfo<DDSExportedSubscription>::GetDefault().m_DataPath; }
};

template <>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
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
  match_const_t<Self, DDSKey> & Get() { return self.m_SubscriptionId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SubscriptionId; }
  void SetDefault() { self.m_SubscriptionId = StormReflTypeInfo<DDSExportedSubscription>::GetDefault().m_SubscriptionId; }
};

template <>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long long
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
  match_const_t<Self, DDSKey> & Get() { return self.m_ResponderKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_ResponderKey; }
  void SetDefault() { self.m_ResponderKey = StormReflTypeInfo<DDSExportedSubscription>::GetDefault().m_ResponderKey; }
};

template <>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data_static<3>
{
  using member_type = int; // int
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
  using member_type = int; // int
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
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
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
  match_const_t<Self, std::string> & Get() { return self.m_ResponderArgs; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ResponderArgs; }
  void SetDefault() { self.m_ResponderArgs = StormReflTypeInfo<DDSExportedSubscription>::GetDefault().m_ResponderArgs; }
};

template <>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data_static<6>
{
  using member_type = bool; // bool
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
  using member_type = bool; // bool
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
  using member_type = DDSKey; // unsigned long long
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
  match_const_t<Self, DDSKey> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSExportedRequestedSubscription>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSExportedRequestedSubscription>::field_data_static<1>
{
  using member_type = int; // int
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
  using member_type = DDSKey; // unsigned long long
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
  match_const_t<Self, DDSKey> & Get() { return self.m_SubscriptionId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SubscriptionId; }
  void SetDefault() { self.m_SubscriptionId = StormReflTypeInfo<DDSExportedRequestedSubscription>::GetDefault().m_SubscriptionId; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageBase>
{
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSTargetedMessageBase"; }
  static constexpr auto GetNameHash() { return 0x64542CEA; }
  static DDSTargetedMessageBase & GetDefault() { static DDSTargetedMessageBase def; return def; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageBase>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDC126BCE; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageBase::m_Key; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessageBase>::field_data<0, Self> : public StormReflTypeInfo<DDSTargetedMessageBase>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSTargetedMessageBase>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageBase>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD2FBD4E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageBase::m_ObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessageBase>::field_data<1, Self> : public StormReflTypeInfo<DDSTargetedMessageBase>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ObjectType; }
  void SetDefault() { self.m_ObjectType = StormReflTypeInfo<DDSTargetedMessageBase>::GetDefault().m_ObjectType; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageBase>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_MethodId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF7823FFB; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageBase::m_MethodId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessageBase>::field_data<2, Self> : public StormReflTypeInfo<DDSTargetedMessageBase>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_MethodId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_MethodId; }
  void SetDefault() { self.m_MethodId = StormReflTypeInfo<DDSTargetedMessageBase>::GetDefault().m_MethodId; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageBase>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_MethodArgs"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE5505EE5; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageBase::m_MethodArgs; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessageBase>::field_data<3, Self> : public StormReflTypeInfo<DDSTargetedMessageBase>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_MethodArgs; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_MethodArgs; }
  void SetDefault() { self.m_MethodArgs = StormReflTypeInfo<DDSTargetedMessageBase>::GetDefault().m_MethodArgs; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageWithResponderBase>
{
  static constexpr int fields_n = 8;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSTargetedMessageWithResponderBase"; }
  static constexpr auto GetNameHash() { return 0x37FF8E28; }
  static DDSTargetedMessageWithResponderBase & GetDefault() { static DDSTargetedMessageWithResponderBase def; return def; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDC126BCE; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponderBase::m_Key; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data<0, Self> : public StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD2FBD4E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponderBase::m_ObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data<1, Self> : public StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ObjectType; }
  void SetDefault() { self.m_ObjectType = StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::GetDefault().m_ObjectType; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_MethodId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF7823FFB; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponderBase::m_MethodId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data<2, Self> : public StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_MethodId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_MethodId; }
  void SetDefault() { self.m_MethodId = StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::GetDefault().m_MethodId; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_MethodArgs"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE5505EE5; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponderBase::m_MethodArgs; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data<3, Self> : public StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_MethodArgs; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_MethodArgs; }
  void SetDefault() { self.m_MethodArgs = StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::GetDefault().m_MethodArgs; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data_static<4>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ResponderObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6ECD8D43; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponderBase::m_ResponderObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data<4, Self> : public StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ResponderObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ResponderObjectType; }
  void SetDefault() { self.m_ResponderObjectType = StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::GetDefault().m_ResponderObjectType; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data_static<5>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_ResponderKey"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x47BF66BE; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponderBase::m_ResponderKey; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data<5, Self> : public StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_ResponderKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_ResponderKey; }
  void SetDefault() { self.m_ResponderKey = StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::GetDefault().m_ResponderKey; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data_static<6>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ResponderMethodId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x28424F94; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponderBase::m_ResponderMethodId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data<6, Self> : public StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ResponderMethodId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ResponderMethodId; }
  void SetDefault() { self.m_ResponderMethodId = StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::GetDefault().m_ResponderMethodId; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data_static<7>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ReturnArg"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBA1409C0; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponderBase::m_ReturnArg; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data<7, Self> : public StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ReturnArg; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ReturnArg; }
  void SetDefault() { self.m_ReturnArg = StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::GetDefault().m_ReturnArg; }
};

template <>
struct StormReflTypeInfo<DDSResponderCallBase>
{
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSResponderCallBase"; }
  static constexpr auto GetNameHash() { return 0xDC4C7AD2; }
  static DDSResponderCallBase & GetDefault() { static DDSResponderCallBase def; return def; }
};

template <>
struct StormReflTypeInfo<DDSResponderCallBase>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDC126BCE; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSResponderCallBase::m_Key; }
};

template <typename Self>
struct StormReflTypeInfo<DDSResponderCallBase>::field_data<0, Self> : public StormReflTypeInfo<DDSResponderCallBase>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSResponderCallBase>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSResponderCallBase>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD2FBD4E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSResponderCallBase::m_ObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSResponderCallBase>::field_data<1, Self> : public StormReflTypeInfo<DDSResponderCallBase>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ObjectType; }
  void SetDefault() { self.m_ObjectType = StormReflTypeInfo<DDSResponderCallBase>::GetDefault().m_ObjectType; }
};

template <>
struct StormReflTypeInfo<DDSResponderCallBase>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_MethodId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF7823FFB; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSResponderCallBase::m_MethodId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSResponderCallBase>::field_data<2, Self> : public StormReflTypeInfo<DDSResponderCallBase>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_MethodId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_MethodId; }
  void SetDefault() { self.m_MethodId = StormReflTypeInfo<DDSResponderCallBase>::GetDefault().m_MethodId; }
};

template <>
struct StormReflTypeInfo<DDSResponderCallBase>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ResponderArgs"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xEE5C340B; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSResponderCallBase::m_ResponderArgs; }
};

template <typename Self>
struct StormReflTypeInfo<DDSResponderCallBase>::field_data<3, Self> : public StormReflTypeInfo<DDSResponderCallBase>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ResponderArgs; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ResponderArgs; }
  void SetDefault() { self.m_ResponderArgs = StormReflTypeInfo<DDSResponderCallBase>::GetDefault().m_ResponderArgs; }
};

template <>
struct StormReflTypeInfo<DDSResponderCallBase>::field_data_static<4>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_MethodArgs"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE5505EE5; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSResponderCallBase::m_MethodArgs; }
};

template <typename Self>
struct StormReflTypeInfo<DDSResponderCallBase>::field_data<4, Self> : public StormReflTypeInfo<DDSResponderCallBase>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_MethodArgs; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_MethodArgs; }
  void SetDefault() { self.m_MethodArgs = StormReflTypeInfo<DDSResponderCallBase>::GetDefault().m_MethodArgs; }
};

template <>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>
{
  static constexpr int fields_n = 9;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSCreateSubscriptionBase"; }
  static constexpr auto GetNameHash() { return 0x97A653B0; }
  static DDSCreateSubscriptionBase & GetDefault() { static DDSCreateSubscriptionBase def; return def; }
};

template <>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_DataPath"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8780827D; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSubscriptionBase::m_DataPath; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data<0, Self> : public StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_DataPath; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_DataPath; }
  void SetDefault() { self.m_DataPath = StormReflTypeInfo<DDSCreateSubscriptionBase>::GetDefault().m_DataPath; }
};

template <>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDC126BCE; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSubscriptionBase::m_Key; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data<1, Self> : public StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSCreateSubscriptionBase>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD2FBD4E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSubscriptionBase::m_ObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data<2, Self> : public StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ObjectType; }
  void SetDefault() { self.m_ObjectType = StormReflTypeInfo<DDSCreateSubscriptionBase>::GetDefault().m_ObjectType; }
};

template <>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<3>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_SubscriptionId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x01DAA775; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSubscriptionBase::m_SubscriptionId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data<3, Self> : public StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SubscriptionId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SubscriptionId; }
  void SetDefault() { self.m_SubscriptionId = StormReflTypeInfo<DDSCreateSubscriptionBase>::GetDefault().m_SubscriptionId; }
};

template <>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<4>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ResponderObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6ECD8D43; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSubscriptionBase::m_ResponderObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data<4, Self> : public StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ResponderObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ResponderObjectType; }
  void SetDefault() { self.m_ResponderObjectType = StormReflTypeInfo<DDSCreateSubscriptionBase>::GetDefault().m_ResponderObjectType; }
};

template <>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<5>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_ResponderKey"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x47BF66BE; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSubscriptionBase::m_ResponderKey; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data<5, Self> : public StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_ResponderKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_ResponderKey; }
  void SetDefault() { self.m_ResponderKey = StormReflTypeInfo<DDSCreateSubscriptionBase>::GetDefault().m_ResponderKey; }
};

template <>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<6>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ResponderMethodId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x28424F94; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSubscriptionBase::m_ResponderMethodId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data<6, Self> : public StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ResponderMethodId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ResponderMethodId; }
  void SetDefault() { self.m_ResponderMethodId = StormReflTypeInfo<DDSCreateSubscriptionBase>::GetDefault().m_ResponderMethodId; }
};

template <>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<7>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ReturnArg"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBA1409C0; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSubscriptionBase::m_ReturnArg; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data<7, Self> : public StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ReturnArg; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ReturnArg; }
  void SetDefault() { self.m_ReturnArg = StormReflTypeInfo<DDSCreateSubscriptionBase>::GetDefault().m_ReturnArg; }
};

template <>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<8>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_DeltaOnly"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB3B163F9; }
  static constexpr unsigned GetTypeNameHash() { return 0xA1B914E5; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSubscriptionBase::m_DeltaOnly; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data<8, Self> : public StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_DeltaOnly; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_DeltaOnly; }
  void SetDefault() { self.m_DeltaOnly = StormReflTypeInfo<DDSCreateSubscriptionBase>::GetDefault().m_DeltaOnly; }
};

template <>
struct StormReflTypeInfo<DDSCreateDataSubscriptionBase>
{
  using MyBase = DDSCreateSubscriptionBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSCreateDataSubscriptionBase"; }
  static constexpr auto GetNameHash() { return 0x95932B79; }
  static DDSCreateDataSubscriptionBase & GetDefault() { static DDSCreateDataSubscriptionBase def; return def; }
};

template <>
struct StormReflTypeInfo<DDSDestroySubscriptionBase>
{
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSDestroySubscriptionBase"; }
  static constexpr auto GetNameHash() { return 0xF2D3DB2E; }
  static DDSDestroySubscriptionBase & GetDefault() { static DDSDestroySubscriptionBase def; return def; }
};

template <>
struct StormReflTypeInfo<DDSDestroySubscriptionBase>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDC126BCE; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSDestroySubscriptionBase::m_Key; }
};

template <typename Self>
struct StormReflTypeInfo<DDSDestroySubscriptionBase>::field_data<0, Self> : public StormReflTypeInfo<DDSDestroySubscriptionBase>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSDestroySubscriptionBase>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSDestroySubscriptionBase>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD2FBD4E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSDestroySubscriptionBase::m_ObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSDestroySubscriptionBase>::field_data<1, Self> : public StormReflTypeInfo<DDSDestroySubscriptionBase>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ObjectType; }
  void SetDefault() { self.m_ObjectType = StormReflTypeInfo<DDSDestroySubscriptionBase>::GetDefault().m_ObjectType; }
};

template <>
struct StormReflTypeInfo<DDSDestroySubscriptionBase>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_SubscriptionId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x01DAA775; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSDestroySubscriptionBase::m_SubscriptionId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSDestroySubscriptionBase>::field_data<2, Self> : public StormReflTypeInfo<DDSDestroySubscriptionBase>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SubscriptionId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SubscriptionId; }
  void SetDefault() { self.m_SubscriptionId = StormReflTypeInfo<DDSDestroySubscriptionBase>::GetDefault().m_SubscriptionId; }
};

template <>
struct StormReflTypeInfo<DDSSubscriptionDeletedBase>
{
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSSubscriptionDeletedBase"; }
  static constexpr auto GetNameHash() { return 0x4631EDE5; }
  static DDSSubscriptionDeletedBase & GetDefault() { static DDSSubscriptionDeletedBase def; return def; }
};

template <>
struct StormReflTypeInfo<DDSSubscriptionDeletedBase>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ResponderObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6ECD8D43; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSSubscriptionDeletedBase::m_ResponderObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSubscriptionDeletedBase>::field_data<0, Self> : public StormReflTypeInfo<DDSSubscriptionDeletedBase>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ResponderObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ResponderObjectType; }
  void SetDefault() { self.m_ResponderObjectType = StormReflTypeInfo<DDSSubscriptionDeletedBase>::GetDefault().m_ResponderObjectType; }
};

template <>
struct StormReflTypeInfo<DDSSubscriptionDeletedBase>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_ResponderKey"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x47BF66BE; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSSubscriptionDeletedBase::m_ResponderKey; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSubscriptionDeletedBase>::field_data<1, Self> : public StormReflTypeInfo<DDSSubscriptionDeletedBase>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_ResponderKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_ResponderKey; }
  void SetDefault() { self.m_ResponderKey = StormReflTypeInfo<DDSSubscriptionDeletedBase>::GetDefault().m_ResponderKey; }
};

template <>
struct StormReflTypeInfo<DDSSubscriptionDeletedBase>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ResponderMethodId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x28424F94; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSSubscriptionDeletedBase::m_ResponderMethodId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSubscriptionDeletedBase>::field_data<2, Self> : public StormReflTypeInfo<DDSSubscriptionDeletedBase>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ResponderMethodId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ResponderMethodId; }
  void SetDefault() { self.m_ResponderMethodId = StormReflTypeInfo<DDSSubscriptionDeletedBase>::GetDefault().m_ResponderMethodId; }
};

template <>
struct StormReflTypeInfo<DDSSubscriptionDeletedBase>::field_data_static<3>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_SubscriptionId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x01DAA775; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSSubscriptionDeletedBase::m_SubscriptionId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSubscriptionDeletedBase>::field_data<3, Self> : public StormReflTypeInfo<DDSSubscriptionDeletedBase>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SubscriptionId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SubscriptionId; }
  void SetDefault() { self.m_SubscriptionId = StormReflTypeInfo<DDSSubscriptionDeletedBase>::GetDefault().m_SubscriptionId; }
};

template <>
struct StormReflTypeInfo<DDSCreateExistSubscriptionBase>
{
  static constexpr int fields_n = 7;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSCreateExistSubscriptionBase"; }
  static constexpr auto GetNameHash() { return 0xA533D97F; }
  static DDSCreateExistSubscriptionBase & GetDefault() { static DDSCreateExistSubscriptionBase def; return def; }
};

template <>
struct StormReflTypeInfo<DDSCreateExistSubscriptionBase>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDC126BCE; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSCreateExistSubscriptionBase::m_Key; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateExistSubscriptionBase>::field_data<0, Self> : public StormReflTypeInfo<DDSCreateExistSubscriptionBase>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSCreateExistSubscriptionBase>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSCreateExistSubscriptionBase>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD2FBD4E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSCreateExistSubscriptionBase::m_ObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateExistSubscriptionBase>::field_data<1, Self> : public StormReflTypeInfo<DDSCreateExistSubscriptionBase>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ObjectType; }
  void SetDefault() { self.m_ObjectType = StormReflTypeInfo<DDSCreateExistSubscriptionBase>::GetDefault().m_ObjectType; }
};

template <>
struct StormReflTypeInfo<DDSCreateExistSubscriptionBase>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_SubscriptionId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x01DAA775; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSCreateExistSubscriptionBase::m_SubscriptionId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateExistSubscriptionBase>::field_data<2, Self> : public StormReflTypeInfo<DDSCreateExistSubscriptionBase>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SubscriptionId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SubscriptionId; }
  void SetDefault() { self.m_SubscriptionId = StormReflTypeInfo<DDSCreateExistSubscriptionBase>::GetDefault().m_SubscriptionId; }
};

template <>
struct StormReflTypeInfo<DDSCreateExistSubscriptionBase>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ResponderObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6ECD8D43; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSCreateExistSubscriptionBase::m_ResponderObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateExistSubscriptionBase>::field_data<3, Self> : public StormReflTypeInfo<DDSCreateExistSubscriptionBase>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ResponderObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ResponderObjectType; }
  void SetDefault() { self.m_ResponderObjectType = StormReflTypeInfo<DDSCreateExistSubscriptionBase>::GetDefault().m_ResponderObjectType; }
};

template <>
struct StormReflTypeInfo<DDSCreateExistSubscriptionBase>::field_data_static<4>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_ResponderKey"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x47BF66BE; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSCreateExistSubscriptionBase::m_ResponderKey; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateExistSubscriptionBase>::field_data<4, Self> : public StormReflTypeInfo<DDSCreateExistSubscriptionBase>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_ResponderKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_ResponderKey; }
  void SetDefault() { self.m_ResponderKey = StormReflTypeInfo<DDSCreateExistSubscriptionBase>::GetDefault().m_ResponderKey; }
};

template <>
struct StormReflTypeInfo<DDSCreateExistSubscriptionBase>::field_data_static<5>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ResponderMethodId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x28424F94; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &DDSCreateExistSubscriptionBase::m_ResponderMethodId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateExistSubscriptionBase>::field_data<5, Self> : public StormReflTypeInfo<DDSCreateExistSubscriptionBase>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ResponderMethodId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ResponderMethodId; }
  void SetDefault() { self.m_ResponderMethodId = StormReflTypeInfo<DDSCreateExistSubscriptionBase>::GetDefault().m_ResponderMethodId; }
};

template <>
struct StormReflTypeInfo<DDSCreateExistSubscriptionBase>::field_data_static<6>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ReturnArg"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBA1409C0; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &DDSCreateExistSubscriptionBase::m_ReturnArg; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateExistSubscriptionBase>::field_data<6, Self> : public StormReflTypeInfo<DDSCreateExistSubscriptionBase>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ReturnArg; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ReturnArg; }
  void SetDefault() { self.m_ReturnArg = StormReflTypeInfo<DDSCreateExistSubscriptionBase>::GetDefault().m_ReturnArg; }
};

template <>
struct StormReflTypeInfo<DDSCreateDataExistSubscriptionBase>
{
  using MyBase = DDSCreateExistSubscriptionBase;
  static constexpr int fields_n = 0 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSCreateDataExistSubscriptionBase"; }
  static constexpr auto GetNameHash() { return 0xAB2A0345; }
  static DDSCreateDataExistSubscriptionBase & GetDefault() { static DDSCreateDataExistSubscriptionBase def; return def; }
};

template <>
struct StormReflTypeInfo<DDSValidateTokenRequestBase>
{
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSValidateTokenRequestBase"; }
  static constexpr auto GetNameHash() { return 0x67C18764; }
  static DDSValidateTokenRequestBase & GetDefault() { static DDSValidateTokenRequestBase def; return def; }
};

template <>
struct StormReflTypeInfo<DDSValidateTokenRequestBase>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long long
  static constexpr auto GetName() { return "m_RequestId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6DDE17CC; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSValidateTokenRequestBase::m_RequestId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSValidateTokenRequestBase>::field_data<0, Self> : public StormReflTypeInfo<DDSValidateTokenRequestBase>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_RequestId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_RequestId; }
  void SetDefault() { self.m_RequestId = StormReflTypeInfo<DDSValidateTokenRequestBase>::GetDefault().m_RequestId; }
};

template <>
struct StormReflTypeInfo<DDSValidateTokenRequestBase>::field_data_static<1>
{
  using member_type = uint32_t; // unsigned int
  static constexpr auto GetName() { return "m_Token"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD094062A; }
  static constexpr unsigned GetTypeNameHash() { return 0xB306EEF4; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSValidateTokenRequestBase::m_Token; }
};

template <typename Self>
struct StormReflTypeInfo<DDSValidateTokenRequestBase>::field_data<1, Self> : public StormReflTypeInfo<DDSValidateTokenRequestBase>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint32_t> & Get() { return self.m_Token; }
  std::add_const_t<std::remove_reference_t<uint32_t>> & Get() const { return self.m_Token; }
  void SetDefault() { self.m_Token = StormReflTypeInfo<DDSValidateTokenRequestBase>::GetDefault().m_Token; }
};

template <>
struct StormReflTypeInfo<DDSValidateTokenRequestBase>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Type"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x70F58FB9; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSValidateTokenRequestBase::m_Type; }
};

template <typename Self>
struct StormReflTypeInfo<DDSValidateTokenRequestBase>::field_data<2, Self> : public StormReflTypeInfo<DDSValidateTokenRequestBase>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Type; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Type; }
  void SetDefault() { self.m_Type = StormReflTypeInfo<DDSValidateTokenRequestBase>::GetDefault().m_Type; }
};

template <>
struct StormReflTypeInfo<DDSValidateTokenResponseBase>
{
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSValidateTokenResponseBase"; }
  static constexpr auto GetNameHash() { return 0x2B768F1B; }
  static DDSValidateTokenResponseBase & GetDefault() { static DDSValidateTokenResponseBase def; return def; }
};

template <>
struct StormReflTypeInfo<DDSValidateTokenResponseBase>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long long
  static constexpr auto GetName() { return "m_RequestId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6DDE17CC; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSValidateTokenResponseBase::m_RequestId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSValidateTokenResponseBase>::field_data<0, Self> : public StormReflTypeInfo<DDSValidateTokenResponseBase>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_RequestId; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_RequestId; }
  void SetDefault() { self.m_RequestId = StormReflTypeInfo<DDSValidateTokenResponseBase>::GetDefault().m_RequestId; }
};

template <>
struct StormReflTypeInfo<DDSValidateTokenResponseBase>::field_data_static<1>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_Success"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5F99A014; }
  static constexpr unsigned GetTypeNameHash() { return 0xA1B914E5; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSValidateTokenResponseBase::m_Success; }
};

template <typename Self>
struct StormReflTypeInfo<DDSValidateTokenResponseBase>::field_data<1, Self> : public StormReflTypeInfo<DDSValidateTokenResponseBase>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_Success; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_Success; }
  void SetDefault() { self.m_Success = StormReflTypeInfo<DDSValidateTokenResponseBase>::GetDefault().m_Success; }
};

template <>
struct StormReflTypeInfo<DDSValidateTokenResponseBase>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_TokenData"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x92972060; }
  static constexpr unsigned GetTypeNameHash() { return 0x7F29EA9F; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSValidateTokenResponseBase::m_TokenData; }
};

template <typename Self>
struct StormReflTypeInfo<DDSValidateTokenResponseBase>::field_data<2, Self> : public StormReflTypeInfo<DDSValidateTokenResponseBase>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_TokenData; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_TokenData; }
  void SetDefault() { self.m_TokenData = StormReflTypeInfo<DDSValidateTokenResponseBase>::GetDefault().m_TokenData; }
};

namespace StormReflFileInfo
{
  struct DDSSharedMessages
  {
    static const int types_n = 13;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct DDSSharedMessages::type_info<0>
  {
    using type = ::DDSExportedSubscription;
  };

  template <>
  struct DDSSharedMessages::type_info<1>
  {
    using type = ::DDSExportedRequestedSubscription;
  };

  template <>
  struct DDSSharedMessages::type_info<2>
  {
    using type = ::DDSTargetedMessageBase;
  };

  template <>
  struct DDSSharedMessages::type_info<3>
  {
    using type = ::DDSTargetedMessageWithResponderBase;
  };

  template <>
  struct DDSSharedMessages::type_info<4>
  {
    using type = ::DDSResponderCallBase;
  };

  template <>
  struct DDSSharedMessages::type_info<5>
  {
    using type = ::DDSCreateSubscriptionBase;
  };

  template <>
  struct DDSSharedMessages::type_info<6>
  {
    using type = ::DDSCreateDataSubscriptionBase;
  };

  template <>
  struct DDSSharedMessages::type_info<7>
  {
    using type = ::DDSDestroySubscriptionBase;
  };

  template <>
  struct DDSSharedMessages::type_info<8>
  {
    using type = ::DDSSubscriptionDeletedBase;
  };

  template <>
  struct DDSSharedMessages::type_info<9>
  {
    using type = ::DDSCreateExistSubscriptionBase;
  };

  template <>
  struct DDSSharedMessages::type_info<10>
  {
    using type = ::DDSCreateDataExistSubscriptionBase;
  };

  template <>
  struct DDSSharedMessages::type_info<11>
  {
    using type = ::DDSValidateTokenRequestBase;
  };

  template <>
  struct DDSSharedMessages::type_info<12>
  {
    using type = ::DDSValidateTokenResponseBase;
  };

}

