#pragma once

#include <string>

#include <glad/glad.h>

/// \brief Initializes and compiles an OpenGL shader program object.
///
/// \param vertex_shader The vertex shader object to use.
/// \param fragment_shader The fragment shader object to use.
///
/// \return The OpenGL ID uniquely identifying the shader program object.
GLuint create_program(GLuint vertex_shader, GLuint fragment_shader);

/// \brief Initializes and compiles an OpenGL shader object.
///
/// \param type The type of shader to create. Currently, only GL_VERTEX_SHADER
///             and GL_FRAGMENT_SHADER are supported.
/// \param source The source code for the shader.
///
/// \return The OpenGL ID uniquely identifying the shader object.
GLuint create_shader(GLenum type, const char *source);

/// \brief Gets the resource path from the command-line arguments passed to the
///        program.
///
/// \param argc The number of command-line arguments.
/// \param argv The command-line arguments themselves.
///
/// \return The path to the directory containing program resources on success,
///         or an empty string on failure.
std::string get_resource_path(int argc, char **argv);

/// \brief Load the source code of a shader.
///
/// \param path The path to the file containing the source code. Ideally, this
///             is an absolute path. The get_resource_path function can be used
///             to get the path of the resource directory, which can then be
///             prepended onto resource files.
///
/// \return The entire contents of the file at path.
std::string load_shader_source(const std::string &path);