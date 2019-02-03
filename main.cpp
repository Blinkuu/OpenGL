#include <iostream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>

#include "window.h"
#include "shader.h"
#include "texture.h"
#include "file_loader.h"

#include "buffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main() {

    Camera camera;

    Window window(800, 600, "Hello World", nullptr, nullptr, &camera);
    window.EnableDepthTesting();

    /** Vertex Data **/
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
    };

    unsigned int indexArray[] = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    IndexBuffer IBO(indexArray, 36);

    /** Cube **/
    VertexArray cubeVAO;
    std::vector<unsigned short int> cubePointerOffsets = {3, 3, 2};
    Buffer* cubeBuffer = new Buffer(vertices, sizeof(vertices)/sizeof(vertices[0]), 8, cubePointerOffsets);
    cubeVAO.AddBuffer(cubeBuffer);

    /** Light **/
    VertexArray lightVAO;
    std::vector<unsigned short int> lightPointerOffsets = {3};
    Buffer* lightBuffer = new Buffer(vertices, sizeof(vertices)/sizeof(vertices[0]), 8, lightPointerOffsets);
    lightVAO.AddBuffer(lightBuffer);

    /** Projection Matrix **/
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), window.GetAspectRatio(), 0.1f, 100.0f);

    /** Light Position and Color**/
    glm::vec3 sunDirection(-1.0f, -1.0f,-1.0f);
    glm::vec3 sunColor(1.0f, 1.0f, 1.0f);
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
    glm::vec3 flashlightColor(1.0f, 1.0f, 1.0f);

    /** Cube Texture **/
    Texture cubeDiffuseMap("src/textures/container2.jpg");
    Texture cubeSpecularMap("src/textures/container2_specular.jpg");

    /** Light Shader **/
    Shader lightShader("src/shaders/light.vert", "src/shaders/light.frag");
    lightShader.Bind();
    lightShader.SetMat4("projection", projection);
    lightShader.SetVec3("light.color", lightColor);

    /** Cube Shader **/
    Shader cubeShader("src/shaders/cube.vert", "src/shaders/cube.frag");
    cubeShader.Bind();
    cubeShader.SetMat4("projection", projection);

    /** Directional Light **/
    cubeShader.SetVec3("u_DirLight.direction", sunDirection);
    cubeShader.SetVec3("u_DirLight.ambient",  sunColor * glm::vec3(0.1f, 0.1f, 0.1f));
    cubeShader.SetVec3("u_DirLight.diffuse",  sunColor * glm::vec3(0.7f, 0.7f, 0.7f));
    cubeShader.SetVec3("u_DirLight.specular", sunColor * glm::vec3(1.0f, 1.0f, 1.0f));

    /** Point Lights **/
    #define NR_POINT_LIGHTS 3
    glm::vec3 pointLightPositions[NR_POINT_LIGHTS] = {
        glm::vec3(2.0f, 1.0f, 1.0f),
        glm::vec3(7.0f, 1.3f, 2.0f),
        glm::vec3(5.0f, 1.0f, 3.0f)
    };

    cubeShader.SetVec3("u_PointLights[0].position",  pointLightPositions[0]);
    cubeShader.SetVec3("u_PointLights[0].ambient",  lightColor * glm::vec3(0.1f, 0.1f, 0.1f));
    cubeShader.SetVec3("u_PointLights[0].diffuse",  lightColor * glm::vec3(0.7f, 0.7f, 0.7f));
    cubeShader.SetVec3("u_PointLights[0].specular", lightColor * glm::vec3(1.0f, 1.0f, 1.0f));
    cubeShader.SetFloat("u_PointLights[0].constant", 1.0f);
    cubeShader.SetFloat("u_PointLights[0].linear", 0.09f);
    cubeShader.SetFloat("u_PointLights[0].quadratic", 0.032f);

    cubeShader.SetVec3("u_PointLights[1].position",  pointLightPositions[1]);
    cubeShader.SetVec3("u_PointLights[1].ambient",  lightColor * glm::vec3(0.1f, 0.1f, 0.1f));
    cubeShader.SetVec3("u_PointLights[1].diffuse",  lightColor * glm::vec3(0.7f, 0.7f, 0.7f));
    cubeShader.SetVec3("u_PointLights[1].specular", lightColor * glm::vec3(1.0f, 1.0f, 1.0f));
    cubeShader.SetFloat("u_PointLights[1].constant", 1.0f);
    cubeShader.SetFloat("u_PointLights[1].linear", 0.09f);
    cubeShader.SetFloat("u_PointLights[1].quadratic", 0.032f);

    cubeShader.SetVec3("u_PointLights[2].position",  pointLightPositions[2]);
    cubeShader.SetVec3("u_PointLights[2].ambient",  lightColor * glm::vec3(0.1f, 0.1f, 0.1f));
    cubeShader.SetVec3("u_PointLights[2].diffuse",  lightColor * glm::vec3(0.7f, 0.7f, 0.7f));
    cubeShader.SetVec3("u_PointLights[2].specular", lightColor * glm::vec3(1.0f, 1.0f, 1.0f));
    cubeShader.SetFloat("u_PointLights[2].constant", 1.0f);
    cubeShader.SetFloat("u_PointLights[2].linear", 0.09f);
    cubeShader.SetFloat("u_PointLights[2].quadratic", 0.032f);

    /** Spotlight **/
    cubeShader.SetVec3("u_SpotLight.diffuse",  flashlightColor * glm::vec3(0.7f, 0.7f, 0.7f));
    cubeShader.SetVec3("u_SpotLight.specular", flashlightColor * glm::vec3(1.0f, 1.0f, 1.0f));
    cubeShader.SetFloat("u_SpotLight.cutOff", glm::cos(glm::radians(8.0f)));
    cubeShader.SetFloat("u_SpotLight.outerCutOff", glm::cos(glm::radians(12.0f)));
    cubeShader.SetFloat("u_SpotLight.constant", 1.0f);
    cubeShader.SetFloat("u_SpotLight.linear", 0.09f);
    cubeShader.SetFloat("u_SpotLight.quadratic", 0.0032f);

    /** Material **/
    cubeShader.SetInt("u_Material.diffuse",  0);
    cubeShader.SetInt("u_Material.specular",  1);
    cubeShader.SetFloat("u_Material.shininess", 32.0f);

    float lastFrame = 0.0f;
    while (!window.ShouldClose())
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        window.Clear();

        auto currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        window.ProcessInput(deltaTime);

        glm::mat4 view = camera.GetViewMatrix();

        /** Point Lights **/
        lightVAO.Bind();
        IBO.Bind();

        lightShader.Bind();
        lightShader.SetMat4("view", view);

        for (int i = 0; i < NR_POINT_LIGHTS; ++i) {
            glm::mat4 lightModel(1.0f);
            lightModel = glm::translate(lightModel, pointLightPositions[i]);
            lightModel = glm::scale(lightModel, glm::vec3(0.1f, 0.1f, 0.1f));
            lightShader.SetMat4("model", lightModel);

            glDrawElements(GL_TRIANGLES, IBO.GetCount(), GL_UNSIGNED_INT, nullptr);
        }

        /** Spotlight **/
        cubeShader.Bind();
        cubeShader.SetVec3("u_SpotLight.position", camera.GetPosition());
        cubeShader.SetVec3("u_SpotLight.direction", camera.GetFront());

        /** Cube **/
        cubeVAO.Bind();
        IBO.Bind();

        cubeDiffuseMap.Activate(0);
        cubeDiffuseMap.Bind();
        cubeSpecularMap.Activate(1);
        cubeSpecularMap.Bind();

        cubeShader.Bind();
        cubeShader.SetMat4("view", view);
        cubeShader.SetVec3("u_CameraPosition", camera.GetPosition());

        for(int i = 0; i < 16; ++i) {
            glm::mat4 cubeModel(1.0f);
            cubeModel = glm::translate(cubeModel, glm::vec3(2.0f + i, 0.0f, (2 + i) % 4));
            cubeModel = glm::scale(cubeModel, glm::vec3(0.5f, 0.5f, 0.5f));
            cubeShader.SetMat4("model", cubeModel);

            glDrawElements(GL_TRIANGLES, IBO.GetCount(), GL_UNSIGNED_INT, nullptr);
        }

        window.Update();
    }

    return 0;
}

