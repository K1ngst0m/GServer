project(SandBox)

add_subdirectory(DemoLib)

add_executable(${PROJECT_NAME} SandBox.cpp)
target_link_libraries(${PROJECT_NAME} demoLib)
