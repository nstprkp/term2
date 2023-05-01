cmake_minimum_required(VERSION 3.23)

set(DATA_PROJECT_NAME myData)

set(DATA_INCLUDES
        Source.c
        Header.h
        )

add_library(${DATA_PROJECT_NAME} STATIC
        ${DATA_INCLUDES}
        )

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
        ${DATA_INCLUDES}
        )

target_include_directories(${DATA_PROJECT_NAME} PUBLIC .)