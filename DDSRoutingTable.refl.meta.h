#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "DDSRoutingTable.refl.h"


template <>
struct StormReflTypeInfo<DDSNodeElementBase>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSNodeElementBase"; }
  static constexpr auto GetNameHash() { return 0xF0F1CCE7; }
  static DDSNodeElementBase & GetDefault() { static DDSNodeElementBase def; return def; }
};

template <>
struct StormReflTypeInfo<DDSNodeElementBase>::field_data_static<0>
{
  using member_type = DDSNodeId; // unsigned int
  static constexpr auto GetName() { return "m_Id"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x86501E36; }
  static constexpr unsigned GetTypeNameHash() { return 0xB306EEF4; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSNodeElementBase::m_Id; }
};

template <typename Self>
struct StormReflTypeInfo<DDSNodeElementBase>::field_data<0, Self> : public StormReflTypeInfo<DDSNodeElementBase>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSNodeId> & Get() { return self.m_Id; }
  std::add_const_t<std::remove_reference_t<DDSNodeId>> & Get() const { return self.m_Id; }
  void SetDefault() { self.m_Id = StormReflTypeInfo<DDSNodeElementBase>::GetDefault().m_Id; }
};

template <>
struct StormReflTypeInfo<DDSNodeElementBase>::field_data_static<1>
{
  using member_type = DDSNodeAddr; // unsigned int
  static constexpr auto GetName() { return "m_Addr"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x92398073; }
  static constexpr unsigned GetTypeNameHash() { return 0xB306EEF4; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSNodeElementBase::m_Addr; }
};

template <typename Self>
struct StormReflTypeInfo<DDSNodeElementBase>::field_data<1, Self> : public StormReflTypeInfo<DDSNodeElementBase>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSNodeAddr> & Get() { return self.m_Addr; }
  std::add_const_t<std::remove_reference_t<DDSNodeAddr>> & Get() const { return self.m_Addr; }
  void SetDefault() { self.m_Addr = StormReflTypeInfo<DDSNodeElementBase>::GetDefault().m_Addr; }
};

template <>
struct StormReflTypeInfo<DDSNodeElementBase>::field_data_static<2>
{
  using member_type = DDSNodePort; // unsigned short
  static constexpr auto GetName() { return "m_Port"; }
  static constexpr auto GetType() { return "unsigned short"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6B7B2786; }
  static constexpr unsigned GetTypeNameHash() { return 0xFB128F18; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSNodeElementBase::m_Port; }
};

template <typename Self>
struct StormReflTypeInfo<DDSNodeElementBase>::field_data<2, Self> : public StormReflTypeInfo<DDSNodeElementBase>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSNodePort> & Get() { return self.m_Port; }
  std::add_const_t<std::remove_reference_t<DDSNodePort>> & Get() const { return self.m_Port; }
  void SetDefault() { self.m_Port = StormReflTypeInfo<DDSNodeElementBase>::GetDefault().m_Port; }
};

template <>
struct StormReflTypeInfo<DDSNodeElementBase>::field_data_static<3>
{
  using member_type = std::vector<DDSNodePort>; // std::vector<unsigned short, std::allocator<unsigned short> >
  static constexpr auto GetName() { return "m_EndpointPorts"; }
  static constexpr auto GetType() { return "std::vector<unsigned short, std::allocator<unsigned short> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x86843321; }
  static constexpr unsigned GetTypeNameHash() { return 0xD4C715E9; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSNodeElementBase::m_EndpointPorts; }
};

template <typename Self>
struct StormReflTypeInfo<DDSNodeElementBase>::field_data<3, Self> : public StormReflTypeInfo<DDSNodeElementBase>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSNodePort>> & Get() { return self.m_EndpointPorts; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSNodePort>>> & Get() const { return self.m_EndpointPorts; }
  void SetDefault() { self.m_EndpointPorts = StormReflTypeInfo<DDSNodeElementBase>::GetDefault().m_EndpointPorts; }
};

template <>
struct StormReflTypeInfo<DDSNodeElementBase>::field_data_static<4>
{
  using member_type = std::vector<DDSNodePort>; // std::vector<unsigned short, std::allocator<unsigned short> >
  static constexpr auto GetName() { return "m_WebsitePorts"; }
  static constexpr auto GetType() { return "std::vector<unsigned short, std::allocator<unsigned short> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE1DA4E76; }
  static constexpr unsigned GetTypeNameHash() { return 0xD4C715E9; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSNodeElementBase::m_WebsitePorts; }
};

template <typename Self>
struct StormReflTypeInfo<DDSNodeElementBase>::field_data<4, Self> : public StormReflTypeInfo<DDSNodeElementBase>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSNodePort>> & Get() { return self.m_WebsitePorts; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSNodePort>>> & Get() const { return self.m_WebsitePorts; }
  void SetDefault() { self.m_WebsitePorts = StormReflTypeInfo<DDSNodeElementBase>::GetDefault().m_WebsitePorts; }
};

template <>
struct StormReflTypeInfo<DDSNodeElement>
{
  using MyBase = DDSNodeElementBase;
  static constexpr int fields_n = 1 + StormReflTypeInfo<MyBase>::fields_n;
  template <int N> struct field_data_static : public StormReflTypeInfo<MyBase>::field_data_static<N> {};
  template <int N, typename Self> struct field_data : public StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>
  {
    field_data(Self & self) : StormReflTypeInfo<MyBase>::field_data<N, match_const_t<Self, MyBase>>(self) {}
  };
  template <int N> struct annotations : public StormReflTypeInfo<MyBase>::annotations<N> {};
  static constexpr auto GetName() { return "DDSNodeElement"; }
  static constexpr auto GetNameHash() { return 0x85F09AA8; }
  static DDSNodeElement & GetDefault() { static DDSNodeElement def; return def; }
};

template <>
struct StormReflTypeInfo<DDSNodeElement>::field_data_static<0 + StormReflTypeInfo<DDSNodeElementBase>::fields_n>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_CentralKey"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x75B64F71; }
  static constexpr unsigned GetTypeNameHash() { return 0x639DDCF5; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<DDSNodeElementBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &DDSNodeElement::m_CentralKey; }
};

template <typename Self>
struct StormReflTypeInfo<DDSNodeElement>::field_data<0 + StormReflTypeInfo<DDSNodeElementBase>::fields_n, Self> : public StormReflTypeInfo<DDSNodeElement>::field_data_static<0 + StormReflTypeInfo<DDSNodeElementBase>::fields_n>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_CentralKey; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_CentralKey; }
  void SetDefault() { self.m_CentralKey = StormReflTypeInfo<DDSNodeElement>::GetDefault().m_CentralKey; }
};

