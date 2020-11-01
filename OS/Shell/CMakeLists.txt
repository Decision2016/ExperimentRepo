# cmake_minimum_required(VERSION <specify CMake version here>)
project(Shell)

set(CMAKE_CXX_STANDARD 11)

add_executable(Shell main.cpp)

include_directories(header)

add_library(common SHARED
        source/Shell.cpp
        source/Queue.cpp
        source/PCB.cpp
        source/Resource.cpp
        source/Process.cpp
        source/LinkList.cpp
        )

target_link_libraries(Shell common)