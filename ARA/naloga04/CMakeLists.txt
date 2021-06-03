cmake_minimum_required(VERSION 3.17)
project(naloga04)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(naloga04
        BinReader.cpp
        BinReader.h
        BinWriter.cpp
        BinWriter.h
        main.cpp)
