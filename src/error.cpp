#include "error.hpp"

#include <iostream>

#include <glad/glad.h>

void gl_check_error(const std::string &file, int line, const std::string &expression) {
    const GLenum code = glGetError();
    if (code == GL_NO_ERROR) {
        return;
    }

    std::string error;

    switch (code) {
    case GL_INVALID_ENUM:
        error = "GL_INVALID_ENUM";
        break;
    case GL_INVALID_VALUE:
        error = "GL_INVALID_VALUE";
        break;
    case GL_INVALID_OPERATION:
        error = "GL_INVALID_OPERATION";
        break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        error = "GL_INVALID_FRAMEBUFFER_OPERATION";
        break;
    case GL_OUT_OF_MEMORY:
        error = "GL_OUT_OF_MEMORY";
        break;
    }

    std::cerr
        << "Recieved " << error << " in file " << file << ", on line " << line
        << ", in expression " << expression << std::endl;
}