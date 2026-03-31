set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}-x64)
cmake_minimum_required(VERSION 3.30)

project(Window)

file(GLOB SOURCES src/*.cpp)

add_executable(Window ${SOURCES})

if(UNIX AND NOT APPLE)
target_link_libraries(Window X11)
endif()