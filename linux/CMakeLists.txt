cmake_minimum_required(VERSION 3.10)
project(EvPong C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES src/*.c)

find_package(SDL3 REQUIRED)
add_executable(EvPong ${SOURCES})
target_link_libraries(EvPong PRIVATE SDL3::SDL3)