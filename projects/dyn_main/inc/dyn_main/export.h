#ifndef DYN_MAIN_EXPORT_H
#define DYN_MAIN_EXPORT_H

#define dyn_main_ex

#if defined(dyn_main_shared)
#undef dyn_main_ex

#if defined(_WIN32) || defined(__CYGWIN__)
#ifdef dyn_main_inside
#define dyn_main_ex __declspec(dllexport)
#else
#define dyn_main_ex __declspec(dllimport)
#endif

#elif defined(__GNUC__) || defined(__clang__)
#ifdef dyn_main_inside
#define dyn_main_ex                         \
  __attribute__((visibility("default")))
#else
#define dyn_main_ex
#endif

#else
#error "unknown compiler"
#endif

#endif

#endif
