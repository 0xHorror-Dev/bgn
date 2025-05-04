cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(bign C)

add_executable(test "main.c")

target_link_libraries(test PRIVATE bign)

add_custom_command(
        TARGET test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:bign>
                $<TARGET_FILE_DIR:test>)
