project(NetMsgDefine)

file(GLOB src_files "${PROJECT_SOURCE_DIR}/*.cc")

add_library(${PROJECT_NAME} SHARED ${src_files})

target_link_libraries(${PROJECT_NAME} protobuf pthread)
