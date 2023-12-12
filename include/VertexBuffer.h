//
// Created by tyler on 12/11/2023.
//

#ifndef RENDERER_VERTEXBUFFER_H
#define RENDERER_VERTEXBUFFER_H

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


#endif //RENDERER_VERTEXBUFFER_H
