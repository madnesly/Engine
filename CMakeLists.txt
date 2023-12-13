
find_package(SDL2 REQUIRED)

add_library(strawx STATIC 
    engine.cc 
    engine.h
    input.cc
    input.h
)

target_compile_features(strawx PUBLIC cxx_std_17)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux" OR "Darwin")
    target_compile_options(strawx PUBLIC -Wall)
else()
    target_compile_options(strawx PUBLIC /W4)
endif()

target_link_libraries(strawx ${SDL2_LIBRARIES})
