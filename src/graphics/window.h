//
// Created by blinku on 17.12.18.
//

#pragma once

class GLFWmonitor;
class GLFWwindow;

class Window {
public:
    Window(int width, int height, const char* windowName, GLFWmonitor *monitor, GLFWwindow *window);
    ~Window() = default;

    void Clear();
    void Update();
    int ShouldClose();
    void Terminate();

    void ProcessInput();
private:
    int m_Width;
    int m_Height;
    const char* m_WindowName;
    GLFWwindow* m_Window;
private:
    void Init(GLFWmonitor *monitor, GLFWwindow *window);
};
