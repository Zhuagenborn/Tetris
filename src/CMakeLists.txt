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