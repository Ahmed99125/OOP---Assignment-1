cmake_minimum_required(VERSION 3.23)
project(Assignment_1___image_filtering)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(
        bmplib.cpp
        bmplib.h
        main.cpp)
