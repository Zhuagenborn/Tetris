add_library(shape INTERFACE)

set(HEADER_PATH ${PROJECT_SOURCE_DIR}/include)

target_include_directories(shape INTERFACE ${HEADER_PATH})

target_sources(shape
    INTERFACE
        ${HEADER_PATH}/shape.h
)

target_link_libraries(shape
    INTERFACE
        location
)