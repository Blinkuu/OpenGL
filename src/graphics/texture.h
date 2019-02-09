//
// Created by Lukasz Gut on 23/12/2018.
//

#pragma once

#include <string>

class Texture {
public:
    Texture() = delete;
    explicit Texture(const char* texturePath);
    ~Texture();

    void Bind() const;
    void Unbind() const;

    void Activate(int offset) const;

    inline unsigned int GetID() const { return m_TextureID; }
    inline std::string GetType() const { return m_Type; }
private:
    unsigned int m_TextureID;
    const char* m_TexturePath;
    std::string m_Type; /* e.g. specular or diffuse */
    int m_Width;
    int m_Height;
    int m_NrChannels;
private:
    void Init();
};
