file(GLOB_RECURSE HEADER_FILES
    ${CMAKE_SOURCE_DIR}/src/publisher/*.h
    ${CMAKE_SOURCE_DIR}/src/subscriber/*.h
    ${CMAKE_SOURCE_DIR}/src/common/*.h
)

file(GLOB_RECURSE SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/publisher/*.cpp
    ${CMAKE_SOURCE_DIR}/src/subscriber/*.cpp
    ${CMAKE_SOURCE_DIR}/src/common/*.cpp
)

message(STATUS ${HEADER_FILES})
message(STATUS ${SOURCE_FILES})

add_executable(
    messaging_library
    main.cpp
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

target_include_directories(messaging_library
    PRIVATE
    include
)

target_link_libraries(messaging_library
    PRIVATE
)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})