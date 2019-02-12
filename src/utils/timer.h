//
// Created by blinku on 12.02.19.
//

#pragma once

class Timer {
public:
    Timer() : m_Frames(0), m_LastFrame(0.0f), m_LastTime(0.0f), m_CurrentTime(0.0f), m_FPS(0.0f) {}
    ~Timer() = default;

    void CalculateFramerate();

    float GetDeltaTime() const { return m_DeltaTime; }
private:
    int m_Frames;
    float m_LastFrame;
    float m_LastTime;
    float m_CurrentTime;
    float m_DeltaTime;
    float m_FPS;
};
