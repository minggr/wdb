cmake_minimum_required(VERSION 2.8)
project(wdb)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")
include_directories(src)
include_directories(gossip)

file(GLOB SOURCES "src/*.cc" "src/*.h" "gossip/*.cc" "gossip/*.h")

add_executable(wdb ${SOURCES})

add_subdirectory(googletest)
add_subdirectory(test)
