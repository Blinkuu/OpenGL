#include <iostream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>

#include "window.h"
#include "shader.h"
#include "texture.h"
#include "file_loader.h"
#include "timer.h"

#include "buffer.h"
#include "indexbuffer.h"
#include "vertexarray.h"

#include "graphics/models/model.h"

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

    /** Projection Matrix **/
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), window.GetAspectRatio(), 0.1f, 100.0f);

    IndexBuffer IBO(indexArray, 36);

    /** Light **/
    VertexArray lightVAO;
    std::vector<unsigned short int> lightPointerOffsets = {3};
    Buffer lightBuffer(vertices, sizeof(vertices)/sizeof(vertices[0]), 8, lightPointerOffsets);
    lightVAO.AddBuffer(lightBuffer);

    /** Light Position and Color**/
    glm::vec3 sunDirection(-1.0f, -1.0f,-1.0f);
    glm::vec3 sunColor(1.0f, 1.0f, 1.0f);
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
    glm::vec3 flashlightColor(1.0f, 1.0f, 1.0f);

    /** Light Shader **/
    Shader lightShader("src/shaders/light.vert", "src/shaders/light.frag");
    lightShader.Bind();
    lightShader.SetMat4("projection", projection);
    lightShader.SetVec3("light.color", lightColor);