template <>
struct StormReflTypeInfo<DDSRoutingTable>
{
  using MyBase = void;
  static constexpr int fields_n = 3;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSRoutingTable"; }
  static constexpr auto GetNameHash() { return 0x2D7E3D41; }
  static DDSRoutingTable & GetDefault() { static DDSRoutingTable def; return def; }
};

template <>
struct StormReflTypeInfo<DDSRoutingTable>::field_data_static<0>
{
  using member_type = std::vector<DDSNodeElement>; // std::vector<DDSNodeElement, std::allocator<DDSNodeElement> >
  static constexpr auto GetName() { return "m_Table"; }
  static constexpr auto GetType() { return "std::vector<DDSNodeElement, std::allocator<DDSNodeElement> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x468693E5; }
  static constexpr unsigned GetTypeNameHash() { return 0xDEF40640; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSRoutingTable::m_Table; }
};

template <typename Self>
struct StormReflTypeInfo<DDSRoutingTable>::field_data<0, Self> : public StormReflTypeInfo<DDSRoutingTable>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSNodeElement>> & Get() { return self.m_Table; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSNodeElement>>> & Get() const { return self.m_Table; }
  void SetDefault() { self.m_Table = StormReflTypeInfo<DDSRoutingTable>::GetDefault().m_Table; }
};

template <>
struct StormReflTypeInfo<DDSRoutingTable>::field_data_static<1>
{
  using member_type = std::vector<DDSNodeElementBase>; // std::vector<DDSNodeElementBase, std::allocator<DDSNodeElementBase> >
  static constexpr auto GetName() { return "m_Defunct"; }
  static constexpr auto GetType() { return "std::vector<DDSNodeElementBase, std::allocator<DDSNodeElementBase> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x8D6ECFC8; }
  static constexpr unsigned GetTypeNameHash() { return 0x351EFABA; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSRoutingTable::m_Defunct; }
};

template <typename Self>
struct StormReflTypeInfo<DDSRoutingTable>::field_data<1, Self> : public StormReflTypeInfo<DDSRoutingTable>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::vector<DDSNodeElementBase>> & Get() { return self.m_Defunct; }
  std::add_const_t<std::remove_reference_t<std::vector<DDSNodeElementBase>>> & Get() const { return self.m_Defunct; }
  void SetDefault() { self.m_Defunct = StormReflTypeInfo<DDSRoutingTable>::GetDefault().m_Defunct; }
};

template <>
struct StormReflTypeInfo<DDSRoutingTable>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_TableGeneration"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x0B85D3D6; }
  static constexpr unsigned GetTypeNameHash() { return 0x0E63B618; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSRoutingTable::m_TableGeneration; }
};

template <typename Self>
struct StormReflTypeInfo<DDSRoutingTable>::field_data<2, Self> : public StormReflTypeInfo<DDSRoutingTable>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_TableGeneration; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_TableGeneration; }
  void SetDefault() { self.m_TableGeneration = StormReflTypeInfo<DDSRoutingTable>::GetDefault().m_TableGeneration; }
};

namespace StormReflFileInfo
{
  struct DDSRoutingTable
  {
    static const int types_n = 3;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct DDSRoutingTable::type_info<0>
  {
    using type = ::DDSNodeElementBase;
  };

  template <>
  struct DDSRoutingTable::type_info<1>
  {
    using type = ::DDSNodeElement;
  };

  template <>
  struct DDSRoutingTable::type_info<2>
  {
    using type = ::DDSRoutingTable;
  };

}

