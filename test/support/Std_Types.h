#ifndef STD_TYPES_H_
#define STD_TYPES_H_

#include <stdint.h>

typedef int8_t sint8;
typedef int16_t sint16;
typedef int32_t sint32;
typedef int64_t sint64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int BOOL;

#define TRUE 1
#define FALSE 0

typedef enum
{
   E_NOT_OK = -1,
   E_OK
}Std_ReturnType;

#define NULL_PTR ((void *)0)


#endif // STD_TYPES_H_
