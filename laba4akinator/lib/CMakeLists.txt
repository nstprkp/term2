cmake_minimum_required(VERSION 3.23)

set(LIB_PROJECT_NAME myLib)

set(LIB_INCLUDES
        treeAPI.c
        treeAPI.h
        )

add_library(${LIB_PROJECT_NAME} STATIC
        ${LIB_INCLUDES}
        )

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
        ${LIB_INCLUDES}
        )

target_include_directories(${LIB_PROJECT_NAME} PUBLIC .)