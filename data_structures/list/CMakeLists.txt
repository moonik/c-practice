cmake_minimum_required(VERSION 3.12)
set(CMAKE_C_STANDARD 99)
project(linked_list)
set(SOURCE_FILES main.c List.c List.h)
add_executable(list ${SOURCE_FILES})