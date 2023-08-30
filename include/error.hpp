#pragma once

#include <string>

#ifndef NDEBUG
#define gl_check(expr)                             \
    do {                                           \
        expr;                                      \
        gl_check_error(__FILE__, __LINE__, #expr); \
    } while (false)
#else
#define gl_check(expr) (expr)
#endif

void gl_check_error(const std::string &file, int line, const std::string &expression);
