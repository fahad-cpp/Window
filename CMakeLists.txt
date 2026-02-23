cmake_minimum_required(VERSION 3.30)

project(Window)

file(GLOB SOURCES src/*.cpp)

add_executable(Window ${SOURCES})

if(UNIX AND NOT APPLE)
target_link_libraries(Window X11)
endif()