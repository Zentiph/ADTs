///
/// @file err.c
/// @author Zentiph
/// @brief Error printing utility.
/// @version 0.1
/// @date 2025-10-22
///
/// @copyright Copyright (c) 2025
///
///

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void error(int code, char *format, ...) {
   va_list ap;
   va_start(ap, format);
   vfprintf(stderr, format, ap);
   va_end(ap);

   _exit(code);
}