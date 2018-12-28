cmake_minimum_required(VERSION 3.12)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(
        -Wall -Wcast-align
        -Wnull-dereference
)

find_package(glfw3 3.2 REQUIRED)
find_package(glu REQUIRED)

include_directories(vendor/glad/include)
include_directories(src/graphics)
include_directories(src/utils)
include_directories(src)

add_executable(OpenGL
        main.cpp
        vendor/glad/src/glad.c
        src/graphics/window.cpp
        src/graphics/texture.cpp
        src/graphics/shader.cpp
        src/graphics/camera.cpp
        src/utils/file_loader.cpp
        src/utils/stb_image.h)

target_link_libraries(OpenGL glfw)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa -framework OpenGL -framework IOKit")

configure_file(src/shaders/shader.vert src/shaders/shader.vert COPYONLY)
configure_file(src/shaders/shader.frag src/shaders/shader.frag COPYONLY)
configure_file(src/textures/wall.jpg src/textures/wall.jpg COPYONLY)
configure_file(src/textures/container.jpg src/textures/container.jpg COPYONLY)
