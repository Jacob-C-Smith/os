// header guard
#pragma once 

// type definitions
typedef char* va_list;

// preprocessor macros
#define va_start(ap, last) (ap = (char*)&(last) + sizeof(last))
#define va_end(ap) (ap = (va_list)0)
#define va_arg(ap, type) (*(type*)((ap += sizeof(type)) - sizeof(type)))
