add_library(tetromino)

set(HEADER_PATH ${PROJECT_SOURCE_DIR}/include)

target_include_directories(tetromino PUBLIC ${HEADER_PATH})

target_sources(tetromino
    PUBLIC
        ${HEADER_PATH}/tetromino.h
    PRIVATE
        subtype/o.h
        subtype/i.h
        subtype/t.h
        subtype/j.h
        subtype/l.h
        subtype/s.h
        subtype/z.h
        tetromino.cpp
)

target_link_libraries(tetromino
    PUBLIC
        shape
        color
        rotation
        location
)