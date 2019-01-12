//
// Created by blinku on 17.12.18.
//

#include "shader.h"

#include <glad/glad.h>
#include <iostream>

#include "file_loader.h"

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char *vertPath, const char *fragPath) : m_VertPath(vertPath), m_FragPath(fragPath) {
    Init();
}

void Shader::Init() {
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    std::string vertexShaderSource = LoadFile(m_VertPath);
    const char *vertexData = vertexShaderSource.c_str();

    glShaderSource(vertexShader, 1, &vertexData, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string fragmentShaderSource = LoadFile(m_FragPath);
    const char *fragmentData= fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentData, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    m_ShaderID = glCreateProgram();
    glAttachShader(m_ShaderID, vertexShader);
    glAttachShader(m_ShaderID, fragmentShader);
    glLinkProgram(m_ShaderID);

    glGetShaderiv(m_ShaderID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDetachShader(m_ShaderID, vertexShader);
    glDetachShader(m_ShaderID, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


void Shader::Bind() const {
    glUseProgram(m_ShaderID);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

int Shader::GetLocation(const char* locationName) const {
    int location = glGetUniformLocation(m_ShaderID, locationName);
    if (location == -1)
        std::cout << "<"<< locationName << "> uniform was not found in shader" << std::endl;
    return location;
}

void Shader::SetBool4(const char* locationName, bool v1, bool v2, bool v3, bool v4) const {
    glUniform4i(GetLocation(locationName), v1, v2, v3, v4);
}

void Shader::SetInt(const char* locationName, int v1) const {
    glUniform1i(GetLocation(locationName), v1);
}

void Shader::SetInit4(const char* locationName, int v1, int v2, int v3, int v4) const {
    glUniform4i(GetLocation(locationName), v1, v2, v3, v4);
}

void Shader::SetFloat4(const char* locationName, float v1, float v2, float v3, float v4) const {
    glUniform4f(GetLocation(locationName), v1, v2, v3, v4);
}

void Shader::SetMat4(const char* locationName, const glm::mat4& matrix) const {
    glUniformMatrix4fv(GetLocation(locationName), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetVec4(const char* locationName, const glm::vec4& vec) const {
    glUniform4f(GetLocation(locationName), vec.x, vec.y, vec.z, vec.w);
}

void Shader::SetVec3(const char* locationName, const glm::vec3& vec) const {
    glUniform3f(GetLocation(locationName), vec.x, vec.y, vec.z);
}

void Shader::SetVec2(const char* locationName, const glm::vec2& vec) const {
    glUniform2f(GetLocation(locationName), vec.x, vec.y);
}
