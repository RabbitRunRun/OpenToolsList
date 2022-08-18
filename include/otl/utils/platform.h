//
// Created by kevin on 2022/8/18.
//

#ifndef OTL_PLATFORM_H
#define OTL_PLATFORM_H


/**
 * Platform
 * including
 *  OTL_PLATFORM_OS_WINDOWS
 *  OTL_PLATFORM_OS_MAC
 *  OTL_PLATFORM_OS_LINUX
 *  OTL_PLATFORM_OS_IOS
 *  OTL_PLATFORM_OS_ANDROID
 */
#if defined(__ANDROID__)
#   define OTL_PLATFORM_OS_ANDROID 1
#   define OTL_PLATFORM_OS_WINDOWS 0
#   define OTL_PLATFORM_OS_MAC     0
#   define OTL_PLATFORM_OS_LINUX   1
#   define OTL_PLATFORM_OS_IOS     0
#elif defined(__WINDOWS__) || defined(_WIN32) || defined(WIN32) || defined(_WIN64) || \
    defined(WIN64) || defined(__WIN32__) || defined(__TOS_WIN__)
#   define OTL_PLATFORM_OS_ANDROID 0
#   define OTL_PLATFORM_OS_WINDOWS 1
#   define OTL_PLATFORM_OS_MAC     0
#   define OTL_PLATFORM_OS_LINUX   0
#   define OTL_PLATFORM_OS_IOS     0
#elif defined(__MACOSX) || defined(__MACOS_CLASSIC__) || defined(__APPLE__) || defined(__apple__)
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE
#   define OTL_PLATFORM_OS_ANDROID 0
#   define OTL_PLATFORM_OS_WINDOWS 0
#   define OTL_PLATFORM_OS_MAC     0
#   define OTL_PLATFORM_OS_LINUX   0
#   define OTL_PLATFORM_OS_IOS     1
#elif TARGET_OS_MAC
#   define OTL_PLATFORM_OS_ANDROID 0
#   define OTL_PLATFORM_OS_WINDOWS 0
#   define OTL_PLATFORM_OS_MAC     1
#   define OTL_PLATFORM_OS_LINUX   0
#   define OTL_PLATFORM_OS_IOS     0
#else
//#   error "Unknown Apple platform"
#   define OTL_PLATFORM_OS_ANDROID 0
#   define OTL_PLATFORM_OS_WINDOWS 0
#   define OTL_PLATFORM_OS_MAC     0
#   define OTL_PLATFORM_OS_LINUX   0
#   define OTL_PLATFORM_OS_IOS     0
#endif
#elif defined(__linux__) || defined(linux) || defined(__linux) || defined(__LINUX__) || \
    defined(LINUX) || defined(_LINUX)
#   define OTL_PLATFORM_OS_ANDROID 0
#   define OTL_PLATFORM_OS_WINDOWS 0
#   define OTL_PLATFORM_OS_MAC     0
#   define OTL_PLATFORM_OS_LINUX   1
#   define OTL_PLATFORM_OS_IOS     0
#else
//#   error Unknown OS
#   define OTL_PLATFORM_OS_ANDROID 0
#   define OTL_PLATFORM_OS_WINDOWS 0
#   define OTL_PLATFORM_OS_MAC     0
#   define OTL_PLATFORM_OS_LINUX   0
#   define OTL_PLATFORM_OS_IOS     0

#endif

/**
 * System bits
 * including
 *  OTL_PLATFORM_BIOTL_32
 *  OTL_PLATFORM_BIOTL_64
 */
#if defined(_WIN64) || defined(WIN64) || defined(__amd64__) || defined(__amd64) || \
    defined(__LP64__) || defined(_LP64) || defined(__x86_64__) || defined(__x86_64) || \
    defined(_M_X64) || defined(__ia64__) || defined(_IA64) || defined(__IA64__) || \
    defined(__ia64) || defined(_M_IA64)
#   define OTL_PLATFORM_BIOTL_16 0
#   define OTL_PLATFORM_BIOTL_32 0
#   define OTL_PLATFORM_BIOTL_64 1
#elif defined(_WIN32) || defined(WIN32) || defined(__32BIT__) || defined(__ILP32__) || \
    defined(_ILP32) || defined(i386) || defined(__i386__) || defined(__i486__) || \
    defined(__i586__) || defined(__i686__) || defined(__i386) || defined(_M_IX86) || \
    defined(__X86__) || defined(_X86_) || defined(__I86__)
#   define OTL_PLATFORM_BIOTL_16 0
#   define OTL_PLATFORM_BIOTL_32 1
#   define OTL_PLATFORM_BIOTL_64 0
#else
//#   error Unknown system bit-length
#   define OTL_PLATFORM_BIOTL_16 0
#   define OTL_PLATFORM_BIOTL_32 0
#   define OTL_PLATFORM_BIOTL_64 0
#endif

/**
 * Compiler
 * including
 *  OTL_PLATFORM_CC_MSVC
 *  OTL_PLATFORM_CC_MINGW
 *  OTL_PLATFORM_CC_GCC
 */
#if defined(_MSC_VER)
#   define OTL_PLATFORM_CC_MSVC  1
#   define OTL_PLATFORM_CC_MINGW 0
#   define OTL_PLATFORM_CC_GCC   0
#elif defined(__MINGW32__) || defined(__MINGW64__)
#   define OTL_PLATFORM_CC_MSVC  0
#   define OTL_PLATFORM_CC_MINGW 1
#   define OTL_PLATFORM_CC_GCC   1
#elif defined(__GNUG__) || defined(__GNUC__)
#   define OTL_PLATFORM_CC_MSVC  0
#   define OTL_PLATFORM_CC_MINGW 0
#   define OTL_PLATFORM_CC_GCC   1
#else
//#   error Unknown compiler
#   define OTL_PLATFORM_CC_MSVC  0
#   define OTL_PLATFORM_CC_MINGW 0
#   define OTL_PLATFORM_CC_GCC   0
#endif

#if defined(__x86_64__) || defined(__amd64__) || defined(_M_IX86) || \
    defined(_M_X64)
#define OTL_PLATFORM_IS_X86 1
#endif

#endif //OTL_PLATFORM_H
