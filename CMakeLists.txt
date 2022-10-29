cmake_minimum_required(VERSION 3.22)
project(Project03 C)

set(CMAKE_C_STANDARD 99)

add_executable(Project03 Benchmark.c MatrixC.h MatrixC.c)
