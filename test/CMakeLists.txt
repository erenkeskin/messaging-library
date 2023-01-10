add_executable(
    esen_test
    main.cpp
)

target_link_libraries(
    esen_test
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(esen_test)