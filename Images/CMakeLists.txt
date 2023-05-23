cmake_minimum_required(VERSION 3.8)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Images "main.cpp" "Cards.h" "Cards.cpp")

target_link_libraries(Images PUBLIC ${OpenCV_LIBS})