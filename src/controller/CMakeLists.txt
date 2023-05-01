add_library(controller)

set(HEADER_PATH ${PROJECT_SOURCE_DIR}/include)

target_include_directories(controller PUBLIC ${HEADER_PATH})

target_sources(controller
    PUBLIC
        ${HEADER_PATH}/controller.h
    PRIVATE
        ui/color_env.h
        ui/color_env.cpp
        ui/board.h
        ui/score_board.h
        ui/grid_board.h
        ui/next_tetromino_board.h
        controller.cpp
)

target_link_libraries(controller
    PUBLIC
        game
    PRIVATE
        location
        grid
        tetromino
        color
)

find_package(Curses REQUIRED)
target_include_directories(controller PRIVATE ${CURSES_INCLUDE_DIR})
target_link_libraries(controller PRIVATE ${CURSES_LIBRARY})