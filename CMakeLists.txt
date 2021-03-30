cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_definitions(-DLOG_LEVEL=0)

project(GServer)

include_directories(${CMAKE_SOURCE_DIR}/Include)

# 二级插件包含目录
set(plug_incl "${CMAKE_SOURCE_DIR}/Common/")

# 插件通用链接库
set(plug_lklibs pthread dl Logger nlohmann_json::nlohmann_json)

# 所有插件目录
file(GLOB plug_dirs ${CMAKE_SOURCE_DIR}/Plugins/*)

# Common目录的子目录
file(GLOB common_dirs ${CMAKE_SOURCE_DIR}/Common/*)


# 添加子目录
add_subdirectory(GameServer)            # 服务器核心

#add_subdirectory(${plug_dirs})         # 插件
add_subdirectory(Plugins/DemoPlugin)
#add_subdirectory(Plugins/UserPlugin)

#add_subdirectory(${common_dirs})
add_subdirectory(Common/Log)            # 日志
add_subdirectory(Common/NetPlugin)            # 网络
add_subdirectory(Common/NetMsgDefine)   # 网络包定义
add_subdirectory(Common/SQLPlugin)   # 数据库

# 添加第三方库子目录
add_subdirectory(3rdParty/njson)    # json库

# 将Resources复制到运行目录
file(COPY Resources DESTINATION ${CMAKE_BINARY_DIR})
