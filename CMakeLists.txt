cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)
add_subdirectory(SandBox)

file(GLOB header_files
        "Include/*.h"
        "GameServer/*.h"
        "DemoPlugin/*.h"
        )

file(GLOB src_files
        "GameServer/*.cpp"
        "DemoPlugin/*.cpp"
        )

project(GServer)

include_directories(Include)

add_executable(${PROJECT_NAME}

        ${src_files}
        ${header_files}

        )

target_link_libraries(${PROJECT_NAME} pthread)