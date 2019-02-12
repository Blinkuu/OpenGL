//
// Created by blinku on 12.02.19.
//

#include "timer.h"
#include <GLFW/glfw3.h>
#include <iostream>

void Timer::CalculateFramerate() {
    ++m_Frames;
    m_CurrentTime = static_cast<float>(glfwGetTime());
    m_DeltaTime = m_CurrentTime - m_LastTime;
    m_LastTime = m_CurrentTime;

    if(m_CurrentTime - m_LastFrame > 1.0f && m_Frames > 10) {
        m_FPS = m_Frames/(m_CurrentTime - m_LastFrame);
        std::cout << "[FPS] " << m_FPS << std::endl;
        m_LastFrame = m_CurrentTime;
        m_Frames = 0;
    }
}
