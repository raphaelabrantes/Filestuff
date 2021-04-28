cmake_minimum_required(VERSION 3.19)
project(Filestuff C)

set(CMAKE_C_STANDARD 99)
file(GLOB SOURCES include/*)
add_compile_options(-Wall -Wextra -pedantic -Werror)
add_executable(Filestuff main.c ${SOURCES})