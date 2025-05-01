cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(bign C)

add_executable(test "main.c")

target_link_libraries(test PRIVATE bign)