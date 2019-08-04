#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "DDSServerToServerMessages.refl.h"
#include "DDSResponder.refl.meta.h"
#include "DDSSharedMessages.refl.meta.h"


template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>
{
  static constexpr int elems_n = 21;
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
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<13>
{
  static constexpr auto GetName() { return "kCreateSharedLocalCopySubscription"; }
  static constexpr auto GetNameHash() { return 0x88566DDC; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kCreateSharedLocalCopySubscription; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<14>
{
  static constexpr auto GetName() { return "kDestroySharedLocalCopySubscription"; }
  static constexpr auto GetNameHash() { return 0xD758A9EA; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kDestroySharedLocalCopySubscription; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<15>
{
  static constexpr auto GetName() { return "kSharedLocalCopyInit"; }
  static constexpr auto GetNameHash() { return 0x05D3E297; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kSharedLocalCopyInit; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<16>
{
  static constexpr auto GetName() { return "kSharedLocalCopyHostDestroyed"; }
  static constexpr auto GetNameHash() { return 0xF6E0DCB8; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kSharedLocalCopyHostDestroyed; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<17>
{
  static constexpr auto GetName() { return "kSharedLocalCopyChange"; }
  static constexpr auto GetNameHash() { return 0xDC67389D; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kSharedLocalCopyChange; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<18>
{
  static constexpr auto GetName() { return "kSharedLocalCopyFastForward"; }
  static constexpr auto GetNameHash() { return 0xFB59763E; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kSharedLocalCopyFastForward; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<19>
{
  static constexpr auto GetName() { return "kSharedLocalCopyAck"; }
  static constexpr auto GetNameHash() { return 0x896CBA4C; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kSharedLocalCopyAck; }
};

template <>
struct StormReflEnumInfo<DDSServerToServerMessageType>::elems<20>
{
  static constexpr auto GetName() { return "kSharedLocalCopyDatabaseDump"; }
  static constexpr auto GetNameHash() { return 0x1433AAC2; }
  static constexpr auto GetValue() { return DDSServerToServerMessageType::kSharedLocalCopyDatabaseDump; }
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
  static constexpr bool HasDefault() { return true; }
  static DDSServerToServerHandshakeRequest & GetDefault() { static DDSServerToServerHandshakeRequest def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSServerToServerHandshakeRequest *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSServerToServerHandshakeRequest *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSServerToServerHandshakeRequest *>(ptr);
    if(typeid(DDSServerToServerHandshakeRequest).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSServerToServerHandshakeRequest *>(ptr);
    if(typeid(DDSServerToServerHandshakeRequest).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSServerToServerHandshakeRequest>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Version"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2AEEA616; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSServerToServerHandshakeRequest::m_Version; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSServerToServerHandshakeRequest *>(obj); return &ptr->m_Version; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSServerToServerHandshakeRequest *>(obj); return &ptr->m_Version; }
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
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSServerToServerHandshakeRequest::m_NodeId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSServerToServerHandshakeRequest *>(obj); return &ptr->m_NodeId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSServerToServerHandshakeRequest *>(obj); return &ptr->m_NodeId; }
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
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSServerToServerHandshakeRequest::m_Secret; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSServerToServerHandshakeRequest *>(obj); return &ptr->m_Secret; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSServerToServerHandshakeRequest *>(obj); return &ptr->m_Secret; }
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
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSServerToServerHandshakeRequest::m_Challenge; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSServerToServerHandshakeRequest *>(obj); return &ptr->m_Challenge; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSServerToServerHandshakeRequest *>(obj); return &ptr->m_Challenge; }
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
  static constexpr bool HasDefault() { return true; }
  static DDSServerToServerHandshakeResponse & GetDefault() { static DDSServerToServerHandshakeResponse def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSServerToServerHandshakeResponse *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSServerToServerHandshakeResponse *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSServerToServerHandshakeResponse *>(ptr);
    if(typeid(DDSServerToServerHandshakeResponse).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSServerToServerHandshakeResponse *>(ptr);
    if(typeid(DDSServerToServerHandshakeResponse).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSServerToServerHandshakeResponse>::field_data_static<0>
{
  using member_type = DDSNodeId; // unsigned int
  static constexpr auto GetName() { return "m_NodeId"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x445D404F; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSServerToServerHandshakeResponse::m_NodeId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSServerToServerHandshakeResponse *>(obj); return &ptr->m_NodeId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSServerToServerHandshakeResponse *>(obj); return &ptr->m_NodeId; }
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
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSServerToServerHandshakeResponse::m_Secret; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSServerToServerHandshakeResponse *>(obj); return &ptr->m_Secret; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSServerToServerHandshakeResponse *>(obj); return &ptr->m_Secret; }
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
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSServerToServerHandshakeResponse::m_Challenge; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSServerToServerHandshakeResponse *>(obj); return &ptr->m_Challenge; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSServerToServerHandshakeResponse *>(obj); return &ptr->m_Challenge; }
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
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSServerToServerHandshakeResponse::m_ChallengeResponse; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSServerToServerHandshakeResponse *>(obj); return &ptr->m_ChallengeResponse; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSServerToServerHandshakeResponse *>(obj); return &ptr->m_ChallengeResponse; }
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
  static constexpr bool HasDefault() { return true; }
  static DDSServerToServerHandshakeFinalize & GetDefault() { static DDSServerToServerHandshakeFinalize def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSServerToServerHandshakeFinalize *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSServerToServerHandshakeFinalize *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSServerToServerHandshakeFinalize *>(ptr);
    if(typeid(DDSServerToServerHandshakeFinalize).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSServerToServerHandshakeFinalize *>(ptr);
    if(typeid(DDSServerToServerHandshakeFinalize).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSServerToServerHandshakeFinalize>::field_data_static<0>
{
  using member_type = unsigned long long; // unsigned long long
  static constexpr auto GetName() { return "m_Challenge"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0B29A84A; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSServerToServerHandshakeFinalize::m_Challenge; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSServerToServerHandshakeFinalize *>(obj); return &ptr->m_Challenge; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSServerToServerHandshakeFinalize *>(obj); return &ptr->m_Challenge; }
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
  static constexpr bool HasDefault() { return true; }
  static DDSExportedMessage & GetDefault() { static DDSExportedMessage def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSExportedMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSExportedMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSExportedMessage *>(ptr);
    if(typeid(DDSExportedMessage).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSExportedMessage *>(ptr);
    if(typeid(DDSExportedMessage).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSExportedMessage>::field_data_static<0>
{
  using member_type = DDSServerToServerMessageType; // DDSServerToServerMessageType
  static constexpr auto GetName() { return "m_Type"; }
  static constexpr auto GetType() { return "DDSServerToServerMessageType"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB243C236; }
  static constexpr unsigned GetTypeNameHash() { return 0xF571F29B; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSExportedMessage::m_Type; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedMessage *>(obj); return &ptr->m_Type; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedMessage *>(obj); return &ptr->m_Type; }
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
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSExportedMessage::m_Message; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedMessage *>(obj); return &ptr->m_Message; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedMessage *>(obj); return &ptr->m_Message; }
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
struct StormReflTypeInfo<DDSExportedAggregateSubscriptionChange>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSExportedAggregateSubscriptionChange"; }
  static constexpr auto GetNameHash() { return 0x132F7E4C; }
  static constexpr bool HasDefault() { return true; }
  static DDSExportedAggregateSubscriptionChange & GetDefault() { static DDSExportedAggregateSubscriptionChange def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSExportedAggregateSubscriptionChange *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSExportedAggregateSubscriptionChange *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSExportedAggregateSubscriptionChange *>(ptr);
    if(typeid(DDSExportedAggregateSubscriptionChange).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSExportedAggregateSubscriptionChange *>(ptr);
    if(typeid(DDSExportedAggregateSubscriptionChange).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSExportedAggregateSubscriptionChange>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Change"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0D68A9E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateSubscriptionChange::m_Change; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateSubscriptionChange *>(obj); return &ptr->m_Change; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateSubscriptionChange *>(obj); return &ptr->m_Change; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateSubscriptionChange>::field_data<0, Self> : public StormReflTypeInfo<DDSExportedAggregateSubscriptionChange>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Change; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Change; }
  void SetDefault() { self.m_Change = StormReflTypeInfo<DDSExportedAggregateSubscriptionChange>::GetDefault().m_Change; }
};

template <>
struct StormReflTypeInfo<DDSExportedAggregateSubscriptionChange>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DataGen"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFC528033; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateSubscriptionChange::m_DataGen; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateSubscriptionChange *>(obj); return &ptr->m_DataGen; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateSubscriptionChange *>(obj); return &ptr->m_DataGen; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateSubscriptionChange>::field_data<1, Self> : public StormReflTypeInfo<DDSExportedAggregateSubscriptionChange>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DataGen; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DataGen; }
  void SetDefault() { self.m_DataGen = StormReflTypeInfo<DDSExportedAggregateSubscriptionChange>::GetDefault().m_DataGen; }
};

template <>
struct StormReflTypeInfo<DDSExportedAggregateSubscriptionChange>::field_data_static<2>
{
  using member_type = std::vector<std::pair<DDSNodeId, DDSKey> >; // std::vector<std::pair<unsigned int, unsigned long long>, std::allocator<std::pair<unsigned int, unsigned long long> > >
  static constexpr auto GetName() { return "m_PendingAckNodes"; }
  static constexpr auto GetType() { return "std::vector<std::pair<unsigned int, unsigned long long>, std::allocator<std::pair<unsigned int, unsigned long long> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4C90E874; }
  static constexpr unsigned GetTypeNameHash() { return 0xD6263F31; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateSubscriptionChange::m_PendingAckNodes; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateSubscriptionChange *>(obj); return &ptr->m_PendingAckNodes; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateSubscriptionChange *>(obj); return &ptr->m_PendingAckNodes; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateSubscriptionChange>::field_data<2, Self> : public StormReflTypeInfo<DDSExportedAggregateSubscriptionChange>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::pair<DDSNodeId, DDSKey> >> & Get() { return self.m_PendingAckNodes; }
  std::add_const_t<std::remove_reference_t<std::vector<std::pair<DDSNodeId, DDSKey> >>> & Get() const { return self.m_PendingAckNodes; }
  void SetDefault() { self.m_PendingAckNodes = StormReflTypeInfo<DDSExportedAggregateSubscriptionChange>::GetDefault().m_PendingAckNodes; }
};

template <>
struct StormReflTypeInfo<DDSExportedAggregateSubscriptionChange>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_WaitForAllClearGen"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4DC35554; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateSubscriptionChange::m_WaitForAllClearGen; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateSubscriptionChange *>(obj); return &ptr->m_WaitForAllClearGen; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateSubscriptionChange *>(obj); return &ptr->m_WaitForAllClearGen; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateSubscriptionChange>::field_data<3, Self> : public StormReflTypeInfo<DDSExportedAggregateSubscriptionChange>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_WaitForAllClearGen; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_WaitForAllClearGen; }
  void SetDefault() { self.m_WaitForAllClearGen = StormReflTypeInfo<DDSExportedAggregateSubscriptionChange>::GetDefault().m_WaitForAllClearGen; }
};

template <>
struct StormReflTypeInfo<DDSExportedAggregateSubscription>
{
  using MyBase = void;
  static constexpr int fields_n = 7;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSExportedAggregateSubscription"; }
  static constexpr auto GetNameHash() { return 0xD3C648CF; }
  static constexpr bool HasDefault() { return true; }
  static DDSExportedAggregateSubscription & GetDefault() { static DDSExportedAggregateSubscription def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSExportedAggregateSubscription *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSExportedAggregateSubscription *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSExportedAggregateSubscription *>(ptr);
    if(typeid(DDSExportedAggregateSubscription).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSExportedAggregateSubscription *>(ptr);
    if(typeid(DDSExportedAggregateSubscription).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSExportedAggregateSubscription>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_SharedLocalCopyKey"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB13E0DFA; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateSubscription::m_SharedLocalCopyKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateSubscription *>(obj); return &ptr->m_SharedLocalCopyKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateSubscription *>(obj); return &ptr->m_SharedLocalCopyKey; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateSubscription>::field_data<0, Self> : public StormReflTypeInfo<DDSExportedAggregateSubscription>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SharedLocalCopyKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SharedLocalCopyKey; }
  void SetDefault() { self.m_SharedLocalCopyKey = StormReflTypeInfo<DDSExportedAggregateSubscription>::GetDefault().m_SharedLocalCopyKey; }
};

template <>
struct StormReflTypeInfo<DDSExportedAggregateSubscription>::field_data_static<1>
{
  using member_type = std::vector<DDSExportedAggregateSubscriptionChange>; // std::vector<DDSExportedAggregateSubscriptionChange, std::allocator<DDSExportedAggregateSubscriptionChange> >
  static constexpr auto GetName() { return "m_Changes"; }
  static constexpr auto GetType() { return "std::vector<DDSExportedAggregateSubscriptionChange, std::allocator<DDSExportedAggregateSubscriptionChange> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB5D2CDE8; }
  static constexpr unsigned GetTypeNameHash() { return 0xA0FBD99A; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateSubscription::m_Changes; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateSubscription *>(obj); return &ptr->m_Changes; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateSubscription *>(obj); return &ptr->m_Changes; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateSubscription>::field_data<1, Self> : public StormReflTypeInfo<DDSExportedAggregateSubscription>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSExportedAggregateSubscriptionChange>> & Get() { return self.m_Changes; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSExportedAggregateSubscriptionChange>>> & Get() const { return self.m_Changes; }
  void SetDefault() { self.m_Changes = StormReflTypeInfo<DDSExportedAggregateSubscription>::GetDefault().m_Changes; }
};

template <>
struct StormReflTypeInfo<DDSExportedAggregateSubscription>::field_data_static<2>
{
  using member_type = std::vector<std::pair<DDSNodeId, DDSKey> >; // std::vector<std::pair<unsigned int, unsigned long long>, std::allocator<std::pair<unsigned int, unsigned long long> > >
  static constexpr auto GetName() { return "m_SubscribedNodes"; }
  static constexpr auto GetType() { return "std::vector<std::pair<unsigned int, unsigned long long>, std::allocator<std::pair<unsigned int, unsigned long long> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2BE503C3; }
  static constexpr unsigned GetTypeNameHash() { return 0xD6263F31; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateSubscription::m_SubscribedNodes; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateSubscription *>(obj); return &ptr->m_SubscribedNodes; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateSubscription *>(obj); return &ptr->m_SubscribedNodes; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateSubscription>::field_data<2, Self> : public StormReflTypeInfo<DDSExportedAggregateSubscription>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::pair<DDSNodeId, DDSKey> >> & Get() { return self.m_SubscribedNodes; }
  std::add_const_t<std::remove_reference_t<std::vector<std::pair<DDSNodeId, DDSKey> >>> & Get() const { return self.m_SubscribedNodes; }
  void SetDefault() { self.m_SubscribedNodes = StormReflTypeInfo<DDSExportedAggregateSubscription>::GetDefault().m_SubscribedNodes; }
};

template <>
struct StormReflTypeInfo<DDSExportedAggregateSubscription>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_DataPath"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x54AD0850; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateSubscription::m_DataPath; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateSubscription *>(obj); return &ptr->m_DataPath; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateSubscription *>(obj); return &ptr->m_DataPath; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateSubscription>::field_data<3, Self> : public StormReflTypeInfo<DDSExportedAggregateSubscription>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_DataPath; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_DataPath; }
  void SetDefault() { self.m_DataPath = StormReflTypeInfo<DDSExportedAggregateSubscription>::GetDefault().m_DataPath; }
};

template <>
struct StormReflTypeInfo<DDSExportedAggregateSubscription>::field_data_static<4>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_HasChangesWaiting"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3AC6AD48; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateSubscription::m_HasChangesWaiting; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateSubscription *>(obj); return &ptr->m_HasChangesWaiting; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateSubscription *>(obj); return &ptr->m_HasChangesWaiting; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateSubscription>::field_data<4, Self> : public StormReflTypeInfo<DDSExportedAggregateSubscription>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_HasChangesWaiting; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_HasChangesWaiting; }
  void SetDefault() { self.m_HasChangesWaiting = StormReflTypeInfo<DDSExportedAggregateSubscription>::GetDefault().m_HasChangesWaiting; }
};

template <>
struct StormReflTypeInfo<DDSExportedAggregateSubscription>::field_data_static<5>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_DataSubscription"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1EE0651D; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateSubscription::m_DataSubscription; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateSubscription *>(obj); return &ptr->m_DataSubscription; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateSubscription *>(obj); return &ptr->m_DataSubscription; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateSubscription>::field_data<5, Self> : public StormReflTypeInfo<DDSExportedAggregateSubscription>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_DataSubscription; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_DataSubscription; }
  void SetDefault() { self.m_DataSubscription = StormReflTypeInfo<DDSExportedAggregateSubscription>::GetDefault().m_DataSubscription; }
};

template <>
struct StormReflTypeInfo<DDSExportedAggregateSubscription>::field_data_static<6>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DataGen"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFC528033; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &DDSExportedAggregateSubscription::m_DataGen; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedAggregateSubscription *>(obj); return &ptr->m_DataGen; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedAggregateSubscription *>(obj); return &ptr->m_DataGen; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedAggregateSubscription>::field_data<6, Self> : public StormReflTypeInfo<DDSExportedAggregateSubscription>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DataGen; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DataGen; }
  void SetDefault() { self.m_DataGen = StormReflTypeInfo<DDSExportedAggregateSubscription>::GetDefault().m_DataGen; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>
{
  using MyBase = void;
  static constexpr int fields_n = 12;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSExportedObject"; }
  static constexpr auto GetNameHash() { return 0xE6435CE3; }
  static constexpr bool HasDefault() { return true; }
  static DDSExportedObject & GetDefault() { static DDSExportedObject def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSExportedObject *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSExportedObject *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSExportedObject *>(ptr);
    if(typeid(DDSExportedObject).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSExportedObject *>(ptr);
    if(typeid(DDSExportedObject).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x79726F4E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_Key; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedObject *>(obj); return &ptr->m_Key; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedObject *>(obj); return &ptr->m_Key; }
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
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_State; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedObject *>(obj); return &ptr->m_State; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedObject *>(obj); return &ptr->m_State; }
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
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_ActiveObject; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedObject *>(obj); return &ptr->m_ActiveObject; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedObject *>(obj); return &ptr->m_ActiveObject; }
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
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_DatabaseObject; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedObject *>(obj); return &ptr->m_DatabaseObject; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedObject *>(obj); return &ptr->m_DatabaseObject; }
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
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ObjectDataGen"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB5D8CDED; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_ObjectDataGen; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedObject *>(obj); return &ptr->m_ObjectDataGen; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedObject *>(obj); return &ptr->m_ObjectDataGen; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<4, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ObjectDataGen; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ObjectDataGen; }
  void SetDefault() { self.m_ObjectDataGen = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_ObjectDataGen; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<5>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DatabaseDataGen"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2A21EEB7; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_DatabaseDataGen; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedObject *>(obj); return &ptr->m_DatabaseDataGen; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedObject *>(obj); return &ptr->m_DatabaseDataGen; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<5, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DatabaseDataGen; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DatabaseDataGen; }
  void SetDefault() { self.m_DatabaseDataGen = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_DatabaseDataGen; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<6>
{
  using member_type = std::vector<DDSExportedMessage>; // std::vector<DDSExportedMessage, std::allocator<DDSExportedMessage> >
  static constexpr auto GetName() { return "m_PendingMessages"; }
  static constexpr auto GetType() { return "std::vector<DDSExportedMessage, std::allocator<DDSExportedMessage> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2C42FDAA; }
  static constexpr unsigned GetTypeNameHash() { return 0x6C768773; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_PendingMessages; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedObject *>(obj); return &ptr->m_PendingMessages; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedObject *>(obj); return &ptr->m_PendingMessages; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<6, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSExportedMessage>> & Get() { return self.m_PendingMessages; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSExportedMessage>>> & Get() const { return self.m_PendingMessages; }
  void SetDefault() { self.m_PendingMessages = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_PendingMessages; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<7>
{
  using member_type = std::vector<DDSExportedSubscription>; // std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> >
  static constexpr auto GetName() { return "m_Subscriptions"; }
  static constexpr auto GetType() { return "std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA001CC15; }
  static constexpr unsigned GetTypeNameHash() { return 0x1CD204EB; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_Subscriptions; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedObject *>(obj); return &ptr->m_Subscriptions; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedObject *>(obj); return &ptr->m_Subscriptions; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<7, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSExportedSubscription>> & Get() { return self.m_Subscriptions; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSExportedSubscription>>> & Get() const { return self.m_Subscriptions; }
  void SetDefault() { self.m_Subscriptions = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_Subscriptions; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<8>
{
  using member_type = std::vector<DDSExportedRequestedSubscription>; // std::vector<DDSExportedRequestedSubscription, std::allocator<DDSExportedRequestedSubscription> >
  static constexpr auto GetName() { return "m_RequestedSubscriptions"; }
  static constexpr auto GetType() { return "std::vector<DDSExportedRequestedSubscription, std::allocator<DDSExportedRequestedSubscription> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1FA2F1D7; }
  static constexpr unsigned GetTypeNameHash() { return 0xC0089DA6; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 8; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_RequestedSubscriptions; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedObject *>(obj); return &ptr->m_RequestedSubscriptions; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedObject *>(obj); return &ptr->m_RequestedSubscriptions; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<8, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<8>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSExportedRequestedSubscription>> & Get() { return self.m_RequestedSubscriptions; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSExportedRequestedSubscription>>> & Get() const { return self.m_RequestedSubscriptions; }
  void SetDefault() { self.m_RequestedSubscriptions = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_RequestedSubscriptions; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<9>
{
  using member_type = std::vector<DDSExportedAggregateSubscription>; // std::vector<DDSExportedAggregateSubscription, std::allocator<DDSExportedAggregateSubscription> >
  static constexpr auto GetName() { return "m_AggregateSubscriptions"; }
  static constexpr auto GetType() { return "std::vector<DDSExportedAggregateSubscription, std::allocator<DDSExportedAggregateSubscription> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDD8352FB; }
  static constexpr unsigned GetTypeNameHash() { return 0xEE891514; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 9; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_AggregateSubscriptions; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedObject *>(obj); return &ptr->m_AggregateSubscriptions; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedObject *>(obj); return &ptr->m_AggregateSubscriptions; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<9, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<9>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSExportedAggregateSubscription>> & Get() { return self.m_AggregateSubscriptions; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSExportedAggregateSubscription>>> & Get() const { return self.m_AggregateSubscriptions; }
  void SetDefault() { self.m_AggregateSubscriptions = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_AggregateSubscriptions; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<10>
{
  using member_type = std::vector<DDSExportedAggregateRequestedSubscription>; // std::vector<DDSExportedAggregateRequestedSubscription, std::allocator<DDSExportedAggregateRequestedSubscription> >
  static constexpr auto GetName() { return "m_RequestedAggregateSubscriptions"; }
  static constexpr auto GetType() { return "std::vector<DDSExportedAggregateRequestedSubscription, std::allocator<DDSExportedAggregateRequestedSubscription> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xC8A557CA; }
  static constexpr unsigned GetTypeNameHash() { return 0x98A2ECF2; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 10; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_RequestedAggregateSubscriptions; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedObject *>(obj); return &ptr->m_RequestedAggregateSubscriptions; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedObject *>(obj); return &ptr->m_RequestedAggregateSubscriptions; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<10, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<10>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSExportedAggregateRequestedSubscription>> & Get() { return self.m_RequestedAggregateSubscriptions; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSExportedAggregateRequestedSubscription>>> & Get() const { return self.m_RequestedAggregateSubscriptions; }
  void SetDefault() { self.m_RequestedAggregateSubscriptions = StormReflTypeInfo<DDSExportedObject>::GetDefault().m_RequestedAggregateSubscriptions; }
};

template <>
struct StormReflTypeInfo<DDSExportedObject>::field_data_static<11>
{
  using member_type = std::vector<std::pair<int, std::vector<DDSExportedSubscription> > >; // std::vector<std::pair<int, std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> > >, std::allocator<std::pair<int, std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> > > > >
  static constexpr auto GetName() { return "m_SharedSubscriptions"; }
  static constexpr auto GetType() { return "std::vector<std::pair<int, std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> > >, std::allocator<std::pair<int, std::vector<DDSExportedSubscription, std::allocator<DDSExportedSubscription> > > > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDEEB192F; }
  static constexpr unsigned GetTypeNameHash() { return 0x9F2C3407; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 11; }
  static constexpr auto GetMemberPtr() { return &DDSExportedObject::m_SharedSubscriptions; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSExportedObject *>(obj); return &ptr->m_SharedSubscriptions; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSExportedObject *>(obj); return &ptr->m_SharedSubscriptions; }
};

template <typename Self>
struct StormReflTypeInfo<DDSExportedObject>::field_data<11, Self> : public StormReflTypeInfo<DDSExportedObject>::field_data_static<11>
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
  static constexpr int fields_n = 6;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSDataObjectListSync"; }
  static constexpr auto GetNameHash() { return 0xD5BF11BC; }
  static constexpr bool HasDefault() { return true; }
  static DDSDataObjectListSync & GetDefault() { static DDSDataObjectListSync def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSDataObjectListSync *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSDataObjectListSync *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSDataObjectListSync *>(ptr);
    if(typeid(DDSDataObjectListSync).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSDataObjectListSync *>(ptr);
    if(typeid(DDSDataObjectListSync).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<0>
{
  using member_type = DDSNodeId; // unsigned int
  static constexpr auto GetName() { return "m_TargetNode"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2D8F95B9; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSDataObjectListSync::m_TargetNode; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSDataObjectListSync *>(obj); return &ptr->m_TargetNode; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSDataObjectListSync *>(obj); return &ptr->m_TargetNode; }
};

template <typename Self>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data<0, Self> : public StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSNodeId> & Get() { return self.m_TargetNode; }
  std::add_const_t<std::remove_reference_t<DDSNodeId>> & Get() const { return self.m_TargetNode; }
  void SetDefault() { self.m_TargetNode = StormReflTypeInfo<DDSDataObjectListSync>::GetDefault().m_TargetNode; }
};

template <>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DataObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x31DC1DA8; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSDataObjectListSync::m_DataObjectType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSDataObjectListSync *>(obj); return &ptr->m_DataObjectType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSDataObjectListSync *>(obj); return &ptr->m_DataObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data<1, Self> : public StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DataObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DataObjectType; }
  void SetDefault() { self.m_DataObjectType = StormReflTypeInfo<DDSDataObjectListSync>::GetDefault().m_DataObjectType; }
};

template <>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_RoutingTableGen"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x608D0035; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSDataObjectListSync::m_RoutingTableGen; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSDataObjectListSync *>(obj); return &ptr->m_RoutingTableGen; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSDataObjectListSync *>(obj); return &ptr->m_RoutingTableGen; }
};

template <typename Self>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data<2, Self> : public StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_RoutingTableGen; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_RoutingTableGen; }
  void SetDefault() { self.m_RoutingTableGen = StormReflTypeInfo<DDSDataObjectListSync>::GetDefault().m_RoutingTableGen; }
};

template <>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<3>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_KeyRangeMin"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xDF42EE40; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSDataObjectListSync::m_KeyRangeMin; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSDataObjectListSync *>(obj); return &ptr->m_KeyRangeMin; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSDataObjectListSync *>(obj); return &ptr->m_KeyRangeMin; }
};

template <typename Self>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data<3, Self> : public StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_KeyRangeMin; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_KeyRangeMin; }
  void SetDefault() { self.m_KeyRangeMin = StormReflTypeInfo<DDSDataObjectListSync>::GetDefault().m_KeyRangeMin; }
};

template <>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<4>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_KeyRangeMax"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE34FD119; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSDataObjectListSync::m_KeyRangeMax; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSDataObjectListSync *>(obj); return &ptr->m_KeyRangeMax; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSDataObjectListSync *>(obj); return &ptr->m_KeyRangeMax; }
};

template <typename Self>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data<4, Self> : public StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_KeyRangeMax; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_KeyRangeMax; }
  void SetDefault() { self.m_KeyRangeMax = StormReflTypeInfo<DDSDataObjectListSync>::GetDefault().m_KeyRangeMax; }
};

template <>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<5>
{
  using member_type = std::vector<DDSExportedObject>; // std::vector<DDSExportedObject, std::allocator<DDSExportedObject> >
  static constexpr auto GetName() { return "m_Entities"; }
  static constexpr auto GetType() { return "std::vector<DDSExportedObject, std::allocator<DDSExportedObject> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x27E8B926; }
  static constexpr unsigned GetTypeNameHash() { return 0x88B81936; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &DDSDataObjectListSync::m_Objects; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSDataObjectListSync *>(obj); return &ptr->m_Objects; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSDataObjectListSync *>(obj); return &ptr->m_Objects; }
};

template <typename Self>
struct StormReflTypeInfo<DDSDataObjectListSync>::field_data<5, Self> : public StormReflTypeInfo<DDSDataObjectListSync>::field_data_static<5>
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
  static constexpr bool HasDefault() { return true; }
  static DDSUnlockObject & GetDefault() { static DDSUnlockObject def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSUnlockObject *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSUnlockObject *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSUnlockObject *>(ptr);
    if(typeid(DDSUnlockObject).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSUnlockObject *>(ptr);
    if(typeid(DDSUnlockObject).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSUnlockObject>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x79726F4E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSUnlockObject::m_Key; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSUnlockObject *>(obj); return &ptr->m_Key; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSUnlockObject *>(obj); return &ptr->m_Key; }
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
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSUnlockObject::m_ObjectType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSUnlockObject *>(obj); return &ptr->m_ObjectType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSUnlockObject *>(obj); return &ptr->m_ObjectType; }
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
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSUnlockObject::m_Data; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSUnlockObject *>(obj); return &ptr->m_Data; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSUnlockObject *>(obj); return &ptr->m_Data; }
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
  static constexpr bool HasDefault() { return true; }
  static DDSResponderCallData & GetDefault() { static DDSResponderCallData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSResponderCallData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x87E6D78C == type_name_hash) return static_cast<DDSResponderCallBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSResponderCallData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x87E6D78C == type_name_hash) return static_cast<const DDSResponderCallBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSResponderCallData *>(ptr);
    if(typeid(DDSResponderCallData).hash_code() == type_id_hash) return c;
    if(typeid(DDSResponderCallBase).hash_code() == type_id_hash) return static_cast<DDSResponderCallBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSResponderCallData *>(ptr);
    if(typeid(DDSResponderCallData).hash_code() == type_id_hash) return c;
    if(typeid(DDSResponderCallBase).hash_code() == type_id_hash) return static_cast<const DDSResponderCallBase *>(c);
    return nullptr;
  }

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
  static constexpr bool HasDefault() { return true; }
  static DDSTargetedMessage & GetDefault() { static DDSTargetedMessage def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSTargetedMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x3AF384DD == type_name_hash) return static_cast<DDSTargetedMessageBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSTargetedMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x3AF384DD == type_name_hash) return static_cast<const DDSTargetedMessageBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSTargetedMessage *>(ptr);
    if(typeid(DDSTargetedMessage).hash_code() == type_id_hash) return c;
    if(typeid(DDSTargetedMessageBase).hash_code() == type_id_hash) return static_cast<DDSTargetedMessageBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSTargetedMessage *>(ptr);
    if(typeid(DDSTargetedMessage).hash_code() == type_id_hash) return c;
    if(typeid(DDSTargetedMessageBase).hash_code() == type_id_hash) return static_cast<const DDSTargetedMessageBase *>(c);
    return nullptr;
  }

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
  static constexpr bool HasDefault() { return true; }
  static DDSTargetedMessageWithResponder & GetDefault() { static DDSTargetedMessageWithResponder def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSTargetedMessageWithResponder *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xBA9BF921 == type_name_hash) return static_cast<DDSTargetedMessageWithResponderBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSTargetedMessageWithResponder *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xBA9BF921 == type_name_hash) return static_cast<const DDSTargetedMessageWithResponderBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSTargetedMessageWithResponder *>(ptr);
    if(typeid(DDSTargetedMessageWithResponder).hash_code() == type_id_hash) return c;
    if(typeid(DDSTargetedMessageWithResponderBase).hash_code() == type_id_hash) return static_cast<DDSTargetedMessageWithResponderBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSTargetedMessageWithResponder *>(ptr);
    if(typeid(DDSTargetedMessageWithResponder).hash_code() == type_id_hash) return c;
    if(typeid(DDSTargetedMessageWithResponderBase).hash_code() == type_id_hash) return static_cast<const DDSTargetedMessageWithResponderBase *>(c);
    return nullptr;
  }

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
  static constexpr bool HasDefault() { return true; }
  static DDSCreateSubscription & GetDefault() { static DDSCreateSubscription def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSCreateSubscription *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x64CEBCD5 == type_name_hash) return static_cast<DDSCreateSubscriptionBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCreateSubscription *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x64CEBCD5 == type_name_hash) return static_cast<const DDSCreateSubscriptionBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSCreateSubscription *>(ptr);
    if(typeid(DDSCreateSubscription).hash_code() == type_id_hash) return c;
    if(typeid(DDSCreateSubscriptionBase).hash_code() == type_id_hash) return static_cast<DDSCreateSubscriptionBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCreateSubscription *>(ptr);
    if(typeid(DDSCreateSubscription).hash_code() == type_id_hash) return c;
    if(typeid(DDSCreateSubscriptionBase).hash_code() == type_id_hash) return static_cast<const DDSCreateSubscriptionBase *>(c);
    return nullptr;
  }

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
  static constexpr bool HasDefault() { return true; }
  static DDSDestroySubscription & GetDefault() { static DDSDestroySubscription def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSDestroySubscription *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xF427137A == type_name_hash) return static_cast<DDSDestroySubscriptionBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSDestroySubscription *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xF427137A == type_name_hash) return static_cast<const DDSDestroySubscriptionBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSDestroySubscription *>(ptr);
    if(typeid(DDSDestroySubscription).hash_code() == type_id_hash) return c;
    if(typeid(DDSDestroySubscriptionBase).hash_code() == type_id_hash) return static_cast<DDSDestroySubscriptionBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSDestroySubscription *>(ptr);
    if(typeid(DDSDestroySubscription).hash_code() == type_id_hash) return c;
    if(typeid(DDSDestroySubscriptionBase).hash_code() == type_id_hash) return static_cast<const DDSDestroySubscriptionBase *>(c);
    return nullptr;
  }

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
  static constexpr bool HasDefault() { return true; }
  static DDSSubscriptionDeleted & GetDefault() { static DDSSubscriptionDeleted def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSSubscriptionDeleted *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xA49AD769 == type_name_hash) return static_cast<DDSSubscriptionDeletedBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSSubscriptionDeleted *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xA49AD769 == type_name_hash) return static_cast<const DDSSubscriptionDeletedBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSSubscriptionDeleted *>(ptr);
    if(typeid(DDSSubscriptionDeleted).hash_code() == type_id_hash) return c;
    if(typeid(DDSSubscriptionDeletedBase).hash_code() == type_id_hash) return static_cast<DDSSubscriptionDeletedBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSSubscriptionDeleted *>(ptr);
    if(typeid(DDSSubscriptionDeleted).hash_code() == type_id_hash) return c;
    if(typeid(DDSSubscriptionDeletedBase).hash_code() == type_id_hash) return static_cast<const DDSSubscriptionDeletedBase *>(c);
    return nullptr;
  }

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
  static constexpr bool HasDefault() { return true; }
  static DDSValidateTokenRequest & GetDefault() { static DDSValidateTokenRequest def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSValidateTokenRequest *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x64B10987 == type_name_hash) return static_cast<DDSValidateTokenRequestBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSValidateTokenRequest *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x64B10987 == type_name_hash) return static_cast<const DDSValidateTokenRequestBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSValidateTokenRequest *>(ptr);
    if(typeid(DDSValidateTokenRequest).hash_code() == type_id_hash) return c;
    if(typeid(DDSValidateTokenRequestBase).hash_code() == type_id_hash) return static_cast<DDSValidateTokenRequestBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSValidateTokenRequest *>(ptr);
    if(typeid(DDSValidateTokenRequest).hash_code() == type_id_hash) return c;
    if(typeid(DDSValidateTokenRequestBase).hash_code() == type_id_hash) return static_cast<const DDSValidateTokenRequestBase *>(c);
    return nullptr;
  }

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
  static constexpr bool HasDefault() { return true; }
  static DDSValidateTokenResponse & GetDefault() { static DDSValidateTokenResponse def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSValidateTokenResponse *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x9A90A8D1 == type_name_hash) return static_cast<DDSValidateTokenResponseBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSValidateTokenResponse *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x9A90A8D1 == type_name_hash) return static_cast<const DDSValidateTokenResponseBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSValidateTokenResponse *>(ptr);
    if(typeid(DDSValidateTokenResponse).hash_code() == type_id_hash) return c;
    if(typeid(DDSValidateTokenResponseBase).hash_code() == type_id_hash) return static_cast<DDSValidateTokenResponseBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSValidateTokenResponse *>(ptr);
    if(typeid(DDSValidateTokenResponse).hash_code() == type_id_hash) return c;
    if(typeid(DDSValidateTokenResponseBase).hash_code() == type_id_hash) return static_cast<const DDSValidateTokenResponseBase *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>
{
  using MyBase = void;
  static constexpr int fields_n = 8;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSCreateSharedLocalCopySubscription"; }
  static constexpr auto GetNameHash() { return 0x559D8F9D; }
  static constexpr bool HasDefault() { return true; }
  static DDSCreateSharedLocalCopySubscription & GetDefault() { static DDSCreateSharedLocalCopySubscription def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSCreateSharedLocalCopySubscription *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCreateSharedLocalCopySubscription *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSCreateSharedLocalCopySubscription *>(ptr);
    if(typeid(DDSCreateSharedLocalCopySubscription).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCreateSharedLocalCopySubscription *>(ptr);
    if(typeid(DDSCreateSharedLocalCopySubscription).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x79726F4E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSharedLocalCopySubscription::m_Key; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCreateSharedLocalCopySubscription *>(obj); return &ptr->m_Key; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCreateSharedLocalCopySubscription *>(obj); return &ptr->m_Key; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data<0, Self> : public StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2C75B4A5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSharedLocalCopySubscription::m_ObjectType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCreateSharedLocalCopySubscription *>(obj); return &ptr->m_ObjectType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCreateSharedLocalCopySubscription *>(obj); return &ptr->m_ObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data<1, Self> : public StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ObjectType; }
  void SetDefault() { self.m_ObjectType = StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::GetDefault().m_ObjectType; }
};

template <>
struct StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_SharedLocalCopyKey"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB13E0DFA; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSharedLocalCopySubscription::m_SharedLocalCopyKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCreateSharedLocalCopySubscription *>(obj); return &ptr->m_SharedLocalCopyKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCreateSharedLocalCopySubscription *>(obj); return &ptr->m_SharedLocalCopyKey; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data<2, Self> : public StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SharedLocalCopyKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SharedLocalCopyKey; }
  void SetDefault() { self.m_SharedLocalCopyKey = StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::GetDefault().m_SharedLocalCopyKey; }
};

template <>
struct StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data_static<3>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_SubscriptionId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD0097192; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSharedLocalCopySubscription::m_SubscriptionId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCreateSharedLocalCopySubscription *>(obj); return &ptr->m_SubscriptionId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCreateSharedLocalCopySubscription *>(obj); return &ptr->m_SubscriptionId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data<3, Self> : public StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SubscriptionId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SubscriptionId; }
  void SetDefault() { self.m_SubscriptionId = StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::GetDefault().m_SubscriptionId; }
};

template <>
struct StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data_static<4>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_DataPath"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x54AD0850; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSharedLocalCopySubscription::m_DataPath; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCreateSharedLocalCopySubscription *>(obj); return &ptr->m_DataPath; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCreateSharedLocalCopySubscription *>(obj); return &ptr->m_DataPath; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data<4, Self> : public StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_DataPath; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_DataPath; }
  void SetDefault() { self.m_DataPath = StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::GetDefault().m_DataPath; }
};

template <>
struct StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data_static<5>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_DataSubscription"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x1EE0651D; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSharedLocalCopySubscription::m_DataSubscription; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCreateSharedLocalCopySubscription *>(obj); return &ptr->m_DataSubscription; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCreateSharedLocalCopySubscription *>(obj); return &ptr->m_DataSubscription; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data<5, Self> : public StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_DataSubscription; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_DataSubscription; }
  void SetDefault() { self.m_DataSubscription = StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::GetDefault().m_DataSubscription; }
};

template <>
struct StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data_static<6>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DataGen"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFC528033; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSharedLocalCopySubscription::m_DataGen; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCreateSharedLocalCopySubscription *>(obj); return &ptr->m_DataGen; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCreateSharedLocalCopySubscription *>(obj); return &ptr->m_DataGen; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data<6, Self> : public StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DataGen; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DataGen; }
  void SetDefault() { self.m_DataGen = StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::GetDefault().m_DataGen; }
};

template <>
struct StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data_static<7>
{
  using member_type = DDSNodeId; // unsigned int
  static constexpr auto GetName() { return "m_ReturnNode"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7FD08D92; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 7; }
  static constexpr auto GetMemberPtr() { return &DDSCreateSharedLocalCopySubscription::m_ReturnNode; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCreateSharedLocalCopySubscription *>(obj); return &ptr->m_ReturnNode; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCreateSharedLocalCopySubscription *>(obj); return &ptr->m_ReturnNode; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data<7, Self> : public StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::field_data_static<7>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSNodeId> & Get() { return self.m_ReturnNode; }
  std::add_const_t<std::remove_reference_t<DDSNodeId>> & Get() const { return self.m_ReturnNode; }
  void SetDefault() { self.m_ReturnNode = StormReflTypeInfo<DDSCreateSharedLocalCopySubscription>::GetDefault().m_ReturnNode; }
};

template <>
struct StormReflTypeInfo<DDSDestroySharedLocalCopySubscription>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSDestroySharedLocalCopySubscription"; }
  static constexpr auto GetNameHash() { return 0xD65E130E; }
  static constexpr bool HasDefault() { return true; }
  static DDSDestroySharedLocalCopySubscription & GetDefault() { static DDSDestroySharedLocalCopySubscription def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSDestroySharedLocalCopySubscription *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSDestroySharedLocalCopySubscription *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSDestroySharedLocalCopySubscription *>(ptr);
    if(typeid(DDSDestroySharedLocalCopySubscription).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSDestroySharedLocalCopySubscription *>(ptr);
    if(typeid(DDSDestroySharedLocalCopySubscription).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSDestroySharedLocalCopySubscription>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x79726F4E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSDestroySharedLocalCopySubscription::m_Key; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSDestroySharedLocalCopySubscription *>(obj); return &ptr->m_Key; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSDestroySharedLocalCopySubscription *>(obj); return &ptr->m_Key; }
};

template <typename Self>
struct StormReflTypeInfo<DDSDestroySharedLocalCopySubscription>::field_data<0, Self> : public StormReflTypeInfo<DDSDestroySharedLocalCopySubscription>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSDestroySharedLocalCopySubscription>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSDestroySharedLocalCopySubscription>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2C75B4A5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSDestroySharedLocalCopySubscription::m_ObjectType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSDestroySharedLocalCopySubscription *>(obj); return &ptr->m_ObjectType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSDestroySharedLocalCopySubscription *>(obj); return &ptr->m_ObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSDestroySharedLocalCopySubscription>::field_data<1, Self> : public StormReflTypeInfo<DDSDestroySharedLocalCopySubscription>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ObjectType; }
  void SetDefault() { self.m_ObjectType = StormReflTypeInfo<DDSDestroySharedLocalCopySubscription>::GetDefault().m_ObjectType; }
};

template <>
struct StormReflTypeInfo<DDSDestroySharedLocalCopySubscription>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_SharedLocalCopyKey"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB13E0DFA; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSDestroySharedLocalCopySubscription::m_SharedLocalCopyKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSDestroySharedLocalCopySubscription *>(obj); return &ptr->m_SharedLocalCopyKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSDestroySharedLocalCopySubscription *>(obj); return &ptr->m_SharedLocalCopyKey; }
};

template <typename Self>
struct StormReflTypeInfo<DDSDestroySharedLocalCopySubscription>::field_data<2, Self> : public StormReflTypeInfo<DDSDestroySharedLocalCopySubscription>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SharedLocalCopyKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SharedLocalCopyKey; }
  void SetDefault() { self.m_SharedLocalCopyKey = StormReflTypeInfo<DDSDestroySharedLocalCopySubscription>::GetDefault().m_SharedLocalCopyKey; }
};

template <>
struct StormReflTypeInfo<DDSDestroySharedLocalCopySubscription>::field_data_static<3>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_SubscriptionId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD0097192; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSDestroySharedLocalCopySubscription::m_SubscriptionId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSDestroySharedLocalCopySubscription *>(obj); return &ptr->m_SubscriptionId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSDestroySharedLocalCopySubscription *>(obj); return &ptr->m_SubscriptionId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSDestroySharedLocalCopySubscription>::field_data<3, Self> : public StormReflTypeInfo<DDSDestroySharedLocalCopySubscription>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SubscriptionId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SubscriptionId; }
  void SetDefault() { self.m_SubscriptionId = StormReflTypeInfo<DDSDestroySharedLocalCopySubscription>::GetDefault().m_SubscriptionId; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyInit>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSSharedLocalCopyInit"; }
  static constexpr auto GetNameHash() { return 0xB5391CEB; }
  static constexpr bool HasDefault() { return true; }
  static DDSSharedLocalCopyInit & GetDefault() { static DDSSharedLocalCopyInit def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSSharedLocalCopyInit *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSSharedLocalCopyInit *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSSharedLocalCopyInit *>(ptr);
    if(typeid(DDSSharedLocalCopyInit).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSSharedLocalCopyInit *>(ptr);
    if(typeid(DDSSharedLocalCopyInit).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyInit>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_SharedLocalCopyKey"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB13E0DFA; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyInit::m_SharedLocalCopyKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyInit *>(obj); return &ptr->m_SharedLocalCopyKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyInit *>(obj); return &ptr->m_SharedLocalCopyKey; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyInit>::field_data<0, Self> : public StormReflTypeInfo<DDSSharedLocalCopyInit>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SharedLocalCopyKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SharedLocalCopyKey; }
  void SetDefault() { self.m_SharedLocalCopyKey = StormReflTypeInfo<DDSSharedLocalCopyInit>::GetDefault().m_SharedLocalCopyKey; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyInit>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_SubscriptionId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD0097192; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyInit::m_SubscriptionId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyInit *>(obj); return &ptr->m_SubscriptionId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyInit *>(obj); return &ptr->m_SubscriptionId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyInit>::field_data<1, Self> : public StormReflTypeInfo<DDSSharedLocalCopyInit>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SubscriptionId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SubscriptionId; }
  void SetDefault() { self.m_SubscriptionId = StormReflTypeInfo<DDSSharedLocalCopyInit>::GetDefault().m_SubscriptionId; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyInit>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyInit::m_Data; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyInit *>(obj); return &ptr->m_Data; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyInit *>(obj); return &ptr->m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyInit>::field_data<2, Self> : public StormReflTypeInfo<DDSSharedLocalCopyInit>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<DDSSharedLocalCopyInit>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyInit>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DataGen"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFC528033; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyInit::m_DataGen; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyInit *>(obj); return &ptr->m_DataGen; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyInit *>(obj); return &ptr->m_DataGen; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyInit>::field_data<3, Self> : public StormReflTypeInfo<DDSSharedLocalCopyInit>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DataGen; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DataGen; }
  void SetDefault() { self.m_DataGen = StormReflTypeInfo<DDSSharedLocalCopyInit>::GetDefault().m_DataGen; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyHostDestroyed>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSSharedLocalCopyHostDestroyed"; }
  static constexpr auto GetNameHash() { return 0xB78C002D; }
  static constexpr bool HasDefault() { return true; }
  static DDSSharedLocalCopyHostDestroyed & GetDefault() { static DDSSharedLocalCopyHostDestroyed def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSSharedLocalCopyHostDestroyed *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSSharedLocalCopyHostDestroyed *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSSharedLocalCopyHostDestroyed *>(ptr);
    if(typeid(DDSSharedLocalCopyHostDestroyed).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSSharedLocalCopyHostDestroyed *>(ptr);
    if(typeid(DDSSharedLocalCopyHostDestroyed).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyHostDestroyed>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_SharedLocalCopy"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF469AE04; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyHostDestroyed::m_SharedLocalCopy; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyHostDestroyed *>(obj); return &ptr->m_SharedLocalCopy; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyHostDestroyed *>(obj); return &ptr->m_SharedLocalCopy; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyHostDestroyed>::field_data<0, Self> : public StormReflTypeInfo<DDSSharedLocalCopyHostDestroyed>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SharedLocalCopy; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SharedLocalCopy; }
  void SetDefault() { self.m_SharedLocalCopy = StormReflTypeInfo<DDSSharedLocalCopyHostDestroyed>::GetDefault().m_SharedLocalCopy; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyHostDestroyed>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_SubscriptionId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD0097192; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyHostDestroyed::m_SubscriptionId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyHostDestroyed *>(obj); return &ptr->m_SubscriptionId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyHostDestroyed *>(obj); return &ptr->m_SubscriptionId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyHostDestroyed>::field_data<1, Self> : public StormReflTypeInfo<DDSSharedLocalCopyHostDestroyed>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SubscriptionId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SubscriptionId; }
  void SetDefault() { self.m_SubscriptionId = StormReflTypeInfo<DDSSharedLocalCopyHostDestroyed>::GetDefault().m_SubscriptionId; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyChange>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSSharedLocalCopyChange"; }
  static constexpr auto GetNameHash() { return 0x05E86196; }
  static constexpr bool HasDefault() { return true; }
  static DDSSharedLocalCopyChange & GetDefault() { static DDSSharedLocalCopyChange def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSSharedLocalCopyChange *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSSharedLocalCopyChange *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSSharedLocalCopyChange *>(ptr);
    if(typeid(DDSSharedLocalCopyChange).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSSharedLocalCopyChange *>(ptr);
    if(typeid(DDSSharedLocalCopyChange).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyChange>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_SharedLocalCopy"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF469AE04; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyChange::m_SharedLocalCopy; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyChange *>(obj); return &ptr->m_SharedLocalCopy; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyChange *>(obj); return &ptr->m_SharedLocalCopy; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyChange>::field_data<0, Self> : public StormReflTypeInfo<DDSSharedLocalCopyChange>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SharedLocalCopy; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SharedLocalCopy; }
  void SetDefault() { self.m_SharedLocalCopy = StormReflTypeInfo<DDSSharedLocalCopyChange>::GetDefault().m_SharedLocalCopy; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyChange>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_SubscriptionId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD0097192; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyChange::m_SubscriptionId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyChange *>(obj); return &ptr->m_SubscriptionId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyChange *>(obj); return &ptr->m_SubscriptionId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyChange>::field_data<1, Self> : public StormReflTypeInfo<DDSSharedLocalCopyChange>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SubscriptionId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SubscriptionId; }
  void SetDefault() { self.m_SubscriptionId = StormReflTypeInfo<DDSSharedLocalCopyChange>::GetDefault().m_SubscriptionId; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyChange>::field_data_static<2>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Change"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0D68A9E8; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyChange::m_Change; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyChange *>(obj); return &ptr->m_Change; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyChange *>(obj); return &ptr->m_Change; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyChange>::field_data<2, Self> : public StormReflTypeInfo<DDSSharedLocalCopyChange>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Change; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Change; }
  void SetDefault() { self.m_Change = StormReflTypeInfo<DDSSharedLocalCopyChange>::GetDefault().m_Change; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyChange>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DataGen"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFC528033; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyChange::m_DataGen; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyChange *>(obj); return &ptr->m_DataGen; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyChange *>(obj); return &ptr->m_DataGen; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyChange>::field_data<3, Self> : public StormReflTypeInfo<DDSSharedLocalCopyChange>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DataGen; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DataGen; }
  void SetDefault() { self.m_DataGen = StormReflTypeInfo<DDSSharedLocalCopyChange>::GetDefault().m_DataGen; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyFastForward>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSSharedLocalCopyFastForward"; }
  static constexpr auto GetNameHash() { return 0x801F25EC; }
  static constexpr bool HasDefault() { return true; }
  static DDSSharedLocalCopyFastForward & GetDefault() { static DDSSharedLocalCopyFastForward def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSSharedLocalCopyFastForward *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSSharedLocalCopyFastForward *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSSharedLocalCopyFastForward *>(ptr);
    if(typeid(DDSSharedLocalCopyFastForward).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSSharedLocalCopyFastForward *>(ptr);
    if(typeid(DDSSharedLocalCopyFastForward).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyFastForward>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_SharedLocalCopy"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF469AE04; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyFastForward::m_SharedLocalCopy; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyFastForward *>(obj); return &ptr->m_SharedLocalCopy; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyFastForward *>(obj); return &ptr->m_SharedLocalCopy; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyFastForward>::field_data<0, Self> : public StormReflTypeInfo<DDSSharedLocalCopyFastForward>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SharedLocalCopy; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SharedLocalCopy; }
  void SetDefault() { self.m_SharedLocalCopy = StormReflTypeInfo<DDSSharedLocalCopyFastForward>::GetDefault().m_SharedLocalCopy; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyFastForward>::field_data_static<1>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_SubscriptionId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD0097192; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyFastForward::m_SubscriptionId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyFastForward *>(obj); return &ptr->m_SubscriptionId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyFastForward *>(obj); return &ptr->m_SubscriptionId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyFastForward>::field_data<1, Self> : public StormReflTypeInfo<DDSSharedLocalCopyFastForward>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SubscriptionId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SubscriptionId; }
  void SetDefault() { self.m_SubscriptionId = StormReflTypeInfo<DDSSharedLocalCopyFastForward>::GetDefault().m_SubscriptionId; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyFastForward>::field_data_static<2>
{
  using member_type = std::vector<std::pair<int, std::string> >; // std::vector<std::pair<int, std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::pair<int, std::basic_string<char, std::char_traits<char>, std::allocator<char> > > > >
  static constexpr auto GetName() { return "m_Changes"; }
  static constexpr auto GetType() { return "std::vector<std::pair<int, std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::pair<int, std::basic_string<char, std::char_traits<char>, std::allocator<char> > > > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB5D2CDE8; }
  static constexpr unsigned GetTypeNameHash() { return 0x7AC297EA; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyFastForward::m_Changes; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyFastForward *>(obj); return &ptr->m_Changes; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyFastForward *>(obj); return &ptr->m_Changes; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyFastForward>::field_data<2, Self> : public StormReflTypeInfo<DDSSharedLocalCopyFastForward>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::pair<int, std::string> >> & Get() { return self.m_Changes; }
  std::add_const_t<std::remove_reference_t<std::vector<std::pair<int, std::string> >>> & Get() const { return self.m_Changes; }
  void SetDefault() { self.m_Changes = StormReflTypeInfo<DDSSharedLocalCopyFastForward>::GetDefault().m_Changes; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyFastForward>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DataGen"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFC528033; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyFastForward::m_DataGen; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyFastForward *>(obj); return &ptr->m_DataGen; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyFastForward *>(obj); return &ptr->m_DataGen; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyFastForward>::field_data<3, Self> : public StormReflTypeInfo<DDSSharedLocalCopyFastForward>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DataGen; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DataGen; }
  void SetDefault() { self.m_DataGen = StormReflTypeInfo<DDSSharedLocalCopyFastForward>::GetDefault().m_DataGen; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyAck>
{
  using MyBase = void;
  static constexpr int fields_n = 7;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSSharedLocalCopyAck"; }
  static constexpr auto GetNameHash() { return 0xB30AE436; }
  static constexpr bool HasDefault() { return true; }
  static DDSSharedLocalCopyAck & GetDefault() { static DDSSharedLocalCopyAck def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSSharedLocalCopyAck *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSSharedLocalCopyAck *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSSharedLocalCopyAck *>(ptr);
    if(typeid(DDSSharedLocalCopyAck).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSSharedLocalCopyAck *>(ptr);
    if(typeid(DDSSharedLocalCopyAck).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyAck>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x79726F4E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyAck::m_Key; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyAck *>(obj); return &ptr->m_Key; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyAck *>(obj); return &ptr->m_Key; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyAck>::field_data<0, Self> : public StormReflTypeInfo<DDSSharedLocalCopyAck>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSSharedLocalCopyAck>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyAck>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2C75B4A5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyAck::m_ObjectType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyAck *>(obj); return &ptr->m_ObjectType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyAck *>(obj); return &ptr->m_ObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyAck>::field_data<1, Self> : public StormReflTypeInfo<DDSSharedLocalCopyAck>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ObjectType; }
  void SetDefault() { self.m_ObjectType = StormReflTypeInfo<DDSSharedLocalCopyAck>::GetDefault().m_ObjectType; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyAck>::field_data_static<2>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_SharedLocalCopy"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF469AE04; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyAck::m_SharedLocalCopy; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyAck *>(obj); return &ptr->m_SharedLocalCopy; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyAck *>(obj); return &ptr->m_SharedLocalCopy; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyAck>::field_data<2, Self> : public StormReflTypeInfo<DDSSharedLocalCopyAck>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SharedLocalCopy; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SharedLocalCopy; }
  void SetDefault() { self.m_SharedLocalCopy = StormReflTypeInfo<DDSSharedLocalCopyAck>::GetDefault().m_SharedLocalCopy; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyAck>::field_data_static<3>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_SubscriptionId"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD0097192; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyAck::m_SubscriptionId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyAck *>(obj); return &ptr->m_SubscriptionId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyAck *>(obj); return &ptr->m_SubscriptionId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyAck>::field_data<3, Self> : public StormReflTypeInfo<DDSSharedLocalCopyAck>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_SubscriptionId; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_SubscriptionId; }
  void SetDefault() { self.m_SubscriptionId = StormReflTypeInfo<DDSSharedLocalCopyAck>::GetDefault().m_SubscriptionId; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyAck>::field_data_static<4>
{
  using member_type = DDSNodeId; // unsigned int
  static constexpr auto GetName() { return "m_NodeId"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x445D404F; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyAck::m_NodeId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyAck *>(obj); return &ptr->m_NodeId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyAck *>(obj); return &ptr->m_NodeId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyAck>::field_data<4, Self> : public StormReflTypeInfo<DDSSharedLocalCopyAck>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSNodeId> & Get() { return self.m_NodeId; }
  std::add_const_t<std::remove_reference_t<DDSNodeId>> & Get() const { return self.m_NodeId; }
  void SetDefault() { self.m_NodeId = StormReflTypeInfo<DDSSharedLocalCopyAck>::GetDefault().m_NodeId; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyAck>::field_data_static<5>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DataGen"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFC528033; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyAck::m_DataGen; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyAck *>(obj); return &ptr->m_DataGen; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyAck *>(obj); return &ptr->m_DataGen; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyAck>::field_data<5, Self> : public StormReflTypeInfo<DDSSharedLocalCopyAck>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DataGen; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DataGen; }
  void SetDefault() { self.m_DataGen = StormReflTypeInfo<DDSSharedLocalCopyAck>::GetDefault().m_DataGen; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyAck>::field_data_static<6>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_RoutingTableGen"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x608D0035; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyAck::m_RoutingTableGen; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyAck *>(obj); return &ptr->m_RoutingTableGen; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyAck *>(obj); return &ptr->m_RoutingTableGen; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyAck>::field_data<6, Self> : public StormReflTypeInfo<DDSSharedLocalCopyAck>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_RoutingTableGen; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_RoutingTableGen; }
  void SetDefault() { self.m_RoutingTableGen = StormReflTypeInfo<DDSSharedLocalCopyAck>::GetDefault().m_RoutingTableGen; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>
{
  using MyBase = void;
  static constexpr int fields_n = 7;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSSharedLocalCopyDatabaseElem"; }
  static constexpr auto GetNameHash() { return 0x7C014622; }
  static constexpr bool HasDefault() { return true; }
  static DDSSharedLocalCopyDatabaseElem & GetDefault() { static DDSSharedLocalCopyDatabaseElem def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSSharedLocalCopyDatabaseElem *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSSharedLocalCopyDatabaseElem *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSSharedLocalCopyDatabaseElem *>(ptr);
    if(typeid(DDSSharedLocalCopyDatabaseElem).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSSharedLocalCopyDatabaseElem *>(ptr);
    if(typeid(DDSSharedLocalCopyDatabaseElem).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_DataGen"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFC528033; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyDatabaseElem::m_DataGen; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyDatabaseElem *>(obj); return &ptr->m_DataGen; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyDatabaseElem *>(obj); return &ptr->m_DataGen; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::field_data<0, Self> : public StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_DataGen; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_DataGen; }
  void SetDefault() { self.m_DataGen = StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::GetDefault().m_DataGen; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::field_data_static<1>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyDatabaseElem::m_Data; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyDatabaseElem *>(obj); return &ptr->m_Data; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyDatabaseElem *>(obj); return &ptr->m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::field_data<1, Self> : public StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::field_data_static<2>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_DataSub"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA409D5E5; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyDatabaseElem::m_DataSub; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyDatabaseElem *>(obj); return &ptr->m_DataSub; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyDatabaseElem *>(obj); return &ptr->m_DataSub; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::field_data<2, Self> : public StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_DataSub; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_DataSub; }
  void SetDefault() { self.m_DataSub = StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::GetDefault().m_DataSub; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::field_data_static<3>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_DataValid"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x778C8019; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyDatabaseElem::m_DataValid; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyDatabaseElem *>(obj); return &ptr->m_DataValid; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyDatabaseElem *>(obj); return &ptr->m_DataValid; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::field_data<3, Self> : public StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, bool> & Get() { return self.m_DataValid; }
  std::add_const_t<std::remove_reference_t<bool>> & Get() const { return self.m_DataValid; }
  void SetDefault() { self.m_DataValid = StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::GetDefault().m_DataValid; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::field_data_static<4>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x79726F4E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyDatabaseElem::m_Key; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyDatabaseElem *>(obj); return &ptr->m_Key; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyDatabaseElem *>(obj); return &ptr->m_Key; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::field_data<4, Self> : public StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::field_data_static<5>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2C75B4A5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyDatabaseElem::m_ObjectType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyDatabaseElem *>(obj); return &ptr->m_ObjectType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyDatabaseElem *>(obj); return &ptr->m_ObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::field_data<5, Self> : public StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ObjectType; }
  void SetDefault() { self.m_ObjectType = StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::GetDefault().m_ObjectType; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::field_data_static<6>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Path"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x35C91E10; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 6; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyDatabaseElem::m_Path; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyDatabaseElem *>(obj); return &ptr->m_Path; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyDatabaseElem *>(obj); return &ptr->m_Path; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::field_data<6, Self> : public StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::field_data_static<6>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Path; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Path; }
  void SetDefault() { self.m_Path = StormReflTypeInfo<DDSSharedLocalCopyDatabaseElem>::GetDefault().m_Path; }
};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyDatabaseDump>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSSharedLocalCopyDatabaseDump"; }
  static constexpr auto GetNameHash() { return 0x7C955F69; }
  static constexpr bool HasDefault() { return true; }
  static DDSSharedLocalCopyDatabaseDump & GetDefault() { static DDSSharedLocalCopyDatabaseDump def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSSharedLocalCopyDatabaseDump *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSSharedLocalCopyDatabaseDump *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSSharedLocalCopyDatabaseDump *>(ptr);
    if(typeid(DDSSharedLocalCopyDatabaseDump).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSSharedLocalCopyDatabaseDump *>(ptr);
    if(typeid(DDSSharedLocalCopyDatabaseDump).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSSharedLocalCopyDatabaseDump>::field_data_static<0>
{
  using member_type = std::map<DDSKey, DDSSharedLocalCopyDatabaseElem>; // std::map<unsigned long long, DDSSharedLocalCopyDatabaseElem, std::less<unsigned long long>, std::allocator<std::pair<const unsigned long long, DDSSharedLocalCopyDatabaseElem> > >
  static constexpr auto GetName() { return "m_Copies"; }
  static constexpr auto GetType() { return "std::map<unsigned long long, DDSSharedLocalCopyDatabaseElem, std::less<unsigned long long>, std::allocator<std::pair<const unsigned long long, DDSSharedLocalCopyDatabaseElem> > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x94408454; }
  static constexpr unsigned GetTypeNameHash() { return 0xFD1A5440; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSSharedLocalCopyDatabaseDump::m_Copies; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSSharedLocalCopyDatabaseDump *>(obj); return &ptr->m_Copies; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSSharedLocalCopyDatabaseDump *>(obj); return &ptr->m_Copies; }
};

template <typename Self>
struct StormReflTypeInfo<DDSSharedLocalCopyDatabaseDump>::field_data<0, Self> : public StormReflTypeInfo<DDSSharedLocalCopyDatabaseDump>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::map<DDSKey, DDSSharedLocalCopyDatabaseElem>> & Get() { return self.m_Copies; }
  std::add_const_t<std::remove_reference_t<std::map<DDSKey, DDSSharedLocalCopyDatabaseElem>>> & Get() const { return self.m_Copies; }
  void SetDefault() { self.m_Copies = StormReflTypeInfo<DDSSharedLocalCopyDatabaseDump>::GetDefault().m_Copies; }
};

namespace StormReflFileInfo
{
  struct DDSServerToServerMessages
  {
    static const int types_n = 26;
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
    using type = ::DDSExportedAggregateSubscriptionChange;
  };

  template <>
  struct DDSServerToServerMessages::type_info<5>
  {
    using type = ::DDSExportedAggregateSubscription;
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
    using type = ::DDSDestroySubscription;
  };

  template <>
  struct DDSServerToServerMessages::type_info<14>
  {
    using type = ::DDSSubscriptionDeleted;
  };

  template <>
  struct DDSServerToServerMessages::type_info<15>
  {
    using type = ::DDSValidateTokenRequest;
  };

  template <>
  struct DDSServerToServerMessages::type_info<16>
  {
    using type = ::DDSValidateTokenResponse;
  };

  template <>
  struct DDSServerToServerMessages::type_info<17>
  {
    using type = ::DDSCreateSharedLocalCopySubscription;
  };

  template <>
  struct DDSServerToServerMessages::type_info<18>
  {
    using type = ::DDSDestroySharedLocalCopySubscription;
  };

  template <>
  struct DDSServerToServerMessages::type_info<19>
  {
    using type = ::DDSSharedLocalCopyInit;
  };

  template <>
  struct DDSServerToServerMessages::type_info<20>
  {
    using type = ::DDSSharedLocalCopyHostDestroyed;
  };

  template <>
  struct DDSServerToServerMessages::type_info<21>
  {
    using type = ::DDSSharedLocalCopyChange;
  };

  template <>
  struct DDSServerToServerMessages::type_info<22>
  {
    using type = ::DDSSharedLocalCopyFastForward;
  };

  template <>
  struct DDSServerToServerMessages::type_info<23>
  {
    using type = ::DDSSharedLocalCopyAck;
  };

  template <>
  struct DDSServerToServerMessages::type_info<24>
  {
    using type = ::DDSSharedLocalCopyDatabaseElem;
  };

  template <>
  struct DDSServerToServerMessages::type_info<25>
  {
    using type = ::DDSSharedLocalCopyDatabaseDump;
  };

}

