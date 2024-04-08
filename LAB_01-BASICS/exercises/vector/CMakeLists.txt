cmake_minimum_required(VERSION 3.16)
set(CMAKE_COLOR_DIAGNOSTICS ON)

project(TOP-LAB01-vector LANGUAGES C)

add_library(vec SHARED src/vector.c)
target_include_directories(vec PRIVATE include)
add_library(compute SHARED src/compute.c)
target_include_directories(compute PRIVATE include)

add_executable(vector src/main.c)
target_include_directories(vector PRIVATE include)
target_link_libraries(vector vec compute)
target_compile_options(vector PUBLIC -Wall -Wextra -Wconversion)
