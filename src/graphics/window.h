//
// Created by blinku on 17.12.18.
//

#pragma once

#include <glm/glm.hpp>

#include "camera.h"

class GLFWmonitor;
class GLFWwindow;

class Window {
public:
    Window(int width, int height, const char* windowName, GLFWmonitor *monitor, GLFWwindow *window, Camera* camera);
    ~Window() = default;

    void Clear();
    void Update();
    int ShouldClose();
    void Terminate();

    void ProcessInput(float deltaTime);
    void EnableDepthTesting();
    void DisableDepthTesting();
    float GetAspectRatio() const;
private:
    int m_Width;
    int m_Height;
    const char* m_WindowName;
    GLFWwindow* m_Window;
    bool m_DepthTest;
    Camera* m_Camera;
private:
    void Init(GLFWmonitor *monitor, GLFWwindow *window);
};
