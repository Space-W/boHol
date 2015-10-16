/*
 * Common socket defines
 **/

#ifndef __NETWORK_SOCKET_DEFINES_H__
#define __NETWORK_SOCKET_DEFINES_H__

#include <platform/global_defines.h>

#if defined(PLATFORM_LINUX)
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#elif defined(PLATFORM_WINDOWS)

#endif

#endif // __NETWORK_SOCKET_DEFINES_H__
