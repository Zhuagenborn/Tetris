add_library(rotation)

set(HEADER_PATH ${PROJECT_SOURCE_DIR}/include)

target_include_directories(rotation PUBLIC ${HEADER_PATH})

target_sources(rotation
    PUBLIC
        ${HEADER_PATH}/rotation.h
    PRIVATE
        rotation.cpp
)