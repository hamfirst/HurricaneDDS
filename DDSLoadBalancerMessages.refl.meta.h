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
  static DDSLoadBalancerNode & GetDefault() { static DDSLoadBalancerNode def; return def; }
};

template <>
struct StormReflTypeInfo<DDSLoadBalancerNode>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_IpAddr"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xF938AA21; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSLoadBalancerNode::m_IpAddr; }
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
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSLoadBalancerNode::m_Port; }
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
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSLoadBalancerNode::m_Cpu; }
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
  static DDSLoadBalancerInfo & GetDefault() { static DDSLoadBalancerInfo def; return def; }
};

template <>
struct StormReflTypeInfo<DDSLoadBalancerInfo>::field_data_static<0>
{
  using member_type = std::vector<DDSLoadBalancerNode>; // std::vector<DDSLoadBalancerNode, std::allocator<DDSLoadBalancerNode> >
  static constexpr auto GetName() { return "m_Nodes"; }
  static constexpr auto GetType() { return "std::vector<DDSLoadBalancerNode, std::allocator<DDSLoadBalancerNode> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x900B959C; }
  static constexpr unsigned GetTypeNameHash() { return 0xF19BA7B2; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSLoadBalancerInfo::m_Nodes; }
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
  static DDSLoadBalancerResponse & GetDefault() { static DDSLoadBalancerResponse def; return def; }
};

template <>
struct StormReflTypeInfo<DDSLoadBalancerResponse>::field_data_static<0>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "host"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xCF2713FD; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSLoadBalancerResponse::host; }
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
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSLoadBalancerResponse::port; }
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

