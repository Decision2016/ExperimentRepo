cmake_minimum_required(VERSION 3.15)
project(SGProject)

set(CMAKE_CXX_STANDARD 11)

include_directories(include include/utils)

add_library(common STATIC
        source/utils/BitReader.cpp
        source/Appender.cpp source/LSBEncoder.cpp include/LSBEncoder.h source/HiddenReader.cpp include/HiddenReader.h)

add_executable(SGProject main.cpp)

target_link_libraries(SGProject common)