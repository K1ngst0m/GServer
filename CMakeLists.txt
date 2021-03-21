cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(plug_incl
    "${CMAKE_SOURCE_DIR}/Include/"
    "${CMAKE_SOURCE_DIR}/Common/"
    "${CMAKE_SOURCE_DIR}/3rdParty/spdlog/include"
    )

set(plug_lklibs
    pthread
    dl
    logger
    nlohmann_json::nlohmann_json
    )

file(GLOB plug_dirs
    ${CMAKE_SOURCE_DIR}/*Plugin
    )

file(GLOB common_dirs
    ${CMAKE_SOURCE_DIR}/Common/*
    )


project(GServer)

# 子目录
add_subdirectory(GameServer)
add_subdirectory(${plug_dirs})
add_subdirectory(${common_dirs})
add_subdirectory(3rdParty/njson)

# 资源目录复制
file(COPY Resources DESTINATION ${CMAKE_BINARY_DIR})
