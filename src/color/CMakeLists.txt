add_library(color)

set(HEADER_PATH ${PROJECT_SOURCE_DIR}/include)

target_include_directories(color PUBLIC ${HEADER_PATH})

target_sources(color
    PUBLIC
        ${HEADER_PATH}/color.h
    PRIVATE
        color.cpp
)