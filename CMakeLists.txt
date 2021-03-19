cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

# test
add_subdirectory(SandBox)

add_subdirectory(DemoPlugin)
#add_subdirectory(3rdParty/boostlog)
add_subdirectory(3rdParty/njson)


# 头文件路径
file(GLOB header_files
        "Include/*.h"
        "GameServer/*.h"
        "DemoPlugin/*.h"
        )

# 源文件路径
file(GLOB src_files
        "GameServer/*.cpp"
        "DemoPlugin/*.cpp"
        )

project(GServer)

include_directories(Include)

# 编译为可执行文件
add_executable(${PROJECT_NAME}

        ${src_files}
        ${header_files}

        )

# 链接动态库
target_link_libraries(${PROJECT_NAME}
        nlohmann_json::nlohmann_json
        pthread
        dl
        DemoPlugin
        )