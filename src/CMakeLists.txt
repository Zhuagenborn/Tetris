add_executable(${CMAKE_PROJECT_NAME})

target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
        main.cpp
)

add_subdirectory(location)
add_subdirectory(color)
add_subdirectory(shape)
add_subdirectory(rotation)
add_subdirectory(tetromino)
add_subdirectory(grid)
add_subdirectory(game)
add_subdirectory(controller)
add_subdirectory(args)

target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
        game
        controller
        args
)