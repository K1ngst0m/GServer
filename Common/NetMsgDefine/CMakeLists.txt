project(NetMsgDefine)

#include_directories("${CMAKE_SOURCE_DIR}/3rdParty/spdlog/include")
#include_directories(${Protobuf_INCLUDE_DIRS})

file(GLOB src_files "${PROJECT_SOURCE_DIR}/*.cc"
                    "${PROJECT_SOURCE_DIR}/*.cpp"
        )

add_library(${PROJECT_NAME} SHARED ${src_files})

target_link_libraries(${PROJECT_NAME} protoc)
