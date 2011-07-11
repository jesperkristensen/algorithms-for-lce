#ifndef _TYPES_H
#define _TYPES_H

#if _MSC_VER

typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
typedef __int32 int32_t;
#define INT32_MAX _I32_MAX
#define snprintf sprintf_s
double log2(double n);

TODO: define what intptr_t and INTPTR_MAX is

#else
#define __STDC_LIMIT_MACROS
#include <stdint.h>
#endif

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef int32_t int32;

#endif
