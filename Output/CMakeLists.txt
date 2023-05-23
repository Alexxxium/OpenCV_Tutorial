cmake_minimum_required(VERSION 3.8)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Output "main.cpp")

target_link_libraries(Output PUBLIC ${OpenCV_LIBS})