#pragma once

typedef __builtin_va_list va_list;

// define vardiac args macros

#define va_start(arg_pointer, param) __builtin_va_start(arg_pointer, param)
#define va_end(arg_pointer)          __builtin_va_end(arg_pointer)
#define va_arg(arg_pointer, type)    __builtin_va_arg(arg_pointer, type)
