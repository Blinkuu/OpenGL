//
// Created by blinku on 17.12.18.
//

#include "window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

static float __lastX = 400.0f;
static float __lastY = 300.0f;

static float __xOffset;
static float __yOffset;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback([[maybe_unused]]GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

Window::Window(int width, int height, const char *windowName, GLFWmonitor *monitor, GLFWwindow *window, Camera* camera) :
    m_Width(width), m_Height(height), m_WindowName(windowName), m_Camera(camera) {

    Init(monitor, window);
    m_DepthTest = false;
}

Window::~Window() {
    glfwTerminate();
}

void Window::Init(GLFWmonitor *monitor, GLFWwindow *window) {
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW!" << std::endl;
        exit(1);
    }

    //glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
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

    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
    glfwSetCursorPosCallback(m_Window, mouse_callback);
    glfwSetKeyCallback(m_Window, key_callback);
}

void Window::Terminate() {
    glfwTerminate();
}

void Window::Clear() {
    if(!m_DepthTest)
        glClear(GL_COLOR_BUFFER_BIT);
    else
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Update() {
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

int Window::ShouldClose() {
    return glfwWindowShouldClose(m_Window);
}

void Window::ProcessInput(float deltaTime) {
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(m_Window, true);

    if(glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS) {
        m_Camera->ProcessKeyboardMovement(CameraMovement::FORWARD, deltaTime);
    }
    if(glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS) {
        m_Camera->ProcessKeyboardMovement(CameraMovement::LEFT, deltaTime);
    }
    if(glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS) {
        m_Camera->ProcessKeyboardMovement(CameraMovement::BACKWARD, deltaTime);
    }
    if(glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS) {
        m_Camera->ProcessKeyboardMovement(CameraMovement::RIGHT, deltaTime);
    }
    if(glfwGetKey(m_Window, GLFW_KEY_E) == GLFW_PRESS) {
        m_Camera->ProcessKeyboardMovement(CameraMovement::UP, deltaTime);
    }
    if(glfwGetKey(m_Window, GLFW_KEY_Q) == GLFW_PRESS) {
        m_Camera->ProcessKeyboardMovement(CameraMovement::DOWN, deltaTime);
    }

    int state = glfwGetKey(m_Window, GLFW_KEY_F);
    if (state == GLFW_PRESS)
        m_Camera->ProcessFlashlight();

    double xpos, ypos;
    glfwGetCursorPos(m_Window, &xpos, &ypos);
    float xoff = static_cast<float>(xpos) - __lastX;
    float yoff = __lastY - static_cast<float>(ypos);

    __xOffset = xoff;
    __yOffset = yoff;

    __lastX = static_cast<float>(xpos);
    __lastY = static_cast<float>(ypos);

    m_Camera->ProcessMouseMovement(__xOffset, __yOffset);

    if(glfwGetKey(m_Window, GLFW_KEY_SPACE) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Window::EnableDepthTesting() {
    glEnable(GL_DEPTH_TEST);
    m_DepthTest = true;
}

void Window::DisableDepthTesting() {
    glDisable(GL_DEPTH_TEST);
    m_DepthTest = false;
}

float Window::GetAspectRatio() const {
    return static_cast<float>(m_Width)/static_cast<float>(m_Height);
}

//Calbacks
void framebuffer_size_callback([[maybe_unused]]GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback([[maybe_unused]]GLFWwindow* window, [[maybe_unused]]double xpos, [[maybe_unused]]double ypos) {}

void key_callback([[maybe_unused]]GLFWwindow* window, [[maybe_unused]]int key, [[maybe_unused]]int scancode, [[maybe_unused]]int action, [[maybe_unused]]int mods) {}