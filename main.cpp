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
    /*float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };*/

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

    IndexBuffer IBO(indexArray, 24);

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
    glm::vec3 lightDirection(2.0f, 2.0f, 2.0f);
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
    glm::vec3 flashlightColor(1.0f, 1.0f, 1.0f);

    /** Cube Texture **/
    Texture cubeDiffuseMap("src/textures/container2.jpg");
    Texture cubeSpecularMap("src/textures/container2_specular.jpg");

    /** Cube Shader **/
    Shader cubeShader("src/shaders/cube.vert", "src/shaders/cube.frag");
    cubeShader.Bind();
    cubeShader.SetMat4("projection", projection);

    cubeShader.SetVec3("light.ambient",  lightColor * glm::vec3(0.1f, 0.1f, 0.1f));
    cubeShader.SetVec3("light.diffuse",  lightColor * glm::vec3(0.7f, 0.7f, 0.7f));
    cubeShader.SetVec3("light.specular", lightColor * glm::vec3(1.0f, 1.0f, 1.0f));
    cubeShader.SetFloat("light.constant", 1.0f);
    cubeShader.SetFloat("light.linear", 0.09f);
    cubeShader.SetFloat("light.quadratic", 0.032f);

    cubeShader.SetVec3("u_spotlight.diffuse", flashlightColor * glm::vec3(0.8f, 0.8f, 0.8f));
    cubeShader.SetFloat("u_spotlight.innerCutOff", glm::cos(glm::radians(5.0f)));
    cubeShader.SetFloat("u_spotlight.outerCutOff", glm::cos(glm::radians(7.0f)));
    cubeShader.SetFloat("u_spotlight.constant", 1.0f);
    cubeShader.SetFloat("u_spotlight.linear", 0.09f);
    cubeShader.SetFloat("u_spotlight.quadratic", 0.0072f);

    cubeShader.SetInt("material.diffuse",  0);
    cubeShader.SetInt("material.specular",  1);
    cubeShader.SetFloat("material.shininess", 32.0f);

    /** Light Shader **/
    Shader lightShader("src/shaders/light.vert", "src/shaders/light.frag");
    lightShader.Bind();
    lightShader.SetMat4("projection", projection);
    lightShader.SetVec3("light.color", lightColor);

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

        /** Light **/
        lightVAO.Bind();
        IBO.Bind();

        lightShader.Bind();
        lightShader.SetMat4("view", view);

        glm::mat4 lightModel(1.0f);
        lightModel = glm::translate(lightModel, lightDirection);
        lightModel = glm::scale(lightModel, glm::vec3(0.1f, 0.1f, 0.1f));
        lightShader.SetMat4("model", lightModel);

        glDrawElements(GL_TRIANGLES, IBO.GetCount(), GL_UNSIGNED_INT, nullptr);

        /** Cube **/
        cubeVAO.Bind();
        IBO.Bind();

        cubeDiffuseMap.Activate(0);
        cubeDiffuseMap.Bind();
        cubeSpecularMap.Activate(1);
        cubeSpecularMap.Bind();

        cubeShader.Bind();
        cubeShader.SetMat4("view", view);
        cubeShader.SetVec3("u_cameraPosition", camera.GetPosition());
        cubeShader.SetVec3("light.direction", lightDirection);
        cubeShader.SetVec3("u_spotlight.direction", camera.GetFront());

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

