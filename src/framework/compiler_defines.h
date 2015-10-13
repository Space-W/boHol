/*
 *  You know what...
 */

#ifndef __PLATFORM_COMPILER_DEFINES_H__
#define __PLATFORM_COMPILER_DEFINES_H__

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

#endif // __PLATFORM_COMPILER_DEFINES_H__
