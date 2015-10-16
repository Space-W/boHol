/*
 * Global include files
 **/

#ifndef __FRAMEWORK_GLOBAL_H__
#define __FRAMEWORK_GLOBAL_H__

#include <platform/compiler_defines.h>
#include <platform/type_defines.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <time.h>

#include <map>
#include <list>
#include <string>
#include <vector>
#include <iterator>

#if defined(PLATFORM_LINUX)
#include <unistd.h>
#include <strings.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#elif defined(PLATFORM_WINDOWS)
// Todo
// Include windows system files here
#endif


#endif //__FRAMEWORK_GLOBAL_H__
