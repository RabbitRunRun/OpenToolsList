//
// Created by kevin on 2022/8/19.
//

#ifndef OTL_API_H
#define OTL_API_H


#include "platform.h"

#define OTL_EXTERN_C extern "C"

#if OTL_PLATFORM_OS_WINDOWS
#   define OTL_DLL_IMPORT __declspec(dllimport)
#   define OTL_DLL_EXPORT __declspec(dllexport)
#   define OTL_DLL_LOCAL
#else
#   if defined(__GNUC__) && __GNUC__ >= 4
#       define OTL_DLL_IMPORT __attribute__((visibility("default")))
#       define OTL_DLL_EXPORT __attribute__((visibility("default")))
#       define OTL_DLL_LOCAL  __attribute__((visibility("hidden")))
#   else
#       define OTL_DLL_IMPORT
#       define OTL_DLL_EXPORT
#       define OTL_DLL_LOCAL
#   endif
#endif

#define OTL_API OTL_DLL_EXPORT

#ifdef __cplusplus
#   define OTL_C_API OTL_EXTERN_C OTL_API
#else
#   define OTL_C_API OTL_API
#endif

#ifndef OTL_UNUSED
#   define OTL_UNUSED(x) ((void)(x))
#endif

#ifdef OTL_USE_DEBUG_API
#define OTL_DEBUG_API OTL_API
#else
#define OTL_DEBUG_API
#endif

#endif //OTL_API_H
