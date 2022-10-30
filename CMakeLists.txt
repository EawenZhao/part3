cmake_minimum_required(VERSION 3.23)
project(part3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(part3
        application.cpp
        application.h
        backtrack.cpp
        backtrack.h
        main.cpp
        position.cpp
        position.h)
