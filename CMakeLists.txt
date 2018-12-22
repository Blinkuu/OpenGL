cmake_minimum_required(VERSION 3.12)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(
        -Wall -Wcast-align
        -Wnull-dereference
        -Wduplicated-cond
        -Wlogical-op
)

include_directories(vendor/glad/include)
include_directories(src/graphics)
include_directories(src/utils)

add_executable(
        OpenGL
        main.cpp
        vendor/glad/src/glad.c
        src/graphics/window.cpp
        src/utils/file_loader.cpp
        src/graphics/shader.cpp
        src/utils/stb_image.h)

target_link_libraries(OpenGL glfw3 GL X11 Xi Xrandr Xxf86vm Xinerama Xcursor rt m pthread dl)

configure_file(src/shaders/shader.vert src/shaders/shader.vert COPYONLY)
configure_file(src/shaders/shader.frag src/shaders/shader.frag COPYONLY)
configure_file(src/textures/wall.jpg src/textures/wall.jpg COPYONLY)
configure_file(src/textures/container.jpg src/textures/container.jpg COPYONLY)
