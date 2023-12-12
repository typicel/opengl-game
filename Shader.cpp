//
// Created by tyler on 12/11/2023.
//

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include "include/Shader.h"
#include "include/Errors.h"

Shader::Shader(const char *vShaderCode, const char *fShaderCode) {
    uint32_t vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    GLCall(glShaderSource(vertex, 1, &vShaderCode, NULL));
    glCompileShader(vertex);

    int success;
    char infoLog[512];
    GLCall(glGetShaderiv(vertex, GL_COMPILE_STATUS, &success));
    if(!success)
    {
        GLCall(glGetShaderInfoLog(vertex, 512, NULL, infoLog));
        std::cout << "Shader | Shader compilation error: " << infoLog << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    GLCall(glShaderSource(fragment, 1, &fShaderCode, NULL));
    GLCall(glCompileShader(fragment));

    GLCall(glGetShaderiv(fragment, GL_COMPILE_STATUS, &success));
    if(!success)
    {
        GLCall(glGetShaderInfoLog(fragment, 512, NULL, infoLog));
        std::cout << "Shader | Shader compilation error: " << infoLog << std::endl;
    }

    m_shaderId = glCreateProgram();
    GLCall(glAttachShader(m_shaderId, vertex));
    GLCall(glAttachShader(m_shaderId, fragment));
    GLCall(glLinkProgram(m_shaderId));

    GLCall(glGetProgramiv(m_shaderId, GL_LINK_STATUS, &success));
    if(!success)
    {
        GLCall(glGetProgramInfoLog(m_shaderId, 512, NULL, infoLog));
        std::cout << "Shader | Shader compilation error: " << infoLog << std::endl;
    }

    std::cout << "Shader | Shader program loaded and linked" << std::endl;
    GLCall(glDeleteShader(vertex));
    GLCall(glDeleteShader(fragment));
}

void Shader::Use() const {
    GLCall(glUseProgram(m_shaderId));
}

void Shader::SetMatrix4(const char* name, glm::mat4 value) const {
    GLCall(glUniformMatrix4fv(glGetUniformLocation(m_shaderId, name), 1, false, glm::value_ptr(value)));
}

void Shader::SetInteger(const char *name, int value) const {
    GLCall(glUniform1i(glGetUniformLocation(m_shaderId, name), value));
}

void Shader::SetVector3f(const char *name, glm::vec3 value) const {
    GLCall(glUniform3f(glGetUniformLocation(m_shaderId, name), value.x, value.y, value.z));
}
