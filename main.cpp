#include <iostream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>

#include "window.h"
#include "shader.h"
#include "texture.h"
#include "file_loader.h"

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
    };


    /** Cube **/
    unsigned int cubeVAO;
    unsigned int cubeVBO;

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);

    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), reinterpret_cast<const void*>(vertices), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), reinterpret_cast<void*>(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), reinterpret_cast<void*>(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /** Light **/
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);

    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), reinterpret_cast<const void*>(vertices), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

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
        auto currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        /** Sun **/
/*      lightDirection.x = glm::cos(0.5f*currentFrame);
        lightDirection.z = glm::sin(0.5f*currentFrame);*/

        window.ProcessInput(deltaTime);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        window.Clear();

        glm::mat4 view = camera.GetViewMatrix();

        /** Light **/
        glBindVertexArray(lightVAO);
        lightShader.Bind();
        lightShader.SetMat4("view", view);

        glm::mat4 lightModel(1.0f);
        lightModel = glm::translate(lightModel, lightDirection);
        lightModel = glm::scale(lightModel, glm::vec3(0.1f, 0.1f, 0.1f));
        lightShader.SetMat4("model", lightModel);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);

        /** Cube **/
        cubeDiffuseMap.Activate(0);
        cubeDiffuseMap.Bind();
        cubeSpecularMap.Activate(1);
        cubeSpecularMap.Bind();

        glBindVertexArray(cubeVAO);
        cubeShader.Bind();
        cubeShader.SetMat4("view", view);

        for(int i = 0; i < 16; ++i) {
            glm::mat4 cubeModel(1.0f);
            cubeModel = glm::translate(cubeModel, glm::vec3(2.0f + i, 0.0f, (2 + i) % 4));
            cubeModel = glm::scale(cubeModel, glm::vec3(0.5f, 0.5f, 0.5f));
            cubeShader.SetMat4("model", cubeModel);

            cubeShader.SetVec3("u_cameraPosition", camera.GetPosition());
            cubeShader.SetVec3("light.direction", lightDirection);
            cubeShader.SetVec3("u_spotlight.direction", camera.GetFront());

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glBindVertexArray(0);

        window.Update();
    }

    glDeleteBuffers(1, &cubeVBO);
    glDeleteVertexArrays(1, &cubeVAO);

    return 0;
}

