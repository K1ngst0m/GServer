project(Logger)

include_directories(spdlog)

file(GLOB src_files "${PROJECT_SOURCE_DIR}/*.cpp")

add_library(${PROJECT_NAME} SHARED ${src_files})
target_link_libraries(${PROJECT_NAME})
