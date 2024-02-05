cmake_minimum_required(VERSION 3.22)
project(IPv4_chat
        VERSION 1.0
        DESCRIPTION "infotecs internship task"
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(lib)
add_subdirectory(bin)
