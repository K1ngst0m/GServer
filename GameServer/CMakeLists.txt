# 服务器程序入口
project(Server)

include_directories(${plug_incl})

file(GLOB src_files "${PROJECT_SOURCE_DIR}/*.cpp")
file(GLOB lnk_plugs "plug::*")

add_executable(${PROJECT_NAME} ${src_files})

target_link_libraries(${PROJECT_NAME} ${plug_lklibs} ${lnk_plugs})

target_precompile_headers(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/pch.h")
