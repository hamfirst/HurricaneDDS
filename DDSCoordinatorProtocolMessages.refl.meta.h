#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "DDSCoordinatorProtocolMessages.refl.h"
#include "DDSSharedMessages.refl.meta.h"
#include "StormData/StormDataChangeType.refl.meta.h"


template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>
{
  static constexpr int elems_n = 17;
  static constexpr auto GetName() { return "DDSCoordinatorProtocolMessageType"; }
  static constexpr auto GetNameHash() { return 0xDA65B046; }
  template <int N> struct elems { };
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<0>
{
  static constexpr auto GetName() { return "kUnknown"; }
  static constexpr auto GetNameHash() { return 0x175422A1; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kUnknown; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<1>
{
  static constexpr auto GetName() { return "kHandshakeRequest"; }
  static constexpr auto GetNameHash() { return 0x88B9BC9A; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kHandshakeRequest; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<2>
{
  static constexpr auto GetName() { return "kHandshakeResponse"; }
  static constexpr auto GetNameHash() { return 0x4EA2D147; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kHandshakeResponse; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<3>
{
  static constexpr auto GetName() { return "kHandshakeFinalize"; }
  static constexpr auto GetNameHash() { return 0x550329B7; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kHandshakeFinalize; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<4>
{
  static constexpr auto GetName() { return "kNodeInit"; }
  static constexpr auto GetNameHash() { return 0xFC63C623; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kNodeInit; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<5>
{
  static constexpr auto GetName() { return "kRoutingTable"; }
  static constexpr auto GetNameHash() { return 0xB81BBD82; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kRoutingTable; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<6>
{
  static constexpr auto GetName() { return "kRoutingTableAck"; }
  static constexpr auto GetNameHash() { return 0x2316681E; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kRoutingTableAck; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<7>
{
  static constexpr auto GetName() { return "kSyncAllClear"; }
  static constexpr auto GetNameHash() { return 0xB6414C8B; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kSyncAllClear; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<8>
{
  static constexpr auto GetName() { return "kShutDown"; }
  static constexpr auto GetNameHash() { return 0x91FBC714; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kShutDown; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<9>
{
  static constexpr auto GetName() { return "kSharedObjectDelta"; }
  static constexpr auto GetNameHash() { return 0x9C3DB581; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kSharedObjectDelta; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<10>
{
  static constexpr auto GetName() { return "kCPUUsage"; }
  static constexpr auto GetNameHash() { return 0x37B33843; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kCPUUsage; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<11>
{
  static constexpr auto GetName() { return "kResponderCall"; }
  static constexpr auto GetNameHash() { return 0xF561031B; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kResponderCall; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<12>
{
  static constexpr auto GetName() { return "kTargetedMessage"; }
  static constexpr auto GetNameHash() { return 0x646CED86; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kTargetedMessage; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<13>
{
  static constexpr auto GetName() { return "kTargetedMessageResponder"; }
  static constexpr auto GetNameHash() { return 0x0F29BAFC; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kTargetedMessageResponder; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<14>
{
  static constexpr auto GetName() { return "kCreateSubscription"; }
  static constexpr auto GetNameHash() { return 0x6310D904; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kCreateSubscription; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<15>
{
  static constexpr auto GetName() { return "kDestroySubscription"; }
  static constexpr auto GetNameHash() { return 0x005B8D36; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kDestroySubscription; }
};

template <>
struct StormReflEnumInfo<DDSCoordinatorProtocolMessageType>::elems<16>
{
  static constexpr auto GetName() { return "kSubscriptionDeleted"; }
  static constexpr auto GetNameHash() { return 0xFA6CC738; }
  static constexpr auto GetValue() { return DDSCoordinatorProtocolMessageType::kSubscriptionDeleted; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorHandshakeRequest>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSCoordinatorHandshakeRequest"; }
  static constexpr auto GetNameHash() { return 0x5A58FB22; }
  static constexpr bool HasDefault() { return true; }
  static DDSCoordinatorHandshakeRequest & GetDefault() { static DDSCoordinatorHandshakeRequest def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorHandshakeRequest *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorHandshakeRequest *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorHandshakeRequest *>(ptr);
    if(typeid(DDSCoordinatorHandshakeRequest).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorHandshakeRequest *>(ptr);
    if(typeid(DDSCoordinatorHandshakeRequest).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSCoordinatorHandshakeRequest>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long long
  static constexpr auto GetName() { return "m_Challenge"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0B29A84A; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorHandshakeRequest::m_Challenge; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorHandshakeRequest *>(obj); return &ptr->m_Challenge; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorHandshakeRequest *>(obj); return &ptr->m_Challenge; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorHandshakeRequest>::field_data<0, Self> : public StormReflTypeInfo<DDSCoordinatorHandshakeRequest>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_Challenge; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_Challenge; }
  void SetDefault() { self.m_Challenge = StormReflTypeInfo<DDSCoordinatorHandshakeRequest>::GetDefault().m_Challenge; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorHandshakeRequest>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Version"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2AEEA616; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorHandshakeRequest::m_Version; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorHandshakeRequest *>(obj); return &ptr->m_Version; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorHandshakeRequest *>(obj); return &ptr->m_Version; }
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
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSCoordinatorHandshakeResponse"; }
  static constexpr auto GetNameHash() { return 0x8BCA0BBE; }
  static constexpr bool HasDefault() { return true; }
  static DDSCoordinatorHandshakeResponse & GetDefault() { static DDSCoordinatorHandshakeResponse def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorHandshakeResponse *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorHandshakeResponse *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorHandshakeResponse *>(ptr);
    if(typeid(DDSCoordinatorHandshakeResponse).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorHandshakeResponse *>(ptr);
    if(typeid(DDSCoordinatorHandshakeResponse).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSCoordinatorHandshakeResponse>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long long
  static constexpr auto GetName() { return "m_ChallengeResponse"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5C674F6E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorHandshakeResponse::m_ChallengeResponse; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorHandshakeResponse *>(obj); return &ptr->m_ChallengeResponse; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorHandshakeResponse *>(obj); return &ptr->m_ChallengeResponse; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorHandshakeResponse>::field_data<0, Self> : public StormReflTypeInfo<DDSCoordinatorHandshakeResponse>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_ChallengeResponse; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_ChallengeResponse; }
  void SetDefault() { self.m_ChallengeResponse = StormReflTypeInfo<DDSCoordinatorHandshakeResponse>::GetDefault().m_ChallengeResponse; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorHandshakeResponse>::field_data_static<1>
{
  using member_type = uint64_t; // unsigned long long
  static constexpr auto GetName() { return "m_ChallengeRequest"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xFACEC5C3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorHandshakeResponse::m_ChallengeRequest; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorHandshakeResponse *>(obj); return &ptr->m_ChallengeRequest; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorHandshakeResponse *>(obj); return &ptr->m_ChallengeRequest; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorHandshakeResponse>::field_data<1, Self> : public StormReflTypeInfo<DDSCoordinatorHandshakeResponse>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_ChallengeRequest; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_ChallengeRequest; }
  void SetDefault() { self.m_ChallengeRequest = StormReflTypeInfo<DDSCoordinatorHandshakeResponse>::GetDefault().m_ChallengeRequest; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSCoordinatorHandshakeFinalize"; }
  static constexpr auto GetNameHash() { return 0x906BF34E; }
  static constexpr bool HasDefault() { return true; }
  static DDSCoordinatorHandshakeFinalize & GetDefault() { static DDSCoordinatorHandshakeFinalize def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorHandshakeFinalize *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorHandshakeFinalize *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorHandshakeFinalize *>(ptr);
    if(typeid(DDSCoordinatorHandshakeFinalize).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorHandshakeFinalize *>(ptr);
    if(typeid(DDSCoordinatorHandshakeFinalize).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data_static<0>
{
  using member_type = uint64_t; // unsigned long long
  static constexpr auto GetName() { return "m_ChallengeResponse"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5C674F6E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorHandshakeFinalize::m_ChallengeResponse; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorHandshakeFinalize *>(obj); return &ptr->m_ChallengeResponse; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorHandshakeFinalize *>(obj); return &ptr->m_ChallengeResponse; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data<0, Self> : public StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_ChallengeResponse; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_ChallengeResponse; }
  void SetDefault() { self.m_ChallengeResponse = StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::GetDefault().m_ChallengeResponse; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data_static<1>
{
  using member_type = uint32_t; // unsigned int
  static constexpr auto GetName() { return "m_PublicIp"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE5F119C6; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorHandshakeFinalize::m_PublicIp; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorHandshakeFinalize *>(obj); return &ptr->m_PublicIp; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorHandshakeFinalize *>(obj); return &ptr->m_PublicIp; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data<1, Self> : public StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint32_t> & Get() { return self.m_PublicIp; }
  std::add_const_t<std::remove_reference_t<uint32_t>> & Get() const { return self.m_PublicIp; }
  void SetDefault() { self.m_PublicIp = StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::GetDefault().m_PublicIp; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data_static<2>
{
  using member_type = uint16_t; // unsigned short
  static constexpr auto GetName() { return "m_NodePort"; }
  static constexpr auto GetType() { return "unsigned short"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2BC11D5D; }
  static constexpr unsigned GetTypeNameHash() { return 0x3DE16827; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorHandshakeFinalize::m_NodePort; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorHandshakeFinalize *>(obj); return &ptr->m_NodePort; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorHandshakeFinalize *>(obj); return &ptr->m_NodePort; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data<2, Self> : public StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint16_t> & Get() { return self.m_NodePort; }
  std::add_const_t<std::remove_reference_t<uint16_t>> & Get() const { return self.m_NodePort; }
  void SetDefault() { self.m_NodePort = StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::GetDefault().m_NodePort; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data_static<3>
{
  using member_type = std::vector<DDSNodePort>; // std::vector<unsigned short, std::allocator<unsigned short> >
  static constexpr auto GetName() { return "m_EndpointPorts"; }
  static constexpr auto GetType() { return "std::vector<unsigned short, std::allocator<unsigned short> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE6C133B1; }
  static constexpr unsigned GetTypeNameHash() { return 0x072FC70B; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorHandshakeFinalize::m_EndpointPorts; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorHandshakeFinalize *>(obj); return &ptr->m_EndpointPorts; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorHandshakeFinalize *>(obj); return &ptr->m_EndpointPorts; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data<3, Self> : public StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSNodePort>> & Get() { return self.m_EndpointPorts; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSNodePort>>> & Get() const { return self.m_EndpointPorts; }
  void SetDefault() { self.m_EndpointPorts = StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::GetDefault().m_EndpointPorts; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data_static<4>
{
  using member_type = std::vector<DDSNodePort>; // std::vector<unsigned short, std::allocator<unsigned short> >
  static constexpr auto GetName() { return "m_WebsitePorts"; }
  static constexpr auto GetType() { return "std::vector<unsigned short, std::allocator<unsigned short> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB0FC1FC0; }
  static constexpr unsigned GetTypeNameHash() { return 0x072FC70B; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorHandshakeFinalize::m_WebsitePorts; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorHandshakeFinalize *>(obj); return &ptr->m_WebsitePorts; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorHandshakeFinalize *>(obj); return &ptr->m_WebsitePorts; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data<4, Self> : public StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSNodePort>> & Get() { return self.m_WebsitePorts; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSNodePort>>> & Get() const { return self.m_WebsitePorts; }
  void SetDefault() { self.m_WebsitePorts = StormReflTypeInfo<DDSCoordinatorHandshakeFinalize>::GetDefault().m_WebsitePorts; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorNodeInitialization>
{
  using MyBase = void;
  static constexpr int fields_n = 6;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSCoordinatorNodeInitialization"; }
  static constexpr auto GetNameHash() { return 0xAF7CF566; }
  static constexpr bool HasDefault() { return true; }
  static DDSCoordinatorNodeInitialization & GetDefault() { static DDSCoordinatorNodeInitialization def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorNodeInitialization *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorNodeInitialization *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorNodeInitialization *>(ptr);
    if(typeid(DDSCoordinatorNodeInitialization).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorNodeInitialization *>(ptr);
    if(typeid(DDSCoordinatorNodeInitialization).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data_static<0>
{
  using member_type = DDSNodeId; // unsigned int
  static constexpr auto GetName() { return "m_NodeId"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x445D404F; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorNodeInitialization::m_NodeId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorNodeInitialization *>(obj); return &ptr->m_NodeId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorNodeInitialization *>(obj); return &ptr->m_NodeId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data<0, Self> : public StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSNodeId> & Get() { return self.m_NodeId; }
  std::add_const_t<std::remove_reference_t<DDSNodeId>> & Get() const { return self.m_NodeId; }
  void SetDefault() { self.m_NodeId = StormReflTypeInfo<DDSCoordinatorNodeInitialization>::GetDefault().m_NodeId; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data_static<1>
{
  using member_type = uint64_t; // unsigned long long
  static constexpr auto GetName() { return "m_ClientSecret"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD5D9E49E; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorNodeInitialization::m_ClientSecret; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorNodeInitialization *>(obj); return &ptr->m_ClientSecret; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorNodeInitialization *>(obj); return &ptr->m_ClientSecret; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data<1, Self> : public StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_ClientSecret; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_ClientSecret; }
  void SetDefault() { self.m_ClientSecret = StormReflTypeInfo<DDSCoordinatorNodeInitialization>::GetDefault().m_ClientSecret; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data_static<2>
{
  using member_type = uint64_t; // unsigned long long
  static constexpr auto GetName() { return "m_ServerSecret"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD6351A20; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorNodeInitialization::m_ServerSecret; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorNodeInitialization *>(obj); return &ptr->m_ServerSecret; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorNodeInitialization *>(obj); return &ptr->m_ServerSecret; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data<2, Self> : public StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_ServerSecret; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_ServerSecret; }
  void SetDefault() { self.m_ServerSecret = StormReflTypeInfo<DDSCoordinatorNodeInitialization>::GetDefault().m_ServerSecret; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data_static<3>
{
  using member_type = bool; // bool
  static constexpr auto GetName() { return "m_InitialNode"; }
  static constexpr auto GetType() { return "bool"; }
  static constexpr unsigned GetFieldNameHash() { return 0x37F85501; }
  static constexpr unsigned GetTypeNameHash() { return 0x55813692; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorNodeInitialization::m_InitialNode; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorNodeInitialization *>(obj); return &ptr->m_InitialNode; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorNodeInitialization *>(obj); return &ptr->m_InitialNode; }
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
  using member_type = int64_t; // long long
  static constexpr auto GetName() { return "m_NetworkTime"; }
  static constexpr auto GetType() { return "long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8B7AF0AF; }
  static constexpr unsigned GetTypeNameHash() { return 0x40FF8523; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorNodeInitialization::m_NetworkTime; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorNodeInitialization *>(obj); return &ptr->m_NetworkTime; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorNodeInitialization *>(obj); return &ptr->m_NetworkTime; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data<4, Self> : public StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int64_t> & Get() { return self.m_NetworkTime; }
  std::add_const_t<std::remove_reference_t<int64_t>> & Get() const { return self.m_NetworkTime; }
  void SetDefault() { self.m_NetworkTime = StormReflTypeInfo<DDSCoordinatorNodeInitialization>::GetDefault().m_NetworkTime; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data_static<5>
{
  using member_type = std::vector<std::string>; // std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >
  static constexpr auto GetName() { return "m_SharedObjects"; }
  static constexpr auto GetType() { return "std::vector<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x431A56CC; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F698566; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 5; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorNodeInitialization::m_SharedObjects; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorNodeInitialization *>(obj); return &ptr->m_SharedObjects; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorNodeInitialization *>(obj); return &ptr->m_SharedObjects; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data<5, Self> : public StormReflTypeInfo<DDSCoordinatorNodeInitialization>::field_data_static<5>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<std::string>> & Get() { return self.m_SharedObjects; }
  std::add_const_t<std::remove_reference_t<std::vector<std::string>>> & Get() const { return self.m_SharedObjects; }
  void SetDefault() { self.m_SharedObjects = StormReflTypeInfo<DDSCoordinatorNodeInitialization>::GetDefault().m_SharedObjects; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorRoutingTableAck>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSCoordinatorRoutingTableAck"; }
  static constexpr auto GetNameHash() { return 0xCFD42D38; }
  static constexpr bool HasDefault() { return true; }
  static DDSCoordinatorRoutingTableAck & GetDefault() { static DDSCoordinatorRoutingTableAck def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorRoutingTableAck *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorRoutingTableAck *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorRoutingTableAck *>(ptr);
    if(typeid(DDSCoordinatorRoutingTableAck).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorRoutingTableAck *>(ptr);
    if(typeid(DDSCoordinatorRoutingTableAck).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSCoordinatorRoutingTableAck>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_TableGen"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4486A8A8; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorRoutingTableAck::m_TableGen; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorRoutingTableAck *>(obj); return &ptr->m_TableGen; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorRoutingTableAck *>(obj); return &ptr->m_TableGen; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorRoutingTableAck>::field_data<0, Self> : public StormReflTypeInfo<DDSCoordinatorRoutingTableAck>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_TableGen; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_TableGen; }
  void SetDefault() { self.m_TableGen = StormReflTypeInfo<DDSCoordinatorRoutingTableAck>::GetDefault().m_TableGen; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorSyncAllClear>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSCoordinatorSyncAllClear"; }
  static constexpr auto GetNameHash() { return 0x23C52751; }
  static constexpr bool HasDefault() { return true; }
  static DDSCoordinatorSyncAllClear & GetDefault() { static DDSCoordinatorSyncAllClear def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorSyncAllClear *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorSyncAllClear *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorSyncAllClear *>(ptr);
    if(typeid(DDSCoordinatorSyncAllClear).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorSyncAllClear *>(ptr);
    if(typeid(DDSCoordinatorSyncAllClear).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSCoordinatorSyncAllClear>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_TableGen"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x4486A8A8; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorSyncAllClear::m_TableGen; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorSyncAllClear *>(obj); return &ptr->m_TableGen; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorSyncAllClear *>(obj); return &ptr->m_TableGen; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorSyncAllClear>::field_data<0, Self> : public StormReflTypeInfo<DDSCoordinatorSyncAllClear>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_TableGen; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_TableGen; }
  void SetDefault() { self.m_TableGen = StormReflTypeInfo<DDSCoordinatorSyncAllClear>::GetDefault().m_TableGen; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorNodeShutdown>
{
  using MyBase = void;
  static constexpr int fields_n = 0;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSCoordinatorNodeShutdown"; }
  static constexpr auto GetNameHash() { return 0xAEBA4DA9; }
  static constexpr bool HasDefault() { return true; }
  static DDSCoordinatorNodeShutdown & GetDefault() { static DDSCoordinatorNodeShutdown def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorNodeShutdown *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorNodeShutdown *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorNodeShutdown *>(ptr);
    if(typeid(DDSCoordinatorNodeShutdown).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorNodeShutdown *>(ptr);
    if(typeid(DDSCoordinatorNodeShutdown).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSCoordinatorNodeCPUUsage>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSCoordinatorNodeCPUUsage"; }
  static constexpr auto GetNameHash() { return 0xA8C01DC0; }
  static constexpr bool HasDefault() { return true; }
  static DDSCoordinatorNodeCPUUsage & GetDefault() { static DDSCoordinatorNodeCPUUsage def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorNodeCPUUsage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorNodeCPUUsage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorNodeCPUUsage *>(ptr);
    if(typeid(DDSCoordinatorNodeCPUUsage).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorNodeCPUUsage *>(ptr);
    if(typeid(DDSCoordinatorNodeCPUUsage).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSCoordinatorNodeCPUUsage>::field_data_static<0>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Usage"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x5DDDCE10; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorNodeCPUUsage::m_Usage; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorNodeCPUUsage *>(obj); return &ptr->m_Usage; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorNodeCPUUsage *>(obj); return &ptr->m_Usage; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorNodeCPUUsage>::field_data<0, Self> : public StormReflTypeInfo<DDSCoordinatorNodeCPUUsage>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Usage; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Usage; }
  void SetDefault() { self.m_Usage = StormReflTypeInfo<DDSCoordinatorNodeCPUUsage>::GetDefault().m_Usage; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSCoordinatorSharedObjectDeltaMessage"; }
  static constexpr auto GetNameHash() { return 0x19D32AB3; }
  static constexpr bool HasDefault() { return true; }
  static DDSCoordinatorSharedObjectDeltaMessage & GetDefault() { static DDSCoordinatorSharedObjectDeltaMessage def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorSharedObjectDeltaMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorSharedObjectDeltaMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorSharedObjectDeltaMessage *>(ptr);
    if(typeid(DDSCoordinatorSharedObjectDeltaMessage).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorSharedObjectDeltaMessage *>(ptr);
    if(typeid(DDSCoordinatorSharedObjectDeltaMessage).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::field_data_static<0>
{
  using member_type = ReflectionNotifyChangeType; // ReflectionNotifyChangeType
  static constexpr auto GetName() { return "m_Type"; }
  static constexpr auto GetType() { return "ReflectionNotifyChangeType"; }
  static constexpr unsigned GetFieldNameHash() { return 0xB243C236; }
  static constexpr unsigned GetTypeNameHash() { return 0xD4869875; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorSharedObjectDeltaMessage::m_Type; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorSharedObjectDeltaMessage *>(obj); return &ptr->m_Type; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorSharedObjectDeltaMessage *>(obj); return &ptr->m_Type; }
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
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Path"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x35C91E10; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorSharedObjectDeltaMessage::m_Path; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorSharedObjectDeltaMessage *>(obj); return &ptr->m_Path; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorSharedObjectDeltaMessage *>(obj); return &ptr->m_Path; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::field_data<1, Self> : public StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Path; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Path; }
  void SetDefault() { self.m_Path = StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::GetDefault().m_Path; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::field_data_static<2>
{
  using member_type = uint64_t; // unsigned long long
  static constexpr auto GetName() { return "m_Index"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0D45F761; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorSharedObjectDeltaMessage::m_Index; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorSharedObjectDeltaMessage *>(obj); return &ptr->m_Index; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorSharedObjectDeltaMessage *>(obj); return &ptr->m_Index; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::field_data<2, Self> : public StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, uint64_t> & Get() { return self.m_Index; }
  std::add_const_t<std::remove_reference_t<uint64_t>> & Get() const { return self.m_Index; }
  void SetDefault() { self.m_Index = StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::GetDefault().m_Index; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::field_data_static<3>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_Data"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x936E667C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorSharedObjectDeltaMessage::m_Data; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorSharedObjectDeltaMessage *>(obj); return &ptr->m_Data; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorSharedObjectDeltaMessage *>(obj); return &ptr->m_Data; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::field_data<3, Self> : public StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_Data; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_Data; }
  void SetDefault() { self.m_Data = StormReflTypeInfo<DDSCoordinatorSharedObjectDeltaMessage>::GetDefault().m_Data; }
};

template <>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDelta>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSCoordinatorSharedObjectDelta"; }
  static constexpr auto GetNameHash() { return 0x59556F78; }
  static constexpr bool HasDefault() { return true; }
  static DDSCoordinatorSharedObjectDelta & GetDefault() { static DDSCoordinatorSharedObjectDelta def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorSharedObjectDelta *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorSharedObjectDelta *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorSharedObjectDelta *>(ptr);
    if(typeid(DDSCoordinatorSharedObjectDelta).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorSharedObjectDelta *>(ptr);
    if(typeid(DDSCoordinatorSharedObjectDelta).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDelta>::field_data_static<0>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_SharedObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x02559DA4; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorSharedObjectDelta::m_SharedObjectType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorSharedObjectDelta *>(obj); return &ptr->m_SharedObjectType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorSharedObjectDelta *>(obj); return &ptr->m_SharedObjectType; }
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
  using member_type = std::vector<DDSCoordinatorSharedObjectDeltaMessage>; // std::vector<DDSCoordinatorSharedObjectDeltaMessage, std::allocator<DDSCoordinatorSharedObjectDeltaMessage> >
  static constexpr auto GetName() { return "m_Deltas"; }
  static constexpr auto GetType() { return "std::vector<DDSCoordinatorSharedObjectDeltaMessage, std::allocator<DDSCoordinatorSharedObjectDeltaMessage> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xA9A8B14D; }
  static constexpr unsigned GetTypeNameHash() { return 0x56B4C346; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSCoordinatorSharedObjectDelta::m_Deltas; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSCoordinatorSharedObjectDelta *>(obj); return &ptr->m_Deltas; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSCoordinatorSharedObjectDelta *>(obj); return &ptr->m_Deltas; }
};

template <typename Self>
struct StormReflTypeInfo<DDSCoordinatorSharedObjectDelta>::field_data<1, Self> : public StormReflTypeInfo<DDSCoordinatorSharedObjectDelta>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSCoordinatorSharedObjectDeltaMessage>> & Get() { return self.m_Deltas; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSCoordinatorSharedObjectDeltaMessage>>> & Get() const { return self.m_Deltas; }
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
  static constexpr auto GetNameHash() { return 0xFCC6B416; }
  static constexpr bool HasDefault() { return true; }
  static DDSCoordinatorResponderCallData & GetDefault() { static DDSCoordinatorResponderCallData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorResponderCallData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x87E6D78C == type_name_hash) return static_cast<DDSResponderCallBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorResponderCallData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x87E6D78C == type_name_hash) return static_cast<const DDSResponderCallBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorResponderCallData *>(ptr);
    if(typeid(DDSCoordinatorResponderCallData).hash_code() == type_id_hash) return c;
    if(typeid(DDSResponderCallBase).hash_code() == type_id_hash) return static_cast<DDSResponderCallBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorResponderCallData *>(ptr);
    if(typeid(DDSCoordinatorResponderCallData).hash_code() == type_id_hash) return c;
    if(typeid(DDSResponderCallBase).hash_code() == type_id_hash) return static_cast<const DDSResponderCallBase *>(c);
    return nullptr;
  }

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
  static constexpr auto GetNameHash() { return 0x88AEA8A0; }
  static constexpr bool HasDefault() { return true; }
  static DDSCoordinatorTargetedMessage & GetDefault() { static DDSCoordinatorTargetedMessage def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorTargetedMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x3AF384DD == type_name_hash) return static_cast<DDSTargetedMessageBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorTargetedMessage *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x3AF384DD == type_name_hash) return static_cast<const DDSTargetedMessageBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorTargetedMessage *>(ptr);
    if(typeid(DDSCoordinatorTargetedMessage).hash_code() == type_id_hash) return c;
    if(typeid(DDSTargetedMessageBase).hash_code() == type_id_hash) return static_cast<DDSTargetedMessageBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorTargetedMessage *>(ptr);
    if(typeid(DDSCoordinatorTargetedMessage).hash_code() == type_id_hash) return c;
    if(typeid(DDSTargetedMessageBase).hash_code() == type_id_hash) return static_cast<const DDSTargetedMessageBase *>(c);
    return nullptr;
  }

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
  static constexpr auto GetNameHash() { return 0x4243BC82; }
  static constexpr bool HasDefault() { return true; }
  static DDSCoordinatorTargetedMessageWithResponder & GetDefault() { static DDSCoordinatorTargetedMessageWithResponder def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorTargetedMessageWithResponder *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xBA9BF921 == type_name_hash) return static_cast<DDSTargetedMessageWithResponderBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorTargetedMessageWithResponder *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xBA9BF921 == type_name_hash) return static_cast<const DDSTargetedMessageWithResponderBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorTargetedMessageWithResponder *>(ptr);
    if(typeid(DDSCoordinatorTargetedMessageWithResponder).hash_code() == type_id_hash) return c;
    if(typeid(DDSTargetedMessageWithResponderBase).hash_code() == type_id_hash) return static_cast<DDSTargetedMessageWithResponderBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorTargetedMessageWithResponder *>(ptr);
    if(typeid(DDSCoordinatorTargetedMessageWithResponder).hash_code() == type_id_hash) return c;
    if(typeid(DDSTargetedMessageWithResponderBase).hash_code() == type_id_hash) return static_cast<const DDSTargetedMessageWithResponderBase *>(c);
    return nullptr;
  }

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
  static constexpr auto GetNameHash() { return 0xA7B4FB66; }
  static constexpr bool HasDefault() { return true; }
  static DDSCoordinatorCreateSubscription & GetDefault() { static DDSCoordinatorCreateSubscription def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorCreateSubscription *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x64CEBCD5 == type_name_hash) return static_cast<DDSCreateSubscriptionBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorCreateSubscription *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x64CEBCD5 == type_name_hash) return static_cast<const DDSCreateSubscriptionBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorCreateSubscription *>(ptr);
    if(typeid(DDSCoordinatorCreateSubscription).hash_code() == type_id_hash) return c;
    if(typeid(DDSCreateSubscriptionBase).hash_code() == type_id_hash) return static_cast<DDSCreateSubscriptionBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorCreateSubscription *>(ptr);
    if(typeid(DDSCoordinatorCreateSubscription).hash_code() == type_id_hash) return c;
    if(typeid(DDSCreateSubscriptionBase).hash_code() == type_id_hash) return static_cast<const DDSCreateSubscriptionBase *>(c);
    return nullptr;
  }

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
  static constexpr auto GetNameHash() { return 0xA3232960; }
  static constexpr bool HasDefault() { return true; }
  static DDSCoordinatorDestroySubscription & GetDefault() { static DDSCoordinatorDestroySubscription def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorDestroySubscription *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xF427137A == type_name_hash) return static_cast<DDSDestroySubscriptionBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorDestroySubscription *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xF427137A == type_name_hash) return static_cast<const DDSDestroySubscriptionBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorDestroySubscription *>(ptr);
    if(typeid(DDSCoordinatorDestroySubscription).hash_code() == type_id_hash) return c;
    if(typeid(DDSDestroySubscriptionBase).hash_code() == type_id_hash) return static_cast<DDSDestroySubscriptionBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorDestroySubscription *>(ptr);
    if(typeid(DDSCoordinatorDestroySubscription).hash_code() == type_id_hash) return c;
    if(typeid(DDSDestroySubscriptionBase).hash_code() == type_id_hash) return static_cast<const DDSDestroySubscriptionBase *>(c);
    return nullptr;
  }

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
  static constexpr auto GetNameHash() { return 0x5914636E; }
  static constexpr bool HasDefault() { return true; }
  static DDSCoordinatorSubscriptionDeleted & GetDefault() { static DDSCoordinatorSubscriptionDeleted def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorSubscriptionDeleted *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xA49AD769 == type_name_hash) return static_cast<DDSSubscriptionDeletedBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorSubscriptionDeleted *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0xA49AD769 == type_name_hash) return static_cast<const DDSSubscriptionDeletedBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSCoordinatorSubscriptionDeleted *>(ptr);
    if(typeid(DDSCoordinatorSubscriptionDeleted).hash_code() == type_id_hash) return c;
    if(typeid(DDSSubscriptionDeletedBase).hash_code() == type_id_hash) return static_cast<DDSSubscriptionDeletedBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSCoordinatorSubscriptionDeleted *>(ptr);
    if(typeid(DDSCoordinatorSubscriptionDeleted).hash_code() == type_id_hash) return c;
    if(typeid(DDSSubscriptionDeletedBase).hash_code() == type_id_hash) return static_cast<const DDSSubscriptionDeletedBase *>(c);
    return nullptr;
  }

};

namespace StormReflFileInfo
{
  struct DDSCoordinatorProtocolMessages
  {
    static const int types_n = 16;
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
    using type = ::DDSCoordinatorRoutingTableAck;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<5>
  {
    using type = ::DDSCoordinatorSyncAllClear;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<6>
  {
    using type = ::DDSCoordinatorNodeShutdown;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<7>
  {
    using type = ::DDSCoordinatorNodeCPUUsage;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<8>
  {
    using type = ::DDSCoordinatorSharedObjectDeltaMessage;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<9>
  {
    using type = ::DDSCoordinatorSharedObjectDelta;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<10>
  {
    using type = ::DDSCoordinatorResponderCallData;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<11>
  {
    using type = ::DDSCoordinatorTargetedMessage;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<12>
  {
    using type = ::DDSCoordinatorTargetedMessageWithResponder;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<13>
  {
    using type = ::DDSCoordinatorCreateSubscription;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<14>
  {
    using type = ::DDSCoordinatorDestroySubscription;
  };

  template <>
  struct DDSCoordinatorProtocolMessages::type_info<15>
  {
    using type = ::DDSCoordinatorSubscriptionDeleted;
  };

}

