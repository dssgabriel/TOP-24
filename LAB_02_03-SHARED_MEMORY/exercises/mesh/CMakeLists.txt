cmake_minimum_required(VERSION 3.16)
set(CMAKE_COLOR_DIAGNOSTICS ON)

project(TOP-LAB_03-mesh LANGUAGES C)
add_compile_options(-Wall -Wextra -Wconversion)

add_executable(mesh src/main.c)
