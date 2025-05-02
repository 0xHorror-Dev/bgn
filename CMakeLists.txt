cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(bign C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_C_EXTENSIONS OFF)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Werror)
    
    add_compile_options(-Wall -Wextra)
    # More specific warnings can be added as needed
    add_compile_options(-Wconversion -Wshadow -Wundef -Wunused)
endif()

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

if(MSVC)
    add_compile_options(/W4 /WX)  
endif()

add_subdirectory("bign")
add_subdirectory("tests")
