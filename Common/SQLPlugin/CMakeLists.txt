project(SQLPlugin)

include_directories(${plug_incl})

file(GLOB src_files
        "${PROJECT_SOURCE_DIR}/Common/*.cpp"
        "${PROJECT_SOURCE_DIR}/SQLitePlugin/*.cpp"
        )

add_library(${PROJECT_NAME} SHARED ${src_files})

add_library(plug::sql ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME})
