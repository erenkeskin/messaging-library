file(GLOB_RECURSE HEADER_FILES
    ${CMAKE_SOURCE_DIR}/src/common/*.h
    ${CMAKE_SOURCE_DIR}/src/publisher/*.h
    ${CMAKE_SOURCE_DIR}/src/subscriber/*.h
)

file(GLOB_RECURSE SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/common/*.cpp
    ${CMAKE_SOURCE_DIR}/src/publisher/*.cpp
    ${CMAKE_SOURCE_DIR}/src/subscriber/*.cpp
)

list(FILTER SOURCE_FILES EXCLUDE REGEX ".*main[.](cpp)$")

add_executable(
    messaging_library_test
    main.cpp
    test_pub_sub_api.cpp
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

target_include_directories(messaging_library_test
    PRIVATE
    include
)

target_link_libraries(
    messaging_library_test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(messaging_library_test)