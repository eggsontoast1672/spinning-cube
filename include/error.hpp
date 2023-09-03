#pragma once

#include <string>

#ifndef NDEBUG
    #define glCall(expr)                             \
        do {                                         \
            expr;                                    \
            glCheckError(__FILE__, __LINE__, #expr); \
        } while (false)
#else
    #define glCall(expr) (expr)
#endif

void glCheckError(const std::string &file, int line, const std::string &expression) noexcept;
