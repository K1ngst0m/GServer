project(sqlite3)

file(GLOB src_files "${PROJECT_SOURCE_DIR}/*.c")

add_library(${PROJECT_NAME} ${src_files})

target_link_libraries(${PROJECT_NAME})