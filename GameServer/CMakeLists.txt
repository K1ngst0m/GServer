project(Server)

include_directories(${plug_incl})

file(GLOB src_files "${PROJECT_SOURCE_DIR}/*.cpp")

add_executable(
    ${PROJECT_NAME}
        ${src_files}
)

target_link_libraries(${PROJECT_NAME}
    ${plug_lklibs})

target_precompile_headers(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/pch.h")
