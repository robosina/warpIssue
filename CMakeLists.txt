cmake_minimum_required(VERSION 3.14)

project(stitcherExample LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

include_directories(${PROJECT_NAME} PRIVATE
    ${OPENCV_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
  main.cpp
)
target_link_libraries(${PROJECT_NAME}  PRIVATE ${OpenCV_LIBS})

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/4.jpg
                ${CMAKE_CURRENT_BINARY_DIR}/4.jpg)

