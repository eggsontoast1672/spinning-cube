cmake_minimum_required(VERSION 3.5)

project(spinning-cube)

add_subdirectory(lib/glad)

find_package(PkgConfig)

pkg_check_modules(GLFW REQUIRED glfw3)

add_executable(cube src/main.cpp)

target_compile_options(cube PRIVATE -Wall -Werror -Wextra -Wpedantic)
target_include_directories(cube PRIVATE include)
target_link_libraries(cube PRIVATE glad ${GLFW_LIBRARIES})