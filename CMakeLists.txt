
cmake_minimum_required(VERSION 3.1)

project(nesEmulator)

set(CMAKE_C_STANDARD 17)

add_executable(file_parse_test main.c file_parser.c cartridge.c)