cmake_minimum_required(VERSION 3.7)
project(geom)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-Werror -Wall)

set(SOURCE_FILES main.cpp Line.cpp Line.h other_func.cpp other_func.h Point.cpp Point.h Ray.cpp Ray.h Segment.cpp Segment.h Vector.cpp Vector.h task.h Polygon.cpp Polygon.h BaseShape.h)
add_executable(geom ${SOURCE_FILES})