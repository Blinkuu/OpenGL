//
// Created by Lukasz Gut on 28/12/2018.
//

#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera() :
    m_Pos(glm::vec3(0.0f, 0.0f, 0.0f)),
    m_WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
    m_Right(glm::normalize(glm::cross(m_Front, m_WorldUp))),
    m_Up(glm::normalize(glm::cross(m_Right, m_Front))),
    m_Yaw(YAW),
    m_Pitch(PITCH),
    m_MovementSpeed(MOV_SPEED),
    m_MouseSensitivity(SENSITIVITY) {}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(m_Pos, m_Pos + m_Front, m_Up);
}

void Camera::ProcessKeyboardMovement(CameraMovement direction, float deltaTime) {
#if FPS_CAM
    if(direction == CameraMovement::FORWARD) {
        m_Pos += m_FrontFPS * m_MovementSpeed * deltaTime;
    }
    if(direction == CameraMovement::BACKWARD) {
        m_Pos -= m_FrontFPS * m_MovementSpeed * deltaTime;
    }
#else
    if(direction == CameraMovement::FORWARD) {
        m_Pos += m_Front * m_MovementSpeed * deltaTime;
    }
    if(direction == CameraMovement::BACKWARD) {
        m_Pos -= m_Front * m_MovementSpeed * deltaTime;
    }
#endif
    if(direction == CameraMovement::LEFT) {
        m_Pos -= m_Right * m_MovementSpeed * deltaTime;
    }
    if(direction == CameraMovement::RIGHT) {
        m_Pos += m_Right * m_MovementSpeed * deltaTime;
    }
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset) {
    xoffset *= m_MouseSensitivity;
    yoffset *= m_MouseSensitivity;

    m_Yaw += xoffset;
    m_Pitch += yoffset;

    if(m_Pitch > 89.0f) {
        m_Pitch = 89.0f;
    }
    if(m_Pitch < -89.0f) {
        m_Pitch = -89.0f;
    }

    UpdateCameraVectors();
}

void Camera::UpdateCameraVectors() {
    glm::vec3 front;
    front.x = static_cast<float>(cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)));
    front.y = static_cast<float>(sin(glm::radians(m_Pitch)));
    front.z = static_cast<float>(sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)));

    m_Front = glm::normalize(front);
    m_FrontFPS = glm::normalize(glm::vec3(front.x, 0.0f, front.z));

    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}