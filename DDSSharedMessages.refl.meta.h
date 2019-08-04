#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "DDSSharedMessages.refl.h"


template <>
struct StormReflTypeInfo<DDSExportedSubscription>
{
  using MyBase = void;
  static constexpr int fields_n = 11;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSExportedSubscription"; }
  static constexpr auto GetNameHash() { return 0xE420CC8A; }
  static constexpr bool HasDefault() { return true; }
  static DDSExportedSubscription & GetDefault() { static DDSExportedSubscription def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSExportedSubscription *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSExportedSubscription *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSExportedSubscription *>(ptr);
    if(typeid(DDSExportedSubscription).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSExportedSubscription *>(ptr);
    if(typeid(DDSExportedSubscription).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_DataPath"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x54AD0850; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSExportedSubscription::m_DataPath; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedSubscription *>(obj); return &ptr->m_DataPath; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedSubscription *>(obj); return &ptr->m_DataPath; }
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
  static constexpr unsigned GetFieldNameHash() { return 0xD0097192; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSExportedSubscription::m_SubscriptionId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedSubscription *>(obj); return &ptr->m_SubscriptionId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedSubscription *>(obj); return &ptr->m_SubscriptionId; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x44270BC4; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSExportedSubscription::m_ResponderKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedSubscription *>(obj); return &ptr->m_ResponderKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedSubscription *>(obj); return &ptr->m_ResponderKey; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x61C42C92; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSExportedSubscription::m_ResponderObjectType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedSubscription *>(obj); return &ptr->m_ResponderObjectType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedSubscription *>(obj); return &ptr->m_ResponderObjectType; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x30ED1712; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSExportedSubscription::m_ResponderMethodId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedSubscription *>(obj); return &ptr->m_ResponderMethodId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedSubscription *>(obj); return &ptr->m_ResponderMethodId; }
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
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ErrorMethodId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3D403BAD; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &DDSExportedSubscription::m_ErrorMethodId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedSubscription *>(obj); return &ptr->m_ErrorMethodId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedSubscription *>(obj); return &ptr->m_ErrorMethodId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data<5, Self> : public StormReflTypeInfo<DDSExportedSubscription>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ErrorMethodId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ErrorMethodId; }
  void SetDefault() { self.m_ErrorMethodId = StormReflTypeInfo<DDSExportedSubscription>::GetDefault().m_ErrorMethodId; }
};

template <>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data_static<6>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ResponderArgs"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x25D684E7; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &DDSExportedSubscription::m_ResponderArgs; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedSubscription *>(obj); return &ptr->m_ResponderArgs; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedSubscription *>(obj); return &ptr->m_ResponderArgs; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data<6, Self> : public StormReflTypeInfo<DDSExportedSubscription>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ResponderArgs; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ResponderArgs; }
  void SetDefault() { self.m_ResponderArgs = StormReflTypeInfo<DDSExportedSubscription>::GetDefault().m_ResponderArgs; }
};

template <>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data_static<7>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_IsDataSubscription"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1FFBB31C; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &DDSExportedSubscription::m_IsDataSubscription; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedSubscription *>(obj); return &ptr->m_IsDataSubscription; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedSubscription *>(obj); return &ptr->m_IsDataSubscription; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data<7, Self> : public StormReflTypeInfo<DDSExportedSubscription>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_IsDataSubscription; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_IsDataSubscription; }
  void SetDefault() { self.m_IsDataSubscription = StormReflTypeInfo<DDSExportedSubscription>::GetDefault().m_IsDataSubscription; }
};

template <>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data_static<8>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_DeltaOnly"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBAF53F0B; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &DDSExportedSubscription::m_DeltaOnly; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedSubscription *>(obj); return &ptr->m_DeltaOnly; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedSubscription *>(obj); return &ptr->m_DeltaOnly; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data<8, Self> : public StormReflTypeInfo<DDSExportedSubscription>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_DeltaOnly; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_DeltaOnly; }
  void SetDefault() { self.m_DeltaOnly = StormReflTypeInfo<DDSExportedSubscription>::GetDefault().m_DeltaOnly; }
};

