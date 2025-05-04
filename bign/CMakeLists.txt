cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(bign C)

option(BIGN_SHARED "Build shared library" OFF)

set(BIGN_SOURCES "source/bign.c" "source/add.c" "source/mul.c" "source/div.c" "source/cmp.c")

if(BIGN_SHARED)
add_library(bign SHARED ${BIGN_SOURCES})
target_compile_definitions(bign PUBLIC BIGN_SHARED)
else()
add_library(bign STATIC ${BIGN_SOURCES})
endif(BIGN_SHARED )


target_include_directories(bign PUBLIC "include/")
target_link_libraries(bign PRIVATE libomp)

