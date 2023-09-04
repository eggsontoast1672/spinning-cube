cmake_minimum_required(VERSION 3.5)
project(SpinningCube VERSION 0.0.5)

find_package(PkgConfig)
pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(GLFW REQUIRED glfw3)

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
target_compile_options(cube PRIVATE -Wall -Wextra -Wpedantic)
target_include_directories(cube PRIVATE include)
target_link_libraries(cube PRIVATE ${GLEW_LIBRARIES} ${GLFW_LIBRARIES})

add_custom_target(run COMMAND cube WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
