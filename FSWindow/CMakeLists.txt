cmake_minimum_required(VERSION 3.30)

project(FSWindow)

file(GLOB SOURCES src/*.cpp)

add_library(FSWindow ${SOURCES})
target_include_directories(FSWindow PUBLIC include)

if(UNIX AND NOT APPLE)
target_link_libraries(FSWindow X11)
endif()