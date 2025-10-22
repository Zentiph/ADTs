///
/// @file err.h
/// @author Zentiph
/// @brief Error printing interface.
/// @version 1.0
/// @date 2025-10-22
///
/// @copyright Copyright (c) 2025
///
///

#ifndef ZEN_ERR_H
#define ZEN_ERR_H

///
/// @brief Print an error and exit.
///
/// @param code   - The error code.
/// @param format - The format string.
/// @param ...    - The format arguments.
///
void error(int code, char *format, ...) __attribute__((noreturn));

#endif // ZEN_ERR_H