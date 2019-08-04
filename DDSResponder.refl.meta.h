#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "DDSResponder.refl.h"


template <>
struct StormReflTypeInfo<DDSResponderData>
{
  using MyBase = void;
  static constexpr int fields_n = 5;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSResponderData"; }
  static constexpr auto GetNameHash() { return 0x8B5B1335; }
  static constexpr bool HasDefault() { return true; }
  static DDSResponderData & GetDefault() { static DDSResponderData def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSResponderData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSResponderData *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSResponderData *>(ptr);
    if(typeid(DDSResponderData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSResponderData *>(ptr);
    if(typeid(DDSResponderData).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSResponderData>::field_data_static<0>
{
  using member_type = DDSKey; // unsigned long
  static constexpr auto GetName() { return "m_Key"; }
  static constexpr auto GetType() { return "unsigned long"; }
  static constexpr unsigned GetFieldNameHash() { return 0x79726F4E; }
  static constexpr unsigned GetTypeNameHash() { return 0x4F6404D1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSResponderData::m_Key; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSResponderData *>(obj); return &ptr->m_Key; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSResponderData *>(obj); return &ptr->m_Key; }
};

template <typename Self>
struct StormReflTypeInfo<DDSResponderData>::field_data<0, Self> : public StormReflTypeInfo<DDSResponderData>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, DDSKey> & Get() { return self.m_Key; }
  std::add_const_t<std::remove_reference_t<DDSKey>> & Get() const { return self.m_Key; }
  void SetDefault() { self.m_Key = StormReflTypeInfo<DDSResponderData>::GetDefault().m_Key; }
};

template <>
struct StormReflTypeInfo<DDSResponderData>::field_data_static<1>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ObjectType"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x2C75B4A5; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSResponderData::m_ObjectType; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSResponderData *>(obj); return &ptr->m_ObjectType; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSResponderData *>(obj); return &ptr->m_ObjectType; }
};

template <typename Self>
struct StormReflTypeInfo<DDSResponderData>::field_data<1, Self> : public StormReflTypeInfo<DDSResponderData>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ObjectType; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ObjectType; }
  void SetDefault() { self.m_ObjectType = StormReflTypeInfo<DDSResponderData>::GetDefault().m_ObjectType; }
};

template <>
struct StormReflTypeInfo<DDSResponderData>::field_data_static<2>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ReturnMethodId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x08249C71; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSResponderData::m_ReturnMethodId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSResponderData *>(obj); return &ptr->m_ReturnMethodId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSResponderData *>(obj); return &ptr->m_ReturnMethodId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSResponderData>::field_data<2, Self> : public StormReflTypeInfo<DDSResponderData>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ReturnMethodId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ReturnMethodId; }
  void SetDefault() { self.m_ReturnMethodId = StormReflTypeInfo<DDSResponderData>::GetDefault().m_ReturnMethodId; }
};

template <>
struct StormReflTypeInfo<DDSResponderData>::field_data_static<3>
{
  using member_type = int; // int
  static constexpr auto GetName() { return "m_ErrorMethodId"; }
  static constexpr auto GetType() { return "int"; }
  static constexpr unsigned GetFieldNameHash() { return 0x3D403BAD; }
  static constexpr unsigned GetTypeNameHash() { return 0x1451DAB1; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSResponderData::m_ErrorMethodId; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSResponderData *>(obj); return &ptr->m_ErrorMethodId; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSResponderData *>(obj); return &ptr->m_ErrorMethodId; }
};

template <typename Self>
struct StormReflTypeInfo<DDSResponderData>::field_data<3, Self> : public StormReflTypeInfo<DDSResponderData>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, int> & Get() { return self.m_ErrorMethodId; }
  std::add_const_t<std::remove_reference_t<int>> & Get() const { return self.m_ErrorMethodId; }
  void SetDefault() { self.m_ErrorMethodId = StormReflTypeInfo<DDSResponderData>::GetDefault().m_ErrorMethodId; }
};

template <>
struct StormReflTypeInfo<DDSResponderData>::field_data_static<4>
{
  using member_type = std::string; // std::basic_string<char, std::char_traits<char>, std::allocator<char> >
  static constexpr auto GetName() { return "m_ReturnArg"; }
  static constexpr auto GetType() { return "std::basic_string<char, std::char_traits<char>, std::allocator<char> >"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD8D32394; }
  static constexpr unsigned GetTypeNameHash() { return 0x4E9D252D; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 4; }
  static constexpr auto GetMemberPtr() { return &DDSResponderData::m_ReturnArg; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSResponderData *>(obj); return &ptr->m_ReturnArg; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSResponderData *>(obj); return &ptr->m_ReturnArg; }
};

template <typename Self>
struct StormReflTypeInfo<DDSResponderData>::field_data<4, Self> : public StormReflTypeInfo<DDSResponderData>::field_data_static<4>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, std::string> & Get() { return self.m_ReturnArg; }
  std::add_const_t<std::remove_reference_t<std::string>> & Get() const { return self.m_ReturnArg; }
  void SetDefault() { self.m_ReturnArg = StormReflTypeInfo<DDSResponderData>::GetDefault().m_ReturnArg; }
};

namespace StormReflFileInfo
{
  struct DDSResponder
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct DDSResponder::type_info<0>
  {
    using type = ::DDSResponderData;
  };

}

