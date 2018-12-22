//
// Created by blinku on 17.12.18.
//

#include "window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

Window::Window(int width, int height, const char *windowName, GLFWmonitor *monitor, GLFWwindow *window) :
    m_Width(width), m_Height(height), m_WindowName(windowName) {

    Init(monitor, window);
}

void Window::Init(GLFWmonitor *monitor, GLFWwindow *window) {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW!" << std::endl;
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_Window = glfwCreateWindow(m_Width, m_Height, m_WindowName, monitor, window);
    if (!m_Window) {
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }

    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
}

void Window::Terminate() {
    glfwTerminate();
}

void Window::Clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::Update() {
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

int Window::ShouldClose() {
    return glfwWindowShouldClose(m_Window);
}

void Window::ProcessInput() {
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(m_Window, true);

    if(glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}



//Calbacks
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}