
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_library(strawx STATIC 
    engine.cc 
    engine.h
    input.cc
    input.h
    texture.cc
    texture.h
)

target_compile_features(strawx PUBLIC cxx_std_17)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux" OR "Darwin")
    target_compile_options(strawx PUBLIC -Wall)
else()
    target_compile_options(strawx PUBLIC /W4)
    set_target_properties(strawx PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")
endif()

target_link_libraries(strawx ${SDL2_LIBRARIES} SDL2_image::SDL2_image)