#define NR_POINT_LIGHTS 3
    glm::vec3 pointLightPositions[NR_POINT_LIGHTS] = {
        glm::vec3(2.0f, 2.0f, -1.0f),
        glm::vec3(2.0f, 2.0f,  1.0f),
        glm::vec3(-2.0f, 2.0f, 1.0f)
    };

    glm::vec3 pointLightColors[NR_POINT_LIGHTS] = {
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.2f, 0.2f, 1.0f),
        glm::vec3(1.0f, 0.6f, 0.6f),
    };

    /** Models **/
    Model firstModel("assets/models/nano_suit/nanosuit.obj");
    Model secondModel("assets/models/skull/Skull.obj");

    /** First Model Shader **/
    Shader firstShader("src/shaders/model_pro.vert", "src/shaders/model_pro.frag");

    firstShader.Bind();
    firstShader.SetMat4("u_Projection", projection);

    firstShader.SetVec3("u_DirLight.direction", sunDirection);
    firstShader.SetVec3("u_DirLight.ambient",  sunColor * glm::vec3(0.1f, 0.1f, 0.1f));
    firstShader.SetVec3("u_DirLight.diffuse",  sunColor * glm::vec3(0.7f, 0.7f, 0.7f));
    firstShader.SetVec3("u_DirLight.specular", sunColor * glm::vec3(1.0f, 1.0f, 1.0f));

    firstShader.SetVec3("u_SpotLight.diffuse",  flashlightColor * glm::vec3(0.7f, 0.7f, 0.7f));
    firstShader.SetVec3("u_SpotLight.specular", flashlightColor * glm::vec3(1.0f, 1.0f, 1.0f));
    firstShader.SetFloat("u_SpotLight.cutOff", glm::cos(glm::radians(8.0f)));
    firstShader.SetFloat("u_SpotLight.outerCutOff", glm::cos(glm::radians(12.0f)));
    firstShader.SetFloat("u_SpotLight.constant", 1.0f);
    firstShader.SetFloat("u_SpotLight.linear", 0.09f);
    firstShader.SetFloat("u_SpotLight.quadratic", 0.0032f);

    firstShader.SetVec3("u_PointLights[0].position", pointLightPositions[0]);
    firstShader.SetVec3("u_PointLights[0].ambient",  pointLightColors[0] * glm::vec3(0.1f, 0.1f, 0.1f));
    firstShader.SetVec3("u_PointLights[0].diffuse",  pointLightColors[0] * glm::vec3(0.7f, 0.7f, 0.7f));
    firstShader.SetVec3("u_PointLights[0].specular", pointLightColors[0] * glm::vec3(1.0f, 1.0f, 1.0f));
    firstShader.SetFloat("u_PointLights[0].constant", 1.0f);
    firstShader.SetFloat("u_PointLights[0].linear", 0.09f);
    firstShader.SetFloat("u_PointLights[0].quadratic", 0.032f);

    firstShader.SetVec3("u_PointLights[1].position", pointLightPositions[1]);
    firstShader.SetVec3("u_PointLights[1].ambient",  pointLightColors[1] * glm::vec3(0.1f, 0.1f, 0.1f));
    firstShader.SetVec3("u_PointLights[1].diffuse",  pointLightColors[1] * glm::vec3(0.7f, 0.7f, 0.7f));
    firstShader.SetVec3("u_PointLights[1].specular", pointLightColors[1] * glm::vec3(1.0f, 1.0f, 1.0f));
    firstShader.SetFloat("u_PointLights[1].constant", 1.0f);
    firstShader.SetFloat("u_PointLights[1].linear", 0.09f);
    firstShader.SetFloat("u_PointLights[1].quadratic", 0.032f);

    firstShader.SetVec3("u_PointLights[2].position", pointLightPositions[2]);
    firstShader.SetVec3("u_PointLights[2].ambient",  pointLightColors[2] * glm::vec3(0.1f, 0.1f, 0.1f));
    firstShader.SetVec3("u_PointLights[2].diffuse",  pointLightColors[2] * glm::vec3(0.7f, 0.7f, 0.7f));
    firstShader.SetVec3("u_PointLights[2].specular", pointLightColors[2] * glm::vec3(1.0f, 1.0f, 1.0f));
    firstShader.SetFloat("u_PointLights[2].constant", 1.0f);
    firstShader.SetFloat("u_PointLights[2].linear", 0.09f);
    firstShader.SetFloat("u_PointLights[2].quadratic", 0.032f);

    firstShader.SetFloat("u_Material.shininess", 32.0f);

    /** First Model Shader **/
    Shader secondShader("src/shaders/model.vert", "src/shaders/model.frag");
    secondShader.Bind();
    secondShader.SetMat4("u_Projection", projection);

    Timer timer;
    while (!window.ShouldClose())
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        window.Clear();

        timer.CalculateFramerate();
        window.ProcessInput(timer.GetDeltaTime());

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
            lightShader.SetVec3("light.color", pointLightColors[i]);

            glDrawElements(GL_TRIANGLES, IBO.GetCount(), GL_UNSIGNED_INT, nullptr);
        }

        /** First Model **/
        glm::mat4 firstModelMatrix(1.0f);
        firstModelMatrix = glm::scale(firstModelMatrix, glm::vec3(0.1f, 0.1f, 0.1f));
        firstModelMatrix = glm::translate(firstModelMatrix, glm::vec3(-10.0f, -2.5f, 0.0f));
        firstShader.Bind();

        firstShader.SetMat4("u_View", view);
        firstShader.SetMat4("u_Model", firstModelMatrix);

        firstShader.SetVec3("u_CameraPosition", camera.GetPosition());

        firstShader.SetVec3("u_SpotLight.position", camera.GetPosition());
        firstShader.SetVec3("u_SpotLight.direction", camera.GetFront());
        firstShader.SetBool("u_FlashlightStatus", camera.GetFlashLightStatus());

        firstModel.Draw(firstShader);

        /** First Model **/
        glm::mat4 secondModelMatrix(1.0f);
        secondModelMatrix = glm::scale(secondModelMatrix, glm::vec3(0.025f, 0.025f, 0.025f));
        secondModelMatrix = glm::translate(secondModelMatrix, glm::vec3(0.0f, 5.0f, 10.0f));
        secondModelMatrix = glm::rotate(secondModelMatrix, glm::radians(-90.0f),glm::vec3(1.0f, 0.0f, 0.0f));
        firstShader.Bind();

        firstShader.SetMat4("u_View", view);
        firstShader.SetMat4("u_Model", secondModelMatrix);

        secondModel.Draw(firstShader);

        window.Update();
    }

    return 0;
}