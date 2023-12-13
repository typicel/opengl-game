#pragma once

#include <cstdint>
#include "glad/glad.h"

class VertexBuffer {
public:
    VertexBuffer(const void* data, uint32_t size);
    ~VertexBuffer();

    void Bind();
    void Unbind();

private:
    uint32_t m_vertexBufferId;
};
