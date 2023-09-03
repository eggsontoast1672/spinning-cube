#include "error.hpp"

#include <iostream>
#include <string>

#include <glad/glad.h>

void glCheckError(const std::string &file, int line, const std::string &expression) noexcept {
    GLenum error = glGetError();
    if (error == GL_NO_ERROR) {
        return;
    }

    std::string repr = "Unknown Error";
    switch (error) {
    case GL_INVALID_ENUM:
        repr = "GL_INVALID_ENUM";
        break;
    case GL_INVALID_VALUE:
        repr = "GL_INVALID_VALUE";
        break;
    case GL_INVALID_OPERATION:
        repr = "GL_INVALID_OPERATION";
        break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        repr = "GL_INVALID_FRAMEBUFFER_OPERATION";
        break;
    case GL_OUT_OF_MEMORY:
        repr = "GL_OUT_OF_MEMORY";
        break;
    }

    std::cerr
        << file << ":" << line << ": " << expression << " (" << repr << ")"
        << std::endl;
}
