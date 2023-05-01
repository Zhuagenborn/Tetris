add_library(grid)

set(HEADER_PATH ${PROJECT_SOURCE_DIR}/include)

target_include_directories(grid PUBLIC ${HEADER_PATH})

target_sources(grid
    PUBLIC
        ${HEADER_PATH}/grid.h
    PRIVATE
        grid.cpp
)

target_link_libraries(grid
    PUBLIC
        tetromino
)