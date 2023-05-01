add_library(location INTERFACE)

set(HEADER_PATH ${PROJECT_SOURCE_DIR}/include)

target_include_directories(location INTERFACE ${HEADER_PATH})

target_sources(location
    INTERFACE
        ${HEADER_PATH}/location.h
)