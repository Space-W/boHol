/*
 * Basic types was defined here.
 */

#ifndef __PLATFORM_TYPE_DEFINES_H__
#define __PLATFORM_TYPE_DEFINES_H__

#include <sys/types.h>

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

#endif // __PLATFORM_TYPE_DEFINES_H__
