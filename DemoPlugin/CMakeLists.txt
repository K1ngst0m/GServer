set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

project(DemoPlugin)

include_directories(../Include)

add_library(
        ${PROJECT_NAME} SHARED
        "DemoModule.cpp"
        "DemoPlugin.cpp"

)