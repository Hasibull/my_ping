cmake_minimum_required(VERSION 3.10)
project(ping_cross C)

set(CMAKE_C_STANDARD 99)

# Platform-specific sources
if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
    add_executable(ping_cross
        src/main.c
        src/ping_common.c
        src/ping_windows.c
    )
    target_link_libraries(ping_cross iphlpapi ws2_32)
else()
    add_executable(ping_cross
        src/main.c
        src/ping_common.c
        src/ping_unix.c
    )
endif()

target_include_directories(ping_cross PRIVATE include)
