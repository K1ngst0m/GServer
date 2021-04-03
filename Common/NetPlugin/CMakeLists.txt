# 插件名
project(NetPlugin)

include_directories(${PROJECT_SOURCE_DIR}/Include)

# 插件源文件目录
file(GLOB src_files "${PROJECT_SOURCE_DIR}/*.cpp")

# 生成动态库
add_library(${PROJECT_NAME} SHARED ${src_files})

# 设置别名
add_library(plug::net ALIAS ${PROJECT_NAME})

# 链接所需动态库 (在根目录的cmake文件定义)
target_link_libraries(${PROJECT_NAME} ${plug_lklibs})

# 预编译头
target_precompile_headers(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/pch.h")

