cmake_minimum_required(VERSION 3.1)
project(assignment_4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp)
add_executable(assignment_4 ${SOURCE_FILES} src/Image.cpp src/Image.h)
