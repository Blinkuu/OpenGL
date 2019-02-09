//
// Created by blinku on 23.01.19.
//

#pragma once

class IndexBuffer {
public:
    IndexBuffer() = default;
    IndexBuffer(unsigned int* data, unsigned int count);
    ~IndexBuffer() = default;
public:
    void Bind() const;
    void Unbind() const;
    inline unsigned int GetCount() const;
private:
    unsigned int m_IndexBufferID;
    unsigned int m_Count;
};

unsigned int IndexBuffer::GetCount() const {
    return m_Count;
}