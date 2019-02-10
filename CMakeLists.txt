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
        src/utils/stb_image.h
        src/graphics/buffers/buffer.cpp
        src/graphics/buffers/indexbuffer.cpp
        src/graphics/buffers/vertexarray.cpp
        src/graphics/models/mesh.cpp
        src/graphics/models/model.cpp)

target_link_libraries(OpenGL glfw assimp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

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

configure_file(assets/models/nano_suit/arm_dif.png              assets/models/nano_suit/arm_dif.png COPYONLY)
configure_file(assets/models/nano_suit/arm_showroom_ddn.png     assets/models/nano_suit/arm_showroom_ddn.png COPYONLY)
configure_file(assets/models/nano_suit/arm_showroom_spec.png    assets/models/nano_suit/arm_showroom_spec.png COPYONLY)
configure_file(assets/models/nano_suit/body_dif.png             assets/models/nano_suit/body_dif.png COPYONLY)
configure_file(assets/models/nano_suit/body_showroom_ddn.png    assets/models/nano_suit/arm_dif.png COPYONLY)
configure_file(assets/models/nano_suit/body_showroom_spec.png   assets/models/nano_suit/body_showroom_spec.png COPYONLY)
configure_file(assets/models/nano_suit/glass_ddn.png            assets/models/nano_suit/glass_ddn.png COPYONLY)
configure_file(assets/models/nano_suit/glass_dif.png            assets/models/nano_suit/glass_dif.png  COPYONLY)
configure_file(assets/models/nano_suit/hand_dif.png             assets/models/nano_suit/hand_dif.png COPYONLY)
configure_file(assets/models/nano_suit/hand_showroom_ddn.png    assets/models/nano_suit/hand_showroom_ddn.png COPYONLY)
configure_file(assets/models/nano_suit/hand_showroom_spec.png   assets/models/nano_suit/hand_showroom_spec.png COPYONLY)
configure_file(assets/models/nano_suit/helmet_diff.png          assets/models/nano_suit/helmet_diff.png COPYONLY)
configure_file(assets/models/nano_suit/helmet_showroom_ddn.png  assets/models/nano_suit/helmet_showroom_ddn.png COPYONLY)
configure_file(assets/models/nano_suit/helmet_showroom_spec.png assets/models/nano_suit/helmet_showroom_spec.png COPYONLY)
configure_file(assets/models/nano_suit/leg_dif.png              assets/models/nano_suit/leg_dif.png COPYONLY)
configure_file(assets/models/nano_suit/leg_showroom_ddn.png     assets/models/nano_suit/leg_showroom_ddn.png COPYONLY)
configure_file(assets/models/nano_suit/leg_showroom_spec.png    assets/models/nano_suit/leg_showroom_spec.png COPYONLY)
configure_file(assets/models/nano_suit/nanosuit.blend           assets/models/nano_suit/nanosuit.blend COPYONLY)
configure_file(assets/models/nano_suit/nanosuit.mtl             assets/models/nano_suit/nanosuit.mtl COPYONLY)
configure_file(assets/models/nano_suit/nanosuit.obj             assets/models/nano_suit/nanosuit.obj COPYONLY)

configure_file(assets/models/light_suit/LightSuitEtc.png        assets/models/light_suit/LightSuitEtc.png COPYONLY)
configure_file(assets/models/light_suit/LightSuitEtcSpec.png    assets/models/light_suit/LightSuitEtcSpec.png COPYONLY)
configure_file(assets/models/light_suit/LightSuitMain.png       assets/models/light_suit/LightSuitMain.png COPYONLY)
configure_file(assets/models/light_suit/LightSuitEtcSpec.png    assets/models/light_suit/LightSuitEtcSpec.png COPYONLY)
configure_file(assets/models/light_suit/Ref.png                 assets/models/light_suit/Ref.png COPYONLY)
configure_file(assets/models/light_suit/Ref2.png                assets/models/light_suit/Ref2.png COPYONLY)
configure_file(assets/models/light_suit/Ref3.png                assets/models/light_suit/Ref3.png COPYONLY)
configure_file(assets/models/light_suit/posed.obj               assets/models/light_suit/posed.obj COPYONLY)
configure_file(assets/models/light_suit/posed.mtl               assets/models/light_suit/posed.mtl COPYONLY)