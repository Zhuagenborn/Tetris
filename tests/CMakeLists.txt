add_executable(public-test)

target_sources(public-test
    PRIVATE
        rotation_test.cpp
        tetromino_test.cpp
        grid_test.cpp
)

target_link_libraries(public-test
    PRIVATE
        rotation
        tetromino
        grid
)

target_link_libraries(public-test
    PRIVATE
        ${GTEST_LIB}
        ${GMOCK_LIB}
)

gtest_discover_tests(public-test)