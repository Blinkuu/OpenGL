cmake_minimum_required(VERSION 3.12)
project(OpenGL)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(
        -Wall -Wcast-align
        -Wnull-dereference
        -g
)

find_package(glfw3 3.2 REQUIRED)

include_directories(vendor/glad/include)
include_directories(src)
include_directories(src/utils)
include_directories(src/graphics)
include_directories(src/graphics/buffers)
include_directories(src/graphics/models)

add_executable(OpenGL
        main.cpp
        vendor/glad/src/glad.c
        src/graphics/window.cpp
        src/graphics/texture.cpp
        src/graphics/shader.cpp
        src/graphics/camera.cpp
        src/utils/file_loader.cpp
        src/utils/timer.cpp
        src/graphics/buffers/buffer.cpp
        src/graphics/buffers/indexbuffer.cpp
        src/graphics/buffers/vertexarray.cpp
        src/graphics/models/mesh.cpp
        src/graphics/models/model.cpp)

target_link_libraries(OpenGL glfw assimp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_custom_command(TARGET OpenGL
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:OpenGL>/assets)

configure_file(src/shaders/cube.vert src/shaders/cube.vert COPYONLY)
configure_file(src/shaders/cube.frag src/shaders/cube.frag COPYONLY)
configure_file(src/shaders/light.vert src/shaders/light.vert COPYONLY)
configure_file(src/shaders/light.frag src/shaders/light.frag COPYONLY)
configure_file(src/shaders/model.vert src/shaders/model.vert COPYONLY)
configure_file(src/shaders/model.frag src/shaders/model.frag COPYONLY)
configure_file(src/shaders/model_pro.vert src/shaders/model_pro.vert COPYONLY)
configure_file(src/shaders/model_pro.frag src/shaders/model_pro.frag COPYONLY)

configure_file(src/textures/wall.jpg src/textures/wall.jpg COPYONLY)
configure_file(src/textures/container.jpg src/textures/container.jpg COPYONLY)
configure_file(src/textures/container2.jpg src/textures/container2.jpg COPYONLY)
configure_file(src/textures/container2_specular.jpg src/textures/container2_specular.jpg COPYONLY)
configure_file(src/textures/matrix.jpg src/textures/matrix.jpg COPYONLY)
configure_file(src/textures/dirt.jpg src/textures/dirt.jpg COPYONLY)
