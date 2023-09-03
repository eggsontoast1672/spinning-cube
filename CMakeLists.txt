cmake_minimum_required(VERSION 3.5)

project(SpinningCube VERSION 0.0.5)

set(CMAKE_BUILD_TYPE Debug)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glad)
add_subdirectory(lib/glfw)
add_subdirectory(lib/stb)

add_executable(
  cube
  src/error.cpp
  src/index_buffer.cpp
  src/main.cpp
  src/shader.cpp
  src/vertex_array.cpp
  src/vertex_buffer.cpp
  src/window.cpp
)

set_property(TARGET cube PROPERTY CXX_EXTENSIONS OFF)
set_property(TARGET cube PROPERTY CXX_STANDARD 11)
set_property(TARGET cube PROPERTY CXX_STANDARD_REQUIRED ON)

target_compile_definitions(cube PRIVATE GLFW_INCLUDE_NONE)
target_include_directories(cube PRIVATE include)
target_link_libraries(cube PRIVATE glad glfw stb)

if(NOT MSVC)
  target_compile_options(cube PRIVATE -Wall -Wextra -Wpedantic)
endif()
