add_executable(public-test)

target_sources(public-test
    PRIVATE
        rotation_test.cpp
        tetromino_test.cpp
)

target_link_libraries(public-test
    PRIVATE
        rotation
        tetromino
)

target_link_libraries(public-test
    PRIVATE
        ${GTEST_LIBS}
        ${GMOCK_LIBS}
)

gtest_discover_tests(public-test)