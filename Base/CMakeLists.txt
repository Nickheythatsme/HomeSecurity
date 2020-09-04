cmake_minimum_required (VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project (HomeSecurityBase)

add_subdirectory (tests)
add_subdirectory (src)

add_executable (main main.cpp)
add_executable (server server.cpp)
