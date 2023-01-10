file(GLOB_RECURSE HEADER_FILES
    **/*[.h, .hpp]
)

file(GLOB_RECURSE SOURCE_FILES
    *.cpp
)

add_executable(
    esen
    main.cpp
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

target_include_directories(esen
    PRIVATE
    include
)

target_link_libraries(esen
    PRIVATE
)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})