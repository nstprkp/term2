cmake_minimum_required(VERSION 3.23)
project(labs)

file(GLOB LABS LIST_DIRECTORIES true "labs/*")

foreach(LAB ${LABS})
  if(IS_DIRECTORY ${LAB})
    get_filename_component(TARGET ${LAB} NAME)
    file(GLOB_RECURSE SOURCES "${LAB}/*.c")
    add_executable(${TARGET} ${SOURCES})
  endif()
endforeach()
