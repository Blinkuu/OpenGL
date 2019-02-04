//
// Created by Lukasz Gut on 28/12/2018.
//

#pragma once

#define FPS_CAM 1

#define YAW 0.0f
#define PITCH 0.0f
#define MOV_SPEED 2.5f
#define SENSITIVITY 0.1f

#include <glm/glm.hpp>

enum class CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera {
public:
    Camera();

    glm::mat4 GetViewMatrix() const;
    glm::vec3 GetPosition() const;
    glm::vec3 GetFront() const;
    bool GetFlashLightStatus() const;
    void ProcessKeyboardMovement(CameraMovement direction, float deltaTime);
    void ProcessMouseMovement(float xOffset, float yOffset);
    void ProcessFlashlight();
private:
    glm::vec3 m_Pos;
    glm::vec3 m_WorldUp;
    glm::vec3 m_Front;
    glm::vec3 m_Right;
    glm::vec3 m_Up;

    glm::vec3 m_FrontFPS;

    float m_Yaw;
    float m_Pitch;

    float m_MovementSpeed;
    float m_MouseSensitivity;

    bool m_FlashlightStatus;
private:
    void UpdateCameraVectors();
};
