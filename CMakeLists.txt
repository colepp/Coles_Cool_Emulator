
cmake_minimum_required(VERSION 3.16)

project(nesEmulator C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(file_parse_test
        main.c
        parser/file_parser.c
        cartridge/cartridge.c
        cpu/cpu.c
        memory/memory_manager.c
)

target_include_directories(file_parse_test PRIVATE
        cpu
        memory
        parser
        cartridge
)
