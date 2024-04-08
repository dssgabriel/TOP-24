cmake_minimum_required(VERSION 3.16)
set(CMAKE_COLOR_DIAGNOSTICS ON)

project(TOP-LAB_03-integer_sum_redux LANGUAGES CXX)
add_compile_options(-Wall -Wextra -Wconversion)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt REQUIRED)
find_package(OpenMP REQUIRED)

add_library(seq src/sequential.cpp)
target_include_directories(seq PUBLIC include)
target_link_libraries(seq OpenMP::OpenMP_CXX)

add_executable(int-sum-redux src/main.cpp)
target_include_directories(int-sum-redux PUBLIC include)
target_link_libraries(int-sum-redux seq fmt::fmt OpenMP::OpenMP_CXX m)