template <>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data_static<9>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_ForceLoad"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1CAEAF78; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &DDSExportedSubscription::m_ForceLoad; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedSubscription *>(obj); return &ptr->m_ForceLoad; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedSubscription *>(obj); return &ptr->m_ForceLoad; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data<9, Self> : public StormReflTypeInfo<DDSExportedSubscription>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_ForceLoad; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_ForceLoad; }
  void SetDefault() { self.m_ForceLoad = StormReflTypeInfo<DDSExportedSubscription>::GetDefault().m_ForceLoad; }
};

template <>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data_static<10>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_State"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2EA5429B; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &DDSExportedSubscription::m_State; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedSubscription *>(obj); return &ptr->m_State; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedSubscription *>(obj); return &ptr->m_State; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedSubscription>::field_data<10, Self> : public StormReflTypeInfo<DDSExportedSubscription>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_State; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_State; }
  void SetDefault() { self.m_State = StormReflTypeInfo<DDSExportedSubscription>::GetDefault().m_State; }
};

template <>
struct StormReflTypeInfo<DDSExportedRequestedSubscription>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSExportedRequestedSubscription"; }
  static constexpr auto GetNameHash() { return 0x259AC373; }
  static constexpr bool HasDefault() { return true; }
  static DDSExportedRequestedSubscription & GetDefault() { static DDSExportedRequestedSubscription def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSExportedRequestedSubscription *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSExportedRequestedSubscription *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSExportedRequestedSubscription *>(ptr);
    if(typeid(DDSExportedRequestedSubscription).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSExportedRequestedSubscription *>(ptr);
    if(typeid(DDSExportedRequestedSubscription).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSExportedRequestedSubscription>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x79726F4E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSExportedRequestedSubscription::m_Key; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedRequestedSubscription *>(obj); return &ptr->m_Key; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedRequestedSubscription *>(obj); return &ptr->m_Key; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x2C75B4A5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSExportedRequestedSubscription::m_ObjectType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedRequestedSubscription *>(obj); return &ptr->m_ObjectType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedRequestedSubscription *>(obj); return &ptr->m_ObjectType; }
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
  static constexpr unsigned GetFieldNameHash() { return 0xD0097192; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSExportedRequestedSubscription::m_SubscriptionId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedRequestedSubscription *>(obj); return &ptr->m_SubscriptionId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedRequestedSubscription *>(obj); return &ptr->m_SubscriptionId; }
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
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>
{
  using MyBase = void;
  static constexpr int fields_n = 13;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSExportedAggregateRequestedSubscription"; }
  static constexpr auto GetNameHash() { return 0x1FE1AA23; }
  static constexpr bool HasDefault() { return true; }
  static DDSExportedAggregateRequestedSubscription & GetDefault() { static DDSExportedAggregateRequestedSubscription def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSExportedAggregateRequestedSubscription *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSExportedAggregateRequestedSubscription *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSExportedAggregateRequestedSubscription *>(ptr);
    if(typeid(DDSExportedAggregateRequestedSubscription).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSExportedAggregateRequestedSubscription *>(ptr);
    if(typeid(DDSExportedAggregateRequestedSubscription).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_SharedLocalCopyKey"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB13E0DFA; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateRequestedSubscription::m_SharedLocalCopyKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_SharedLocalCopyKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_SharedLocalCopyKey; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data<0, Self> : public StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SharedLocalCopyKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SharedLocalCopyKey; }
  void SetDefault() { self.m_SharedLocalCopyKey = StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::GetDefault().m_SharedLocalCopyKey; }
};

template <>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_SubscriptionId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD0097192; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateRequestedSubscription::m_SubscriptionId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_SubscriptionId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_SubscriptionId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data<1, Self> : public StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SubscriptionId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SubscriptionId; }
  void SetDefault() { self.m_SubscriptionId = StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::GetDefault().m_SubscriptionId; }
};

template <>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x79726F4E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateRequestedSubscription::m_Key; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_Key; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_Key; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data<2, Self> : public StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2C75B4A5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateRequestedSubscription::m_ObjectType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_ObjectType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_ObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data<3, Self> : public StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ObjectType; }
  void SetDefault() { self.m_ObjectType = StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::GetDefault().m_ObjectType; }
};

template <>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<4>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Path"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x35C91E10; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateRequestedSubscription::m_Path; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_Path; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_Path; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data<4, Self> : public StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Path; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Path; }
  void SetDefault() { self.m_Path = StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::GetDefault().m_Path; }
};

