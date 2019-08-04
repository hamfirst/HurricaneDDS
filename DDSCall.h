#pragma once

#define DDS_DECLARE_HAS_FUNC(FuncName) \
template <typename T> class DDSHasFunc##FuncName \
{  \
  public :template <typename C> static char test(decltype(&C::FuncName)); template <typename C> static long test(...);  static const bool value = sizeof(test<T>(0)) == sizeof(char); \
}; \

#define DDS_DECLARE_CALL_FUNC(FuncName) \
template <bool Enable> struct DDSCallFunc##FuncName \
{ \
  template <typename T, typename ... Args> static bool Call(T & t, Args && ... args) { t.FuncName(std::forward<Args>(args)...); return true; } \
}; \
template <> struct DDSCallFunc##FuncName<false> \
{ \
  template <typename T, typename ... Args> static bool Call(T & t, Args && ... args) { return false; } \
}; \

#define DDS_DECLARE_CALL(FuncName) \
  DDS_DECLARE_HAS_FUNC(FuncName) \
  DDS_DECLARE_CALL_FUNC(FuncName) \

#define DDS_HAS_FUNC(ClassName, FuncName)  DDSHasFunc ## FuncName<ClassName>::value
#define DDS_CALL_FUNC(FuncName, Inst, ...) DDSCallFunc ## FuncName<DDSHasFunc ## FuncName<std::decay_t<decltype(Inst)>>::value>::Call(Inst, ##__VA_ARGS__)
