// header guard
#pragma once

#define CHAR_BIT    8                    // the number of bits in a byte.
#define SCHAR_MIN   -128                 // the minimum value for a signed char.
#define SCHAR_MAX   +127                 // the maximum value for a signed char.
#define UCHAR_MAX   255	                 // the maximum value for an unsigned char.
#define CHAR_MIN    -128                 // the minimum value for type char and its value will be equal to SCHAR_MIN if char represents negative values, otherwise zero.
#define CHAR_MAX    +127                 // the value for type char and its value will be equal to SCHAR_MAX if char represents negative values, otherwise UCHAR_MAX.
#define MB_LEN_MAX  16                   // the maximum number of bytes in a multi-byte character.
#define SHRT_MIN    -32768               // the minimum value for a short int.
#define SHRT_MAX    +32767               // the maximum value for a short int.
#define USHRT_MAX   65535                // the maximum value for an unsigned short int.
#define INT_MIN     -2147483648          // the minimum value for an int.
#define INT_MAX     +2147483647          // the maximum value for an int.
#define UINT_MAX    4294967295           // the maximum value for an unsigned int.
#define LONG_MIN    -9223372036854775808 // the minimum value for a long int.
#define LONG_MAX    +9223372036854775807 // the maximum value for a long int.
#define ULONG_MAX   18446744073709551615 // the maximum value for an unsigned long int.
