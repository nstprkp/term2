cmake_minimum_required(VERSION 3.23)
project(laba4akinator C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(lib)
add_subdirectory(data)

add_executable(laba4akinator main.c)

target_link_libraries(laba4akinator myLib)
target_link_libraries(laba4akinator myData)
