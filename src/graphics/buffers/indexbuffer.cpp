//
// Created by blinku on 23.01.19.
//

#include "indexbuffer.h"
#include "glad/glad.h"

IndexBuffer::IndexBuffer(unsigned int *data, unsigned int count) : m_Count(count) {
    glGenBuffers(1, &m_IndexBufferID);
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), reinterpret_cast<const void*>(data), GL_STATIC_DRAW);
    Unbind();
}

void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferID);
}

void IndexBuffer::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
