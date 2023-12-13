#pragma once

#include <cstdint>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader {
private:
    uint32_t m_shaderId;

public:
    Shader() {}
    Shader(const char* vShaderCode, const char* fShaderCode);

    void SetMatrix4(const char* name, const glm::mat4 value) const;
    void SetInteger(const char* name, const int value) const;
    void SetVector3f(const char* name, const glm::vec3 value) const;

    void Use() const;

};