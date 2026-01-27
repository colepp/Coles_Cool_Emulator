
cmake_minimum_required(VERSION 3.1)

project(nesEmulator)

set(CMAKE_C_STANDARD 17)

add_executable(file_parse_test main.c parser/file_parser.c cartridge/cartridge.c
        cpu/cpu.h
        memory/memory_manager.c)