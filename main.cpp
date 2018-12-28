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

    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int VAO;
    unsigned int VBO;
    //unsigned int EBO;

    glGenVertexArrays(1, &VAO);

        glGenBuffers(1, &VBO);
       // glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), reinterpret_cast<const void*>(vertices), GL_STATIC_DRAW);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), reinterpret_cast<const void*>(indices), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), reinterpret_cast<void*>(0));
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

/*        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), reinterpret_cast<void*>(6*sizeof(float)));
        glEnableVertexAttribArray(2);*/

    glBindVertexArray(0);

    // DO NOT UNBIND THEM BEFORE UNBINDING Vertex Array Object, because VAO stores the last bound buffer - even if it means storing no bound object!!!
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    Shader shader("src/shaders/shader.vert", "src/shaders/shader.frag");

    Texture texture1("src/textures/container.jpg");
    Texture texture2("src/textures/wall.jpg");

    shader.Use();
    shader.SetInt("texture1", 0);
    shader.SetInt("texture2", 1);

    glm::vec3 cubeTranslations[] = {
            glm::vec3(1.0f, 1.0f, -0.5f),
            glm::vec3(-2.0f, -2.5f, -3.0f),
            glm::vec3(-1.0f, 2.0f, -5.0f),
            glm::vec3(-4.0f, 2.5f, -10.0f),
            glm::vec3(4.0f, -2.0f, -4.0f)
    };

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!window.ShouldClose())
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        window.ProcessInput(deltaTime);
        glClearColor(0.3f, 0.2f, 0.0f, 1.0f);
        window.Clear();

        texture1.Activate(0);
        texture1.Bind();
        texture2.Activate(1);
        texture2.Bind();

        glBindVertexArray(VAO);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

        glm::mat4 view = camera.GetViewMatrix();

        glm::mat4 projection(1.0f);
        projection = glm::perspective(glm::radians(45.0f), window.GetAspectRatio(), 0.1f, 100.0f);

        shader.SetMat4("view", view);
        shader.SetMat4("projection", projection);

        for(int i = 0; i < 5; i++) {
            glm::mat4 model(1.0f);
            model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
            model = glm::translate(model, cubeTranslations[i]);
            if(i%2 == 0)
                model = glm::rotate(model,  currentFrame * glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));

            shader.SetMat4("model", model);

            //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        window.Update();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    //glDeleteBuffers(1, &EBO);

    window.Terminate();

    return 0;
}

