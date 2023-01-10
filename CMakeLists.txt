cmake_minimum_required(VERSION 3.20)

project(Esen)
get_filename_component(PROJECT_DIRECTORY ./ ABSOLUTE)
add_compile_definitions(PROJECT_DIRECTORY="${PROJECT_DIRECTORY}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER_VERSION 11.0)

include(conan.cmake)

add_subdirectory(src)

option(RUN_TESTS "Build the tests" ON)

if(RUN_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    add_subdirectory(test)
endif()
