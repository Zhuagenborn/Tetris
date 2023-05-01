add_library(game)

set(HEADER_PATH ${PROJECT_SOURCE_DIR}/include)

target_include_directories(game PUBLIC ${HEADER_PATH})

target_sources(game
    PUBLIC
        ${HEADER_PATH}/game.h
    PRIVATE
        game.cpp
)

target_link_libraries(game
    PUBLIC
        grid
)