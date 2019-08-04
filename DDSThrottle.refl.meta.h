#pragma once

#include <StormRefl/StormReflMetaInfoBase.h>

#include "DDSThrottle.refl.h"


template <>
struct StormReflTypeInfo<DDSThrottle>
{
  using MyBase = void;
  static constexpr int fields_n = 4;
  template <int N> struct field_data_static {};
  template <int N, typename Self> struct field_data {};
  template <int N> struct annotations { static constexpr int annotations_n = 0; template <int A> struct annoation { }; };
  static constexpr auto GetName() { return "DDSThrottle"; }
  static constexpr auto GetNameHash() { return 0xA610F43B; }
  static constexpr bool HasDefault() { return true; }
  static DDSThrottle & GetDefault() { static DDSThrottle def; return def; }

  static void * CastFromTypeNameHash(uint32_t type_name_hash, void * ptr)
  {
    auto c = static_cast<DDSThrottle *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeNameHash(uint32_t type_name_hash, const void * ptr)
  {
    auto c = static_cast<const DDSThrottle *>(ptr);
    if(GetNameHash() == type_name_hash) return c;
    return nullptr;
  }

  static void * CastFromTypeIdHash(std::size_t type_id_hash, void * ptr)
  {
    auto c = static_cast<DDSThrottle *>(ptr);
    if(typeid(DDSThrottle).hash_code() == type_id_hash) return c;
    return nullptr;
  }

  static const void * CastFromTypeIdHash(std::size_t type_id_hash, const void * ptr)
  {
    auto c = static_cast<const DDSThrottle *>(ptr);
    if(typeid(DDSThrottle).hash_code() == type_id_hash) return c;
    return nullptr;
  }

};

template <>
struct StormReflTypeInfo<DDSThrottle>::field_data_static<0>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Credits"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xD4E5A4AB; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 0; }
  static constexpr auto GetMemberPtr() { return &DDSThrottle::m_Credits; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSThrottle *>(obj); return &ptr->m_Credits; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSThrottle *>(obj); return &ptr->m_Credits; }
};

template <typename Self>
struct StormReflTypeInfo<DDSThrottle>::field_data<0, Self> : public StormReflTypeInfo<DDSThrottle>::field_data_static<0>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Credits; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Credits; }
  void SetDefault() { self.m_Credits = StormReflTypeInfo<DDSThrottle>::GetDefault().m_Credits; }
};

template <>
struct StormReflTypeInfo<DDSThrottle>::field_data_static<1>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Rate"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE171AA26; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 1; }
  static constexpr auto GetMemberPtr() { return &DDSThrottle::m_Rate; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSThrottle *>(obj); return &ptr->m_Rate; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSThrottle *>(obj); return &ptr->m_Rate; }
};

template <typename Self>
struct StormReflTypeInfo<DDSThrottle>::field_data<1, Self> : public StormReflTypeInfo<DDSThrottle>::field_data_static<1>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Rate; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Rate; }
  void SetDefault() { self.m_Rate = StormReflTypeInfo<DDSThrottle>::GetDefault().m_Rate; }
};

template <>
struct StormReflTypeInfo<DDSThrottle>::field_data_static<2>
{
  using member_type = float; // float
  static constexpr auto GetName() { return "m_Max"; }
  static constexpr auto GetType() { return "float"; }
  static constexpr unsigned GetFieldNameHash() { return 0x6E94E66E; }
  static constexpr unsigned GetTypeNameHash() { return 0xC9A55E95; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 2; }
  static constexpr auto GetMemberPtr() { return &DDSThrottle::m_Max; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSThrottle *>(obj); return &ptr->m_Max; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSThrottle *>(obj); return &ptr->m_Max; }
};

template <typename Self>
struct StormReflTypeInfo<DDSThrottle>::field_data<2, Self> : public StormReflTypeInfo<DDSThrottle>::field_data_static<2>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, float> & Get() { return self.m_Max; }
  std::add_const_t<std::remove_reference_t<float>> & Get() const { return self.m_Max; }
  void SetDefault() { self.m_Max = StormReflTypeInfo<DDSThrottle>::GetDefault().m_Max; }
};

template <>
struct StormReflTypeInfo<DDSThrottle>::field_data_static<3>
{
  using member_type = time_t; // long long
  static constexpr auto GetName() { return "m_CreditStart"; }
  static constexpr auto GetType() { return "long long"; }
  static constexpr unsigned GetFieldNameHash() { return 0xE100B249; }
  static constexpr unsigned GetTypeNameHash() { return 0x40FF8523; }
  static constexpr bool HasDefault() { return true; }
  static constexpr auto GetFieldIndex() { return 3; }
  static constexpr auto GetMemberPtr() { return &DDSThrottle::m_CreditStart; }
  static void * GetFromParent(void * obj) { auto ptr = static_cast<DDSThrottle *>(obj); return &ptr->m_CreditStart; }
  static const void * GetFromParentConst(const void * obj) { auto ptr = static_cast<const DDSThrottle *>(obj); return &ptr->m_CreditStart; }
};

template <typename Self>
struct StormReflTypeInfo<DDSThrottle>::field_data<3, Self> : public StormReflTypeInfo<DDSThrottle>::field_data_static<3>
{
  Self & self;
  field_data(Self & self) : self(self) {}
  match_const_t<Self, time_t> & Get() { return self.m_CreditStart; }
  std::add_const_t<std::remove_reference_t<time_t>> & Get() const { return self.m_CreditStart; }
  void SetDefault() { self.m_CreditStart = StormReflTypeInfo<DDSThrottle>::GetDefault().m_CreditStart; }
};

namespace StormReflFileInfo
{
  struct DDSThrottle
  {
    static const int types_n = 1;
    template <int i> struct type_info { using type = void; };
  };

  template <>
  struct DDSThrottle::type_info<0>
  {
    using type = ::DDSThrottle;
  };

}

