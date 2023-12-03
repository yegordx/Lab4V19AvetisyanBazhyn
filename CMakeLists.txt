cmake_minimum_required(VERSION 3.20)

project(prog)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(prog main.cpp Struct.cpp Struct.h)