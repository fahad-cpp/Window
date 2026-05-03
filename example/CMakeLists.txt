cmake_minimum_required(VERSION 3.10)

project(MyProj)

add_subdirectory(../FSWindow bin)

add_executable(MyProj Game.cpp Application.cpp)

target_link_libraries(MyProj FSWindow)