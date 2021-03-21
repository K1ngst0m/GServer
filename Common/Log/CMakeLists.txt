project(logger)

include_directories("${CMAKE_SOURCE_DIR}/3rdParty/spdlog/include")

file(GLOB src_files "${PROJECT_SOURCE_DIR}/*.cpp")

add_library(
    ${PROJECT_NAME} SHARED
    ${src_files}
)
