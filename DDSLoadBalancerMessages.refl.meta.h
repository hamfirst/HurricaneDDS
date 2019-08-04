#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "DDSLoadBalancerMessages.refl.h"


template <>
struct StormReflTypeInfo<DDSLoadBalancerNode>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSLoadBalancerNode"; }
  static constexpr auto GetNameHash() { return 0xFB6E154B; }
  static constexpr bool HasDefault() { return true; }
  static DDSLoadBalancerNode & GetDefault() { static DDSLoadBalancerNode def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSLoadBalancerNode *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSLoadBalancerNode *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSLoadBalancerNode *>(ptr);
    if(typeid(DDSLoadBalancerNode).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSLoadBalancerNode *>(ptr);
    if(typeid(DDSLoadBalancerNode).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSLoadBalancerNode>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_IpAddr"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF938AA21; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSLoadBalancerNode::m_IpAddr; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSLoadBalancerNode *>(obj); return &ptr->m_IpAddr; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSLoadBalancerNode *>(obj); return &ptr->m_IpAddr; }
};

template <typename Self>
struct StormReflTypeInfo<DDSLoadBalancerNode>::field_data<0, Self> : public StormReflTypeInfo<DDSLoadBalancerNode>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_IpAddr; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_IpAddr; }
  void SetDefault() { self.m_IpAddr = StormReflTypeInfo<DDSLoadBalancerNode>::GetDefault().m_IpAddr; }
};

template <>
struct StormReflTypeInfo<DDSLoadBalancerNode>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Port"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7D0CC8D3; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSLoadBalancerNode::m_Port; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSLoadBalancerNode *>(obj); return &ptr->m_Port; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSLoadBalancerNode *>(obj); return &ptr->m_Port; }
};

template <typename Self>
struct StormReflTypeInfo<DDSLoadBalancerNode>::field_data<1, Self> : public StormReflTypeInfo<DDSLoadBalancerNode>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Port; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Port; }
  void SetDefault() { self.m_Port = StormReflTypeInfo<DDSLoadBalancerNode>::GetDefault().m_Port; }
};

template <>
struct StormReflTypeInfo<DDSLoadBalancerNode>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_Cpu"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x496294C9; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSLoadBalancerNode::m_Cpu; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSLoadBalancerNode *>(obj); return &ptr->m_Cpu; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSLoadBalancerNode *>(obj); return &ptr->m_Cpu; }
};

template <typename Self>
struct StormReflTypeInfo<DDSLoadBalancerNode>::field_data<2, Self> : public StormReflTypeInfo<DDSLoadBalancerNode>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_Cpu; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_Cpu; }
  void SetDefault() { self.m_Cpu = StormReflTypeInfo<DDSLoadBalancerNode>::GetDefault().m_Cpu; }
};

template <>
struct StormReflTypeInfo<DDSLoadBalancerInfo>
{
  using MyBase = void;
  static constexpr int fields_n = 1;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSLoadBalancerInfo"; }
  static constexpr auto GetNameHash() { return 0xB598CC59; }
  static constexpr bool HasDefault() { return true; }
  static DDSLoadBalancerInfo & GetDefault() { static DDSLoadBalancerInfo def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSLoadBalancerInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSLoadBalancerInfo *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSLoadBalancerInfo *>(ptr);
    if(typeid(DDSLoadBalancerInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSLoadBalancerInfo *>(ptr);
    if(typeid(DDSLoadBalancerInfo).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSLoadBalancerInfo>::field_data_static<0>
{
  using member_type = std::vector<DDSLoadBalancerNode>; // std::vector<DDSLoadBalancerNode, std::allocator<DDSLoadBalancerNode> >
  static constexpr auto GetName() { return "m_Nodes"; }
  static constexpr auto GetType() { return "std::vector<DDSLoadBalancerNode, std::allocator<DDSLoadBalancerNode> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x900B959C; }
  static constexpr unsigned GetTypeNameHash() { return 0xF19BA7B2; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSLoadBalancerInfo::m_Nodes; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSLoadBalancerInfo *>(obj); return &ptr->m_Nodes; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSLoadBalancerInfo *>(obj); return &ptr->m_Nodes; }
};

template <typename Self>
struct StormReflTypeInfo<DDSLoadBalancerInfo>::field_data<0, Self> : public StormReflTypeInfo<DDSLoadBalancerInfo>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSLoadBalancerNode>> & Get() { return self.m_Nodes; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSLoadBalancerNode>>> & Get() const { return self.m_Nodes; }
  void SetDefault() { self.m_Nodes = StormReflTypeInfo<DDSLoadBalancerInfo>::GetDefault().m_Nodes; }
};

template <>
struct StormReflTypeInfo<DDSLoadBalancerResponse>
{
  using MyBase = void;
  static constexpr int fields_n = 2;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSLoadBalancerResponse"; }
  static constexpr auto GetNameHash() { return 0x87DCE360; }
  static constexpr bool HasDefault() { return true; }
  static DDSLoadBalancerResponse & GetDefault() { static DDSLoadBalancerResponse def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSLoadBalancerResponse *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSLoadBalancerResponse *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSLoadBalancerResponse *>(ptr);
    if(typeid(DDSLoadBalancerResponse).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSLoadBalancerResponse *>(ptr);
    if(typeid(DDSLoadBalancerResponse).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSLoadBalancerResponse>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "host"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCF2713FD; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSLoadBalancerResponse::host; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSLoadBalancerResponse *>(obj); return &ptr->host; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSLoadBalancerResponse *>(obj); return &ptr->host; }
};

template <typename Self>
struct StormReflTypeInfo<DDSLoadBalancerResponse>::field_data<0, Self> : public StormReflTypeInfo<DDSLoadBalancerResponse>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.host; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.host; }
  void SetDefault() { self.host = StormReflTypeInfo<DDSLoadBalancerResponse>::GetDefault().host; }
};

template <>
struct StormReflTypeInfo<DDSLoadBalancerResponse>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "port"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x43915DCC; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSLoadBalancerResponse::port; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSLoadBalancerResponse *>(obj); return &ptr->port; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSLoadBalancerResponse *>(obj); return &ptr->port; }
};

template <typename Self>
struct StormReflTypeInfo<DDSLoadBalancerResponse>::field_data<1, Self> : public StormReflTypeInfo<DDSLoadBalancerResponse>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.port; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.port; }
  void SetDefault() { self.port = StormReflTypeInfo<DDSLoadBalancerResponse>::GetDefault().port; }
};

namespace StormReflFileInfo
{
  struct DDSLoadBalancerMessages
  {
    static const int types_n = 3;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct DDSLoadBalancerMessages::type_info<0>
  {
    using type = ::DDSLoadBalancerNode;
  };

  template <>
  struct DDSLoadBalancerMessages::type_info<1>
  {
    using type = ::DDSLoadBalancerInfo;
  };

  template <>
  struct DDSLoadBalancerMessages::type_info<2>
  {
    using type = ::DDSLoadBalancerResponse;
  };

}

