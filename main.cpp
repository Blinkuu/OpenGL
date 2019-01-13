#include <iostream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>

#include "window.h"
#include "shader.h"
#include "texture.h"
#include "file_loader.h"
#include "event.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main() {

    Camera camera;

    Window window(800, 600, "Hello World", nullptr, nullptr, &camera);
    window.EnableDepthTesting();

    /** Vertex Data **/
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };


    /** Cube **/
    unsigned int cubeVAO;
    unsigned int cubeVBO;

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);

    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), reinterpret_cast<const void*>(vertices), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), reinterpret_cast<void*>(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /** Light **/
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);

    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), reinterpret_cast<const void*>(vertices), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /** Projection Matrix **/
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), window.GetAspectRatio(), 0.1f, 100.0f);

    /** Light Position **/
    glm::vec3 lightPosition = glm::vec3(2.0f, 3.0f, 2.0f);

    /** Cube Shader **/
    Shader cubeShader("src/shaders/cube.vert", "src/shaders/cube.frag");
    cubeShader.Bind();
    cubeShader.SetMat4("projection", projection);

    glm::vec3 objectColor = glm::vec3(0.7f, 0.4f, 0.2f);
    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    cubeShader.SetVec3("light.ambient",  glm::vec3(1.0f, 1.0f, 1.0f));
    cubeShader.SetVec3("light.diffuse",  glm::vec3(0.5f, 0.5f, 0.5f));
    cubeShader.SetVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

    cubeShader.SetVec3("material.ambient",  glm::vec3(0.0215f, 0.1745f, 0.0215f));
    cubeShader.SetVec3("material.diffuse",  glm::vec3(0.07568f, 0.61424f, 0.07568f));
    cubeShader.SetVec3("material.specular", glm::vec3(0.633f, 0.727811f, 0.633f));
    cubeShader.SetFloat("material.shininess", 32.0f);

    /** Light Shader **/
    Shader lightShader("src/shaders/light.vert", "src/shaders/light.frag");
    lightShader.Bind();
    lightShader.SetMat4("projection", projection);
    lightShader.SetVec3("light.color", glm::vec3(1.0f, 1.0f, 1.0f));

    float lastFrame = 0.0f;

    while (!window.ShouldClose())
    {
        auto currentFrame = static_cast<float>(glfwGetTime());
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        window.ProcessInput(deltaTime);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        window.Clear();

        glm::mat4 view = camera.GetViewMatrix();

        /** Light **/
        glBindVertexArray(lightVAO);
        lightShader.Bind();
        lightShader.SetMat4("view", view);

        glm::mat4 lightModel(1.0f);
        lightModel = glm::translate(lightModel, lightPosition);
        lightModel = glm::scale(lightModel, glm::vec3(0.1f, 0.1f, 0.1f));
        lightShader.SetMat4("model", lightModel);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);

        /** Cube **/
        glBindVertexArray(cubeVAO);
        cubeShader.Bind();
        cubeShader.SetMat4("view", view);

        glm::mat4 cubeModel(1.0f);
        cubeModel = glm::translate(cubeModel, glm::vec3(0.0f, 0.0f, 0.0f));
        cubeModel = glm::scale(cubeModel, glm::vec3(0.5f, 0.5f, 0.5f));
        cubeShader.SetMat4("model", cubeModel);

        cubeShader.SetVec3("u_cameraPosition", camera.GetPosition());
        cubeShader.SetVec3("light.position", lightPosition);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(0);


        window.Update();
    }

    glDeleteBuffers(1, &cubeVBO);
    glDeleteVertexArrays(1, &cubeVAO);

    window.Terminate();

    return 0;
}

