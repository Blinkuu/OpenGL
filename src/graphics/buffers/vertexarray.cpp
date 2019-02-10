//
// Created by blinku on 23.01.19.
//

#include "vertexarray.h"
#include "glad/glad.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_VertexArrayID);
}

void VertexArray::AddBuffer(Buffer buffer) {
    unsigned int offset = 0;

    Bind();
    buffer.Bind();
    glVertexAttribPointer(0, buffer.GetPointerOffset()[0], GL_FLOAT, GL_FALSE, buffer.GetComponentCount() * sizeof(float), reinterpret_cast<void *>(offset * sizeof(float)));
    glEnableVertexAttribArray(0);
    offset += buffer.GetPointerOffset()[0];
    for (unsigned int index = 1; index < buffer.GetPointerOffset().size(); ++index) {
        glVertexAttribPointer(index, buffer.GetPointerOffset()[index], GL_FLOAT, GL_FALSE, buffer.GetComponentCount() * sizeof(float), reinterpret_cast<void *>(offset * sizeof(float)));
        glEnableVertexAttribArray(index);
        offset += buffer.GetPointerOffset()[index];
    }
    Unbind();
    buffer.Unbind();
}

void VertexArray::Bind() const {
    glBindVertexArray(m_VertexArrayID);
}

void VertexArray::Unbind() const {
    glBindVertexArray(0);
}