template <>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<5>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_ReturnKey"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2AC81FB7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateRequestedSubscription::m_ReturnKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_ReturnKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_ReturnKey; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data<5, Self> : public StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_ReturnKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_ReturnKey; }
  void SetDefault() { self.m_ReturnKey = StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::GetDefault().m_ReturnKey; }
};

template <>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<6>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ReturnObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x557E7697; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateRequestedSubscription::m_ReturnObjectType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_ReturnObjectType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_ReturnObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data<6, Self> : public StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ReturnObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ReturnObjectType; }
  void SetDefault() { self.m_ReturnObjectType = StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::GetDefault().m_ReturnObjectType; }
};

template <>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<7>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ReturnArgs"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xECB44B75; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateRequestedSubscription::m_ReturnArgs; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_ReturnArgs; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_ReturnArgs; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data<7, Self> : public StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ReturnArgs; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ReturnArgs; }
  void SetDefault() { self.m_ReturnArgs = StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::GetDefault().m_ReturnArgs; }
};

template <>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<8>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ReturnMethod"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xADF806C0; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateRequestedSubscription::m_ReturnMethod; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_ReturnMethod; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_ReturnMethod; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data<8, Self> : public StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ReturnMethod; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ReturnMethod; }
  void SetDefault() { self.m_ReturnMethod = StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::GetDefault().m_ReturnMethod; }
};

template <>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<9>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ErrorMethod"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x19B9DF64; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateRequestedSubscription::m_ErrorMethod; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_ErrorMethod; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_ErrorMethod; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data<9, Self> : public StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ErrorMethod; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ErrorMethod; }
  void SetDefault() { self.m_ErrorMethod = StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::GetDefault().m_ErrorMethod; }
};

template <>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<10>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DataGen"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFC528033; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateRequestedSubscription::m_DataGen; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_DataGen; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_DataGen; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data<10, Self> : public StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DataGen; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DataGen; }
  void SetDefault() { self.m_DataGen = StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::GetDefault().m_DataGen; }
};

template <>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<11>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_DataSub"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA409D5E5; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateRequestedSubscription::m_DataSub; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_DataSub; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_DataSub; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data<11, Self> : public StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<11>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_DataSub; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_DataSub; }
  void SetDefault() { self.m_DataSub = StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::GetDefault().m_DataSub; }
};

