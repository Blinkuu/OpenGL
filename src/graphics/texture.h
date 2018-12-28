//
// Created by Lukasz Gut on 23/12/2018.
//

#pragma once

class Texture {
public:
    Texture() = delete;
    explicit Texture(const char* texturePath);
    ~Texture();

    void Bind() const;
    void Unbind() const;

    void Activate(int offset) const;
private:
    unsigned int m_TextureID;
    const char* m_TexturePath;
    int m_Width;
    int m_Height;
    int m_NrChannels;
private:
    void Init();
};
