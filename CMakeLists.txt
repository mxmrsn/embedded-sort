cmake_minimum_required(VERSION 3.7.0)
project(embedded-sort C)

set(CMAKE_C_COMPILER gcc)

include_directories(
    include
)

add_executable(embedded-sort src/main.c)
