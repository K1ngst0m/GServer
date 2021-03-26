# 插件名
project(DemoPlugin)

# 包含头文件目录 (在根目录的cmake文件定义)
include_directories(${plug_incl})

# 插件源文件目录
file(GLOB src_files "${PROJECT_SOURCE_DIR}/*.cpp")

# 生成动态库
add_library(${PROJECT_NAME} SHARED ${src_files})

# 设置别名
add_library(plug::demo ALIAS ${PROJECT_NAME})

# 链接所需动态库 (在根目录的cmake文件定义)
target_link_libraries(${PROJECT_NAME} ${plug_lklibs})
