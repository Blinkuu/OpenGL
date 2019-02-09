//
// Created by blinku on 09.02.19.
//

#include "mesh.h"
#include "glad/glad.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    : m_Vertices(vertices), m_Indices(indices), m_Textures(textures) {
    SetupMesh();
}

void Mesh::SetupMesh() {
    VertexArray VAO;
    VAO.Bind();
    std::vector<unsigned short int> Offsets = {3, 3, 2};
    Buffer VBO(&m_Vertices[0], m_Vertices.size() * 12, 8, Offsets);
    VAO.AddBuffer(&VBO);

    IndexBuffer IBO(&m_Indices[0], static_cast<unsigned int>(m_Indices.size()));
    IBO.Bind();

    VAO.Unbind();
    IBO.Unbind();

    m_VAO = VAO;
    m_VBO = VBO;
    m_IBO = IBO;
}

void Mesh::Draw(Shader shader) {
    unsigned int diffuseNumber = 1;
    unsigned int specularNumber = 1;
    for(unsigned int i = 0; i < m_Textures.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string name = m_Textures[i].GetType();
        if(name == "Diffuse")
            number = std::to_string(diffuseNumber++);
        else if (name == "Specular")
            number = std::to_string(specularNumber++);
        shader.SetInt(("u_Material.texture"+name+number).c_str(),i);
    }
    glActiveTexture(GL_TEXTURE0);
    m_VAO.Bind();
    glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, nullptr);
    m_VAO.Unbind();
}
