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
  static constexpr auto GetNameHash() { return 0x0DA54077; }
  static constexpr bool HasDefault() { return true; }
  static DDSNodeElementBase & GetDefault() { static DDSNodeElementBase def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSNodeElementBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSNodeElementBase *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSNodeElementBase *>(ptr);
    if(typeid(DDSNodeElementBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSNodeElementBase *>(ptr);
    if(typeid(DDSNodeElementBase).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSNodeElementBase>::field_data_static<0>
{
  using member_type = DDSNodeId; // unsigned int
  static constexpr auto GetName() { return "m_Id"; }
  static constexpr auto GetType() { return "unsigned int"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE48CC842; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSNodeElementBase::m_Id; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSNodeElementBase *>(obj); return &ptr->m_Id; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSNodeElementBase *>(obj); return &ptr->m_Id; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x6C07072A; }
  static constexpr unsigned GetTypeNameHash() { return 0x562EF932; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSNodeElementBase::m_Addr; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSNodeElementBase *>(obj); return &ptr->m_Addr; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSNodeElementBase *>(obj); return &ptr->m_Addr; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x7D0CC8D3; }
  static constexpr unsigned GetTypeNameHash() { return 0x3DE16827; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSNodeElementBase::m_Port; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSNodeElementBase *>(obj); return &ptr->m_Port; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSNodeElementBase *>(obj); return &ptr->m_Port; }
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
  static constexpr unsigned GetFieldNameHash() { return 0xE6C133B1; }
  static constexpr unsigned GetTypeNameHash() { return 0x072FC70B; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSNodeElementBase::m_EndpointPorts; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSNodeElementBase *>(obj); return &ptr->m_EndpointPorts; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSNodeElementBase *>(obj); return &ptr->m_EndpointPorts; }
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
  static constexpr unsigned GetFieldNameHash() { return 0xB0FC1FC0; }
  static constexpr unsigned GetTypeNameHash() { return 0x072FC70B; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSNodeElementBase::m_WebsitePorts; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSNodeElementBase *>(obj); return &ptr->m_WebsitePorts; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSNodeElementBase *>(obj); return &ptr->m_WebsitePorts; }
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
  static constexpr auto GetNameHash() { return 0x91B8D954; }
  static constexpr bool HasDefault() { return true; }
  static DDSNodeElement & GetDefault() { static DDSNodeElement def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSNodeElement *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x0DA54077 == type_name_hash) return static_cast<DDSNodeElementBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSNodeElement *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    if(0x0DA54077 == type_name_hash) return static_cast<const DDSNodeElementBase *>(c);
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSNodeElement *>(ptr);
    if(typeid(DDSNodeElement).hash_code() == type_id_hash) return c;
    if(typeid(DDSNodeElementBase).hash_code() == type_id_hash) return static_cast<DDSNodeElementBase *>(c);
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSNodeElement *>(ptr);
    if(typeid(DDSNodeElement).hash_code() == type_id_hash) return c;
    if(typeid(DDSNodeElementBase).hash_code() == type_id_hash) return static_cast<const DDSNodeElementBase *>(c);
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSNodeElement>::field_data_static<0 + StormReflTypeInfo<DDSNodeElementBase>::fields_n>
{
  using member_type = DDSKey; // unsigned long long
  static constexpr auto GetName() { return "m_CentralKey"; }
  static constexpr auto GetType() { return "unsigned long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x46853245; }
  static constexpr unsigned GetTypeNameHash() { return 0x1EF85FE5; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0 + StormReflTypeInfo<DDSNodeElementBase>::fields_n; }
  static constexpr auto GetMemberPtr() { return &DDSNodeElement::m_CentralKey; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSNodeElement *>(obj); return &ptr->m_CentralKey; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSNodeElement *>(obj); return &ptr->m_CentralKey; }
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
  static constexpr auto GetNameHash() { return 0x2554A051; }
  static constexpr bool HasDefault() { return true; }
  static DDSRoutingTable & GetDefault() { static DDSRoutingTable def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSRoutingTable *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSRoutingTable *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSRoutingTable *>(ptr);
    if(typeid(DDSRoutingTable).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSRoutingTable *>(ptr);
    if(typeid(DDSRoutingTable).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSRoutingTable>::field_data_static<0>
{
  using member_type = std::vector<DDSNodeElement>; // std::vector<DDSNodeElement, std::allocator<DDSNodeElement> >
  static constexpr auto GetName() { return "m_Table"; }
  static constexpr auto GetType() { return "std::vector<DDSNodeElement, std::allocator<DDSNodeElement> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0x7B1F1F26; }
  static constexpr unsigned GetTypeNameHash() { return 0xFBA8241F; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSRoutingTable::m_Table; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSRoutingTable *>(obj); return &ptr->m_Table; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSRoutingTable *>(obj); return &ptr->m_Table; }
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
  static constexpr unsigned GetFieldNameHash() { return 0x3E3CE59C; }
  static constexpr unsigned GetTypeNameHash() { return 0x4BB2C546; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSRoutingTable::m_Defunct; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSRoutingTable *>(obj); return &ptr->m_Defunct; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSRoutingTable *>(obj); return &ptr->m_Defunct; }
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
  static constexpr unsigned GetFieldNameHash() { return 0xE6B5368A; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSRoutingTable::m_TableGeneration; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSRoutingTable *>(obj); return &ptr->m_TableGeneration; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSRoutingTable *>(obj); return &ptr->m_TableGeneration; }
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

