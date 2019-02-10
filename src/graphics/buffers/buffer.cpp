//
// Created by blinku on 23.01.19.
//

#include "buffer.h"
#include "glad/glad.h"

Buffer::Buffer(void* data, unsigned int count, unsigned int componentCount, std::vector<unsigned short int> pointerOffset)
    : m_ComponentCount(componentCount), m_PointerOffset(pointerOffset) {
    glGenBuffers(1, &m_BufferID);
    Bind();
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), reinterpret_cast<const void*>(data), GL_STATIC_DRAW);
    Unbind();
}

void Buffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
}

void Buffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
