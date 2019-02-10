//
// Created by blinku on 23.01.19.
//

#pragma once

#include "buffer.h"
#include <vector>
#include <memory>

class VertexArray {
public:
    VertexArray();
    ~VertexArray() = default;
public:
    void AddBuffer(Buffer buffer);
    void Bind() const;
    void Unbind() const;
private:
    unsigned int m_VertexArrayID;
    std::vector<Buffer> m_Buffers;
};
