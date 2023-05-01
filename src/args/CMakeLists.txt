add_library(args)

set(HEADER_PATH ${PROJECT_SOURCE_DIR}/include)

target_include_directories(args PUBLIC ${HEADER_PATH})

target_sources(args
    PUBLIC
        ${HEADER_PATH}/args.h
    PRIVATE
        args.cpp
)

include(FetchContent)

FetchContent_Declare(argh
    GIT_REPOSITORY https://github.com/adishavit/argh
    GIT_TAG        v1.3.2
)

FetchContent_MakeAvailable(argh)
target_include_directories(args PRIVATE ${argh_SOURCE_DIR})
target_link_libraries(args PRIVATE argh)