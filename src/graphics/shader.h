//
// Created by blinku on 17.12.18.
//

#pragma once

#include <glm/glm.hpp>

class Shader {
public:
    Shader() = delete;
    Shader(const char *vertPath, const char *fragPath);
    ~Shader() = default;

    void Use() const;

    unsigned int GetID() const noexcept { return m_ShaderID; }

    void SetInt(const char* locationName, int v1) const;
    void SetBool4(const char* locationName, bool v1, bool v2, bool v3, bool v4) const;
    void SetInit4(const char* locationName, int v1, int v2, int v3, int v4) const;
    void SetFloat4(const char* locationName, float v1, float v2, float v3, float v4) const;
    void SetMat4(const char* locationName, glm::mat4& matrix);
private:
    unsigned int m_ShaderID;
    const char* m_VertPath;
    const char* m_FragPath;
private:
    void Init();
    int GetLocation(const char* locationName) const;
};