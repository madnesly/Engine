cmake_minimum_required(VERSION 3.26)

project(Engine CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

add_executable(Engine main.cc)

add_subdirectory(strawx)

target_link_libraries(Engine PUBLIC strawx)