template <>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<12>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_DataValid"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x778C8019; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 12; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateRequestedSubscription::m_DataValid; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_DataValid; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateRequestedSubscription *>(obj); return &ptr->m_DataValid; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data<12, Self> : public StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::field_data_static<12>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_DataValid; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_DataValid; }
  void SetDefault() { self.m_DataValid = StormReflTypeInfo<DDSExportedAggregateRequestedSubscription>::GetDefault().m_DataValid; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageBase>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSTargetedMessageBase"; }
  static constexpr auto GetNameHash() { return 0x3AF384DD; }
  static constexpr bool HasDefault() { return true; }
  static DDSTargetedMessageBase & GetDefault() { static DDSTargetedMessageBase def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSTargetedMessageBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSTargetedMessageBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSTargetedMessageBase *>(ptr);
    if(typeid(DDSTargetedMessageBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSTargetedMessageBase *>(ptr);
    if(typeid(DDSTargetedMessageBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSTargetedMessageBase>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x79726F4E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageBase::m_Key; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSTargetedMessageBase *>(obj); return &ptr->m_Key; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSTargetedMessageBase *>(obj); return &ptr->m_Key; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x2C75B4A5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageBase::m_ObjectType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSTargetedMessageBase *>(obj); return &ptr->m_ObjectType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSTargetedMessageBase *>(obj); return &ptr->m_ObjectType; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x7F607B90; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageBase::m_MethodId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSTargetedMessageBase *>(obj); return &ptr->m_MethodId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSTargetedMessageBase *>(obj); return &ptr->m_MethodId; }
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
  static constexpr unsigned GetFieldNameHash() { return 0xC9E065FA; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageBase::m_MethodArgs; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSTargetedMessageBase *>(obj); return &ptr->m_MethodArgs; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSTargetedMessageBase *>(obj); return &ptr->m_MethodArgs; }
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
  using MyBase = void;
  static constexpr int fields_n = 9;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSTargetedMessageWithResponderBase"; }
  static constexpr auto GetNameHash() { return 0xBA9BF921; }
  static constexpr bool HasDefault() { return true; }
  static DDSTargetedMessageWithResponderBase & GetDefault() { static DDSTargetedMessageWithResponderBase def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSTargetedMessageWithResponderBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSTargetedMessageWithResponderBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSTargetedMessageWithResponderBase *>(ptr);
    if(typeid(DDSTargetedMessageWithResponderBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSTargetedMessageWithResponderBase *>(ptr);
    if(typeid(DDSTargetedMessageWithResponderBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x79726F4E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponderBase::m_Key; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSTargetedMessageWithResponderBase *>(obj); return &ptr->m_Key; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSTargetedMessageWithResponderBase *>(obj); return &ptr->m_Key; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x2C75B4A5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponderBase::m_ObjectType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSTargetedMessageWithResponderBase *>(obj); return &ptr->m_ObjectType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSTargetedMessageWithResponderBase *>(obj); return &ptr->m_ObjectType; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x7F607B90; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponderBase::m_MethodId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSTargetedMessageWithResponderBase *>(obj); return &ptr->m_MethodId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSTargetedMessageWithResponderBase *>(obj); return &ptr->m_MethodId; }
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
  static constexpr unsigned GetFieldNameHash() { return 0xC9E065FA; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponderBase::m_MethodArgs; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSTargetedMessageWithResponderBase *>(obj); return &ptr->m_MethodArgs; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSTargetedMessageWithResponderBase *>(obj); return &ptr->m_MethodArgs; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x61C42C92; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponderBase::m_ResponderObjectType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSTargetedMessageWithResponderBase *>(obj); return &ptr->m_ResponderObjectType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSTargetedMessageWithResponderBase *>(obj); return &ptr->m_ResponderObjectType; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x44270BC4; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponderBase::m_ResponderKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSTargetedMessageWithResponderBase *>(obj); return &ptr->m_ResponderKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSTargetedMessageWithResponderBase *>(obj); return &ptr->m_ResponderKey; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x30ED1712; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponderBase::m_ResponderMethodId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSTargetedMessageWithResponderBase *>(obj); return &ptr->m_ResponderMethodId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSTargetedMessageWithResponderBase *>(obj); return &ptr->m_ResponderMethodId; }
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
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ErrorMethodId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3D403BAD; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponderBase::m_ErrorMethodId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSTargetedMessageWithResponderBase *>(obj); return &ptr->m_ErrorMethodId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSTargetedMessageWithResponderBase *>(obj); return &ptr->m_ErrorMethodId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data<7, Self> : public StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ErrorMethodId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ErrorMethodId; }
  void SetDefault() { self.m_ErrorMethodId = StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::GetDefault().m_ErrorMethodId; }
};

template <>
struct StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data_static<8>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ReturnArg"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD8D32394; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &DDSTargetedMessageWithResponderBase::m_ReturnArg; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSTargetedMessageWithResponderBase *>(obj); return &ptr->m_ReturnArg; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSTargetedMessageWithResponderBase *>(obj); return &ptr->m_ReturnArg; }
};

template <typename Self>
struct StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data<8, Self> : public StormReflTypeInfo<DDSTargetedMessageWithResponderBase>::field_data_static<8>
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
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSResponderCallBase"; }
  static constexpr auto GetNameHash() { return 0x87E6D78C; }
  static constexpr bool HasDefault() { return true; }
  static DDSResponderCallBase & GetDefault() { static DDSResponderCallBase def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSResponderCallBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSResponderCallBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSResponderCallBase *>(ptr);
    if(typeid(DDSResponderCallBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSResponderCallBase *>(ptr);
    if(typeid(DDSResponderCallBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSResponderCallBase>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x79726F4E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSResponderCallBase::m_Key; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSResponderCallBase *>(obj); return &ptr->m_Key; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSResponderCallBase *>(obj); return &ptr->m_Key; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x2C75B4A5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSResponderCallBase::m_ObjectType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSResponderCallBase *>(obj); return &ptr->m_ObjectType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSResponderCallBase *>(obj); return &ptr->m_ObjectType; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x7F607B90; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSResponderCallBase::m_MethodId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSResponderCallBase *>(obj); return &ptr->m_MethodId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSResponderCallBase *>(obj); return &ptr->m_MethodId; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x25D684E7; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSResponderCallBase::m_ResponderArgs; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSResponderCallBase *>(obj); return &ptr->m_ResponderArgs; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSResponderCallBase *>(obj); return &ptr->m_ResponderArgs; }
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
  static constexpr unsigned GetFieldNameHash() { return 0xC9E065FA; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSResponderCallBase::m_MethodArgs; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSResponderCallBase *>(obj); return &ptr->m_MethodArgs; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSResponderCallBase *>(obj); return &ptr->m_MethodArgs; }
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
  using MyBase = void;
  static constexpr int fields_n = 12;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSCreateSubscriptionBase"; }
  static constexpr auto GetNameHash() { return 0x64CEBCD5; }
  static constexpr bool HasDefault() { return true; }
  static DDSCreateSubscriptionBase & GetDefault() { static DDSCreateSubscriptionBase def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSCreateSubscriptionBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCreateSubscriptionBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSCreateSubscriptionBase *>(ptr);
    if(typeid(DDSCreateSubscriptionBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCreateSubscriptionBase *>(ptr);
    if(typeid(DDSCreateSubscriptionBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_DataPath"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x54AD0850; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSubscriptionBase::m_DataPath; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCreateSubscriptionBase *>(obj); return &ptr->m_DataPath; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCreateSubscriptionBase *>(obj); return &ptr->m_DataPath; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x79726F4E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSubscriptionBase::m_Key; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCreateSubscriptionBase *>(obj); return &ptr->m_Key; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCreateSubscriptionBase *>(obj); return &ptr->m_Key; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x2C75B4A5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSubscriptionBase::m_ObjectType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCreateSubscriptionBase *>(obj); return &ptr->m_ObjectType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCreateSubscriptionBase *>(obj); return &ptr->m_ObjectType; }
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
  static constexpr unsigned GetFieldNameHash() { return 0xD0097192; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSubscriptionBase::m_SubscriptionId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCreateSubscriptionBase *>(obj); return &ptr->m_SubscriptionId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCreateSubscriptionBase *>(obj); return &ptr->m_SubscriptionId; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x61C42C92; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSubscriptionBase::m_ResponderObjectType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCreateSubscriptionBase *>(obj); return &ptr->m_ResponderObjectType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCreateSubscriptionBase *>(obj); return &ptr->m_ResponderObjectType; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x44270BC4; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSubscriptionBase::m_ResponderKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCreateSubscriptionBase *>(obj); return &ptr->m_ResponderKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCreateSubscriptionBase *>(obj); return &ptr->m_ResponderKey; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x30ED1712; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSubscriptionBase::m_ResponderMethodId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCreateSubscriptionBase *>(obj); return &ptr->m_ResponderMethodId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCreateSubscriptionBase *>(obj); return &ptr->m_ResponderMethodId; }
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
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ErrorMethodId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3D403BAD; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSubscriptionBase::m_ErrorMethodId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCreateSubscriptionBase *>(obj); return &ptr->m_ErrorMethodId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCreateSubscriptionBase *>(obj); return &ptr->m_ErrorMethodId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data<7, Self> : public StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ErrorMethodId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ErrorMethodId; }
  void SetDefault() { self.m_ErrorMethodId = StormReflTypeInfo<DDSCreateSubscriptionBase>::GetDefault().m_ErrorMethodId; }
};

template <>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<8>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ReturnArg"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD8D32394; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSubscriptionBase::m_ReturnArg; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCreateSubscriptionBase *>(obj); return &ptr->m_ReturnArg; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCreateSubscriptionBase *>(obj); return &ptr->m_ReturnArg; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data<8, Self> : public StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ReturnArg; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ReturnArg; }
  void SetDefault() { self.m_ReturnArg = StormReflTypeInfo<DDSCreateSubscriptionBase>::GetDefault().m_ReturnArg; }
};

template <>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<9>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_DataSubscription"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1EE0651D; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSubscriptionBase::m_DataSubscription; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCreateSubscriptionBase *>(obj); return &ptr->m_DataSubscription; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCreateSubscriptionBase *>(obj); return &ptr->m_DataSubscription; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data<9, Self> : public StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_DataSubscription; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_DataSubscription; }
  void SetDefault() { self.m_DataSubscription = StormReflTypeInfo<DDSCreateSubscriptionBase>::GetDefault().m_DataSubscription; }
};

template <>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<10>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_DeltaOnly"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xBAF53F0B; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSubscriptionBase::m_DeltaOnly; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCreateSubscriptionBase *>(obj); return &ptr->m_DeltaOnly; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCreateSubscriptionBase *>(obj); return &ptr->m_DeltaOnly; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data<10, Self> : public StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_DeltaOnly; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_DeltaOnly; }
  void SetDefault() { self.m_DeltaOnly = StormReflTypeInfo<DDSCreateSubscriptionBase>::GetDefault().m_DeltaOnly; }
};

template <>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<11>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_ForceLoad"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1CAEAF78; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSubscriptionBase::m_ForceLoad; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCreateSubscriptionBase *>(obj); return &ptr->m_ForceLoad; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCreateSubscriptionBase *>(obj); return &ptr->m_ForceLoad; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data<11, Self> : public StormReflTypeInfo<DDSCreateSubscriptionBase>::field_data_static<11>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_ForceLoad; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_ForceLoad; }
  void SetDefault() { self.m_ForceLoad = StormReflTypeInfo<DDSCreateSubscriptionBase>::GetDefault().m_ForceLoad; }
};

template <>
struct StormReflTypeInfo<DDSDestroySubscriptionBase>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSDestroySubscriptionBase"; }
  static constexpr auto GetNameHash() { return 0xF427137A; }
  static constexpr bool HasDefault() { return true; }
  static DDSDestroySubscriptionBase & GetDefault() { static DDSDestroySubscriptionBase def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSDestroySubscriptionBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSDestroySubscriptionBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSDestroySubscriptionBase *>(ptr);
    if(typeid(DDSDestroySubscriptionBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSDestroySubscriptionBase *>(ptr);
    if(typeid(DDSDestroySubscriptionBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSDestroySubscriptionBase>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x79726F4E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSDestroySubscriptionBase::m_Key; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSDestroySubscriptionBase *>(obj); return &ptr->m_Key; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSDestroySubscriptionBase *>(obj); return &ptr->m_Key; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x2C75B4A5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSDestroySubscriptionBase::m_ObjectType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSDestroySubscriptionBase *>(obj); return &ptr->m_ObjectType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSDestroySubscriptionBase *>(obj); return &ptr->m_ObjectType; }
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
  static constexpr unsigned GetFieldNameHash() { return 0xD0097192; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSDestroySubscriptionBase::m_SubscriptionId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSDestroySubscriptionBase *>(obj); return &ptr->m_SubscriptionId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSDestroySubscriptionBase *>(obj); return &ptr->m_SubscriptionId; }
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
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSSubscriptionDeletedBase"; }
  static constexpr auto GetNameHash() { return 0xA49AD769; }
  static constexpr bool HasDefault() { return true; }
  static DDSSubscriptionDeletedBase & GetDefault() { static DDSSubscriptionDeletedBase def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSSubscriptionDeletedBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSSubscriptionDeletedBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSSubscriptionDeletedBase *>(ptr);
    if(typeid(DDSSubscriptionDeletedBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSSubscriptionDeletedBase *>(ptr);
    if(typeid(DDSSubscriptionDeletedBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSSubscriptionDeletedBase>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x79726F4E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSSubscriptionDeletedBase::m_Key; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSubscriptionDeletedBase *>(obj); return &ptr->m_Key; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSubscriptionDeletedBase *>(obj); return &ptr->m_Key; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSubscriptionDeletedBase>::field_data<0, Self> : public StormReflTypeInfo<DDSSubscriptionDeletedBase>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSSubscriptionDeletedBase>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSSubscriptionDeletedBase>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2C75B4A5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSSubscriptionDeletedBase::m_ObjectType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSubscriptionDeletedBase *>(obj); return &ptr->m_ObjectType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSubscriptionDeletedBase *>(obj); return &ptr->m_ObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSubscriptionDeletedBase>::field_data<1, Self> : public StormReflTypeInfo<DDSSubscriptionDeletedBase>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ObjectType; }
  void SetDefault() { self.m_ObjectType = StormReflTypeInfo<DDSSubscriptionDeletedBase>::GetDefault().m_ObjectType; }
};

template <>
struct StormReflTypeInfo<DDSSubscriptionDeletedBase>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_SubscriptionId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD0097192; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSSubscriptionDeletedBase::m_SubscriptionId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSubscriptionDeletedBase *>(obj); return &ptr->m_SubscriptionId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSubscriptionDeletedBase *>(obj); return &ptr->m_SubscriptionId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSubscriptionDeletedBase>::field_data<2, Self> : public StormReflTypeInfo<DDSSubscriptionDeletedBase>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SubscriptionId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SubscriptionId; }
  void SetDefault() { self.m_SubscriptionId = StormReflTypeInfo<DDSSubscriptionDeletedBase>::GetDefault().m_SubscriptionId; }
};

template <>
struct StormReflTypeInfo<DDSValidateTokenRequestBase>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSValidateTokenRequestBase"; }
  static constexpr auto GetNameHash() { return 0x64B10987; }
  static constexpr bool HasDefault() { return true; }
  static DDSValidateTokenRequestBase & GetDefault() { static DDSValidateTokenRequestBase def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSValidateTokenRequestBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSValidateTokenRequestBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSValidateTokenRequestBase *>(ptr);
    if(typeid(DDSValidateTokenRequestBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSValidateTokenRequestBase *>(ptr);
    if(typeid(DDSValidateTokenRequestBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSValidateTokenRequestBase>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long long
  static constexpr auto GetName() { return "m_RequestId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7D43511A; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSValidateTokenRequestBase::m_RequestId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSValidateTokenRequestBase *>(obj); return &ptr->m_RequestId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSValidateTokenRequestBase *>(obj); return &ptr->m_RequestId; }
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
  static constexpr unsigned GetFieldNameHash() { return 0xD201315B; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSValidateTokenRequestBase::m_Token; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSValidateTokenRequestBase *>(obj); return &ptr->m_Token; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSValidateTokenRequestBase *>(obj); return &ptr->m_Token; }
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
  static constexpr unsigned GetFieldNameHash() { return 0xB243C236; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSValidateTokenRequestBase::m_Type; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSValidateTokenRequestBase *>(obj); return &ptr->m_Type; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSValidateTokenRequestBase *>(obj); return &ptr->m_Type; }
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
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSValidateTokenResponseBase"; }
  static constexpr auto GetNameHash() { return 0x9A90A8D1; }
  static constexpr bool HasDefault() { return true; }
  static DDSValidateTokenResponseBase & GetDefault() { static DDSValidateTokenResponseBase def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSValidateTokenResponseBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSValidateTokenResponseBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSValidateTokenResponseBase *>(ptr);
    if(typeid(DDSValidateTokenResponseBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSValidateTokenResponseBase *>(ptr);
    if(typeid(DDSValidateTokenResponseBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSValidateTokenResponseBase>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long long
  static constexpr auto GetName() { return "m_RequestId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7D43511A; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSValidateTokenResponseBase::m_RequestId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSValidateTokenResponseBase *>(obj); return &ptr->m_RequestId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSValidateTokenResponseBase *>(obj); return &ptr->m_RequestId; }
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
  static constexpr unsigned GetFieldNameHash() { return 0xFAF2AA67; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSValidateTokenResponseBase::m_Success; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSValidateTokenResponseBase *>(obj); return &ptr->m_Success; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSValidateTokenResponseBase *>(obj); return &ptr->m_Success; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x45A2D9E0; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSValidateTokenResponseBase::m_TokenData; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSValidateTokenResponseBase *>(obj); return &ptr->m_TokenData; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSValidateTokenResponseBase *>(obj); return &ptr->m_TokenData; }
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
    static const int types_n = 11;
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
    using type = ::DDSExportedAggregateRequestedSubscription;
  };

  template <>
  struct DDSSharedMessages::type_info<3>
  {
    using type = ::DDSTargetedMessageBase;
  };

  template <>
  struct DDSSharedMessages::type_info<4>
  {
    using type = ::DDSTargetedMessageWithResponderBase;
  };

  template <>
  struct DDSSharedMessages::type_info<5>
  {
    using type = ::DDSResponderCallBase;
  };

  template <>
  struct DDSSharedMessages::type_info<6>
  {
    using type = ::DDSCreateSubscriptionBase;
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
    using type = ::DDSValidateTokenRequestBase;
  };

  template <>
  struct DDSSharedMessages::type_info<10>
  {
    using type = ::DDSValidateTokenResponseBase;
  };

}

