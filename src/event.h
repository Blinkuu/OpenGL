//
// Created by Lukasz Gut on 28/12/2018.
//

#pragma once

class Event {
public:
    Event() = default;
    ~Event() = default;
    void SetMousePosInEvent(float x, float y);
private:
    float xPos;
    float yPos;
};