//
// Created by blinku on 09.02.19.
//

#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"
#include "graphics/texture.h"
#include "graphics/shader.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh {
public:
    Mesh() = default;
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    ~Mesh() = default;

    void Draw(Shader shader);
private:
    VertexArray m_VAO;
    Buffer m_VBO;
    IndexBuffer m_IBO;
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<Texture> m_Textures;
private:
    void SetupMesh();
};
