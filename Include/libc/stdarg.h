<<<<<<< HEAD
#pragma once
=======
#ifndef __STDARG_H__
#define __STDARG_H__
>>>>>>> 0724837fc22bc01f98fa21061ef9c01bbe60f241

typedef __builtin_va_list va_list;

// define vardiac args macros

#define va_start(arg_pointer, param) __builtin_va_start(arg_pointer, param)
#define va_end(arg_pointer)          __builtin_va_end(arg_pointer)
#define va_arg(arg_pointer, type)    __builtin_va_arg(arg_pointer, type)
