//
// Created by blinku on 09.02.19.
//

#include "mesh.h"
#include "glad/glad.h"

#include <iostream>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    : m_Vertices(vertices), m_Indices(indices), m_Textures(textures) {
    SetupMesh();
}

void Mesh::SetupMesh() {

    std::vector<unsigned short int> offsets = {3, 3, 2};

    VertexArray tempVAO;
    Buffer tempVBO(&m_Vertices[0], static_cast<unsigned int>(m_Vertices.size()) * 12, 8, offsets);
    IndexBuffer tempIBO(&m_Indices[0], static_cast<unsigned int>(m_Indices.size()));
    m_VAO = tempVAO;
    m_VBO = tempVBO;
    m_IBO = tempIBO;

    m_VAO.AddBuffer(m_VBO);

    m_VAO.Unbind();
}

void Mesh::Draw(Shader shader) {
    unsigned int diffuseNumber = 1;
    unsigned int specularNumber = 1;

    for(unsigned int i = 0; i < m_Textures.size(); i++)
    {
        Texture::Activate(i);
        std::string number;
        std::string name = m_Textures[i].GetType();

        if(name == "texture_diffuse")
            number = std::to_string(diffuseNumber++);
        else if(name == "texture_specular")
            number = std::to_string(specularNumber++);

        shader.SetInt(("u_Material." + name + number).c_str(), i);
        m_Textures[i].Bind();
    }

    m_VAO.Bind();
    m_IBO.Bind();
    glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, nullptr);
    m_IBO.Unbind();
    m_VAO.Unbind();

    Texture::Activate(0);
}
