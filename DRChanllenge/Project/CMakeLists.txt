cmake_minimum_required(VERSION 3.15)
project(Project)

set(CMAKE_CXX_STANDARD 11)

include_directories(include
        include/utils
        include/structs)

add_library(common STATIC
        source/structs/HuffmanTree.cpp
        source/utils/BitReader.cpp
        source/utils/ZigZag.cpp
        source/Parser.cpp
        source/structs/Matrix.cpp
        source/utils/IDCT.cpp
        source/utils/BitOutput.cpp
        source/Recover.cpp include/Recover.h
        source/utils/SkipReader.cpp source/utils/Exporter.cpp include/utils/Exporter.h)

add_executable(Project main.cpp)

target_link_libraries(Project common)