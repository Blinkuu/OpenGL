//
// Created by Lukasz Gut on 23/12/2018.
//
#include "texture.h"
#include <iostream>
#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* texturePath) : m_TexturePath(texturePath) {
    Init();
}

Texture::~Texture() {
    //if(m_TextureID)
        //glDeleteTextures(1, &m_TextureID);
}

void Texture::Bind() const {
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}
void Texture::Unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Activate(int offset) {
    glActiveTexture(GL_TEXTURE0 + (GLenum)offset);
}

void Texture::Init() {
    glGenTextures(1, &m_TextureID);

    unsigned char *data = stbi_load(m_TexturePath.c_str(), &m_Width, &m_Height, &m_NrChannels, 0);
    if (data)
    {
        GLenum format;
        if(m_NrChannels == 1)
            format = GL_RED;
        else if(m_NrChannels == 3)
            format = GL_RGB;
        else if(m_NrChannels == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, m_TextureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Couldn't load the texture!" << std::endl;
    }

    stbi_image_free(data);
}

void Texture::SetID(unsigned int id) {
    m_TextureID = id;
}

void Texture::SetPath(std::string path) {
    m_TexturePath = path;
}

void Texture::SetType(std::string type) {
    m_Type = type;
}
