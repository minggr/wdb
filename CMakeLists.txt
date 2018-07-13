cmake_minimum_required(VERSION 2.8)
project(wdb)

include_directories(src)

file(GLOB SOURCES "src/*.cc" "src/*.h")

add_executable(wdb ${SOURCES})

add_subdirectory(googletest)
add_subdirectory(test)
