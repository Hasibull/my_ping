cmake_minimum_required(VERSION 3.10)
project(my_ping C)

set(CMAKE_C_STANDARD 99)

# Platform-specific sources
if(WIN32)
    add_executable(my_ping
        src/main.c
        src/common.c
        src/ping_windows.c
    )
    target_link_libraries(my_ping ws2_32)
else()
    add_executable(my_ping
        src/main.c
        src/common.c
        src/ping_unix.c
    )
endif()

target_include_directories(my_ping PRIVATE include)
