//
// Created by Lukasz Gut on 23/12/2018.
//

#pragma once

#include <string>

class Texture {
public:
    Texture() = default;
    explicit Texture(const char* texturePath);
    ~Texture();

    void Bind() const;
    void Unbind() const;

    static void Activate(int offset);

    inline unsigned int GetID() const { return m_TextureID; }
    inline std::string GetTexturePath() const { return m_TexturePath; }
    inline std::string GetType() const { return m_Type; }

    void SetID(unsigned int id);
    void SetPath(std::string path);
    void SetType(std::string type);

private:
    unsigned int m_TextureID;
    std::string m_TexturePath;
    std::string m_Type; /* e.g. specular or diffuse */
    int m_Width;
    int m_Height;
    int m_NrChannels;
private:
    void Init();
};
