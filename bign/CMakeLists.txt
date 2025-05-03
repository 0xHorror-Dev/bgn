cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(bign C)

add_library(bign STATIC "source/bign.c" "source/add.c" "source/mul.c")

target_include_directories(bign PUBLIC "include/")
target_link_libraries(bign PRIVATE libomp)