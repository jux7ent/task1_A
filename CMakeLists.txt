cmake_minimum_required(VERSION 3.6)
project(task1_A)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Point.h Point.cpp Vector.h Vector.cpp Line.cpp Line.h)
add_executable(task1_A ${SOURCE_FILES})