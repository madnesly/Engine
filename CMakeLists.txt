cmake_minimum_required(VERSION 3.26)

find_package(SDL2 REQUIRED)

add_library(strawx STATIC 
    engine.cc 
    engine.h
    input.cc
    input.h
)

target_compile_features(strawx PUBLIC cxx_std_17)

target_link_libraries(strawx ${SDL2_LIBRARIES})
