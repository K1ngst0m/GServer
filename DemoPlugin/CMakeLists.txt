set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(DemoPlugin)

include_directories(../Include)

add_library(
        ${PROJECT_NAME} SHARED
        "DemoModule.cpp"
        "DemoPlugin.cpp"

)