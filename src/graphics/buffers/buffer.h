//
// Created by blinku on 23.01.19.
//

#pragma once

#include <vector>

class Buffer {
public:
    Buffer() = delete;
    Buffer(float* data, unsigned int count, unsigned int componentCount, std::vector<unsigned short int> pointerOffset);
    ~Buffer();
public:
    void Bind() const;
    void Unbind() const;
    inline unsigned int GetComponentCount() const;
    inline const std::vector<unsigned int short>& GetPointerOffset() const;
private:
    unsigned int m_BufferID;
    unsigned int m_ComponentCount;
    std::vector<unsigned short int> m_PointerOffset;
};

unsigned int Buffer::GetComponentCount() const {
    return m_ComponentCount;
}

const std::vector<unsigned int short>& Buffer::GetPointerOffset() const {
    return m_PointerOffset;
}