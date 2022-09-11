/*****************************************************************************\
*  Copyright (c) 2022 Tucan Software Pty Ltd. All rights reserved.
*
*  MIT License
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy 
*  of this software and associated documentation files (the "Software"), to 
*  deal in the Software without restriction, including without limitation the 
*  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
*  sell copies of the Software, and to permit persons to whom the Software is 
*  furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in 
*  all copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
*  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
*  IN THE SOFTWARE.
*
*  You should have received a copy of the MIT License along with this program.
*  If not, see https://opensource.org/licenses/MIT.
\*****************************************************************************/
#pragma once

/**************************************************************\
* Detect supported operating system
\**************************************************************/
#if defined(_WIN32)
   #define XP_OS_NAME	"Windows"
   #define XP_OS_WIN32
   #if defined(_WIN64)
      #define XP_OS_WIN64
   #endif
#elif defined(__linux__)
   #define XP_OS_NAME	"Linux"
   #define XP_OS_LINUX
   #define XP_OS_UNIX      
#elif defined(__APPLE__) && defined(__MACH__)
   #define XP_OS_NAME	"Mac OS/X"
   #define XP_OS_MACOSX
   #define XP_OS_UNIX      	
#elif defined( __FreeBSD__ ) || defined( __OpenBSD__ ) || defined( __NetBSD__ )
   #if defined( __FreeBSD__ )
   	#define XP_OS_NAME	"FreeBSD"
   	#define XP_OS_FREEBSD
   #endif
   #if defined( __OpenBSD__ )
   	#define XP_OS_NAME	"OpenBSD"
   	#define XP_OS_OPENBSD
   #endif
   #if defined( __NetBSD__ )
   	#define XP_OS_NAME	"NetBSD"
   	#define XP_OS_NETBSD
   #endif
   #define XP_OS_BSD
   #define XP_OS_UNIX
#else
   #pragma error "Unknown operating system"
#endif

/**************************************************************\
*
* detect suported compilers
*
\**************************************************************/
#if defined(_MSC_VER)
   #define XP_CC_NAME   "Microsoft Visual Studio"
   #define XP_CC_MSVC    _MSC_VER
#elif defined(__clang__)
   #define XP_CC_NAME   "Clang"
   #define XP_CC_CLANG  ((__clang_major * 100) + __clang_minor__)
#elif defined(__GNUC__)
   #define XP_CC_NAME   "GNU C++"
   #define XP_CC_GNUC   ((__GNUC__ * 100) + __GNUC_MINOR__)
#else
   #pragma error "Unknown C++ compiler"
#endif

/**************************************************************\
*
* detect supported architectures
*
\**************************************************************/
#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_X64) || defined(_M_AMD64)
   #define XP_CPU_IX86
   #define XP_CPU_AMD64
   #define XP_CPU_NAME  "AMD 64"
   #define XP_CPU_64BITS
#elif defined(i386) || defined(__i386) || defined(__i386__) || defined(__i386) || defined(__i386) || defined(__IA32__) || \
      defined(_M_I86) || defined(_M_IX86) || defined(__X86__) || defined(_X86_) || defined(__THW_INTEL__) || \
      defined(__I86__) || defined(__INTEL__)
   #define XP_CPU_IX86
   #define XP_CPU_NAME  "Intel"
   #define XP_CPU_32BITS
#elif defined(__arm__) || defined(_M_ARM)
   #define XP_ARM
   #define XP_CPU_NAME  "ARM"
#else
   #pragma error "Unknown CPU architecture"
#endif

/**************************************************************\
*
* detect path, extension and driver separators
*
\**************************************************************/
#ifndef XP_PATH_SEPARATOR
   #if defined(XP_OS_WIN32)
      #define XP_PATH_SEPARATOR  '\\'
      #define XP_EXT_SEPARATOR   '.'
      #define XP_DRIVE_SEPARATOR ':'
   #else
      #define XP_PATH_SEPARATOR  '/'
      #define XP_EXT_SEPARATOR   '.'
      #define XP_DRIVE_SEPARATOR '\0'
   #endif
#endif

/**************************************************************\
*
* Define additional integer types
*
\**************************************************************/
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

   typedef unsigned char   byte_t;
   typedef uint64_t        timeout_t;
   const   timeout_t       timeout_forever = UINT64_MAX;
   typedef size_t          count_t;
   typedef unsigned int    offset_t;

#ifdef __cplusplus
} /* extern "C" */
#endif
