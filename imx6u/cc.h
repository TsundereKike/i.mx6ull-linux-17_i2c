#ifndef __CC_H
#define __CC_H

#define OFF     0
#define ON      1

#define __I     volatile
#define __O     volatile
#define __IO    volatile

typedef signed char         int8_t;
typedef signed short        int16_t;
typedef signed int          int32_t;
typedef signed long long    int64_t;
typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;

typedef signed char         s8;
typedef signed short        s16;
typedef signed int          s32;
typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;
#endif