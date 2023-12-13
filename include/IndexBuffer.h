#pragma once

#include <cstdint>
#include "glad/glad.h"

class IndexBuffer{
public:
    IndexBuffer(const uint32_t* data, const uint32_t count); // count - element count, size = total size of buffer
    ~IndexBuffer();

    void Bind();
    void Unbind();

private:
    uint32_t m_indexBufferId;
    uint32_t m_Count;
};
