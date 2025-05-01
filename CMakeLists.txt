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

if(MSVC)
    add_compile_options(/W4 /WX)  
endif()

add_subdirectory("bign")
add_subdirectory("tests")
