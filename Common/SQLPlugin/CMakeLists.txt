project(SQLPlugin)

include_directories(
        ${CMAKE_SOURCE_DIR}/Include
)

add_subdirectory(SQLitePlugin/sqlite)

file(GLOB src_files "${PROJECT_SOURCE_DIR}/Common/*.cpp" "${PROJECT_SOURCE_DIR}/SQLitePlugin/*.cpp")

add_library(${PROJECT_NAME} SHARED ${src_files})

add_library(plug::sql ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} sqlite3)

target_precompile_headers(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/Common/pch.h)
