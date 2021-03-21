project(DemoPlugin)

include_directories(${plug_incl})

file(GLOB src_files "${PROJECT_SOURCE_DIR}/*.cpp")

add_library(
    ${PROJECT_NAME} SHARED
        ${src_files}
)

add_library(plug::demo ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} ${plug_lklibs})
