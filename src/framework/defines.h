/*
 * Common defination is here, include OS, compilers and some base data types.
 */

#ifndef __FRAMEWORK_DEFINES_H__
#define __FRAMEWORK_DEFINES_H__

#include <sys/types.h>

// OS types
#define PLATFORM_WINDOWS    0
#define PLATFORM_LINUX      1

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__WIN32__) || defined(_WIN64) 
#   define PLATFORM PLATFORM_WINDOWS
#elif defined(linux) || defined(__linux) || defined(__linux__)
#   define PLATFORM PLATFORM_LINUX 
#else
#   pragma error: "FATAL ERROR: Unkown system."
#endif

// Compiler types
#define COMPILER_MICROSOFT  0
#define COMPILER_GNU        1

#if defined(_MSC_VER)
#   define COMPILER COMPILER_MICROSOFT
#elif defined(__GNUC__) || defined(__GNUG__)
#   define COMPILER COMPILER_GNU
#else
#   pragma error: "FATAL ERROR: Unkown compiler."
#endif

#if COMPILER == COMPILER_MICROSOFT
#   pragma warning(disable:4267) // size_t to int maybe lost data
#   pragma warning(disable:4786) // identifier war truncated to '255'
#endif

// Base data types
#if COMPILER == COMPILER_MICROSOFT 
typedef __int64             int64;
typedef long                int32;
typedef short               int16;
typedef signed char         int8;
typedef unsigned __int64    uint64;
typedef unsigned long       uint32;
typedef unsigned short      uint16;
typedef unsigned char       uint8;
#else
typedef __int64_t           int64;
typedef __int32_t           int32;
typedef __int16_t           int16;
typedef __int8_t            int8;
typedef __uint64_t          uint64;
typedef __uint32_t          uint32;
typedef __uint16_t          uint16;
typedef __uint8_t           uint8;
#endif

#endif // __FRAMEWORK_DEFINES_H__
