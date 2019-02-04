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
    m_MouseSensitivity(SENSITIVITY),
    m_FlashlightStatus(false) {}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(m_Pos, m_Pos + m_Front, m_Up);
}

glm::vec3 Camera::GetPosition() const {
    return m_Pos;
}

void Camera::ProcessKeyboardMovement(CameraMovement direction, float deltaTime) {
    float velocity = m_MovementSpeed * deltaTime;
#if FPS_CAM
    if(direction == CameraMovement::FORWARD) {
        m_Pos += m_FrontFPS * velocity;
    } else if(direction == CameraMovement::BACKWARD) {
        m_Pos -= m_FrontFPS * velocity;
    }
#else
    if(direction == CameraMovement::FORWARD) {
        m_Pos += m_Front * velocity;
    }
    if(direction == CameraMovement::BACKWARD) {
        m_Pos -= m_Front * velocity;
    }
#endif
    else if(direction == CameraMovement::LEFT) {
        m_Pos -= m_Right * velocity;
    } else if(direction == CameraMovement::RIGHT) {
        m_Pos += m_Right * velocity;
    } else if(direction == CameraMovement::UP) {
        m_Pos += m_WorldUp * velocity;
    } else if(direction == CameraMovement::DOWN) {
        m_Pos -= m_WorldUp * velocity;
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

void Camera::ProcessFlashlight() {
    if(m_FlashlightStatus)
        m_FlashlightStatus = false;
    m_FlashlightStatus = true;
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

glm::vec3 Camera::GetFront() const {
    return m_Front;
}

bool Camera::GetFlashLightStatus() const {
    return m_FlashlightStatus;
}
