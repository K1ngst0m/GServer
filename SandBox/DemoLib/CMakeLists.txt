project(demoLib)

add_library(${PROJECT_NAME} test.cpp test.h)
target_link_libraries(${PROJECT_NAME} pthread)
