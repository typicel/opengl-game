//
// Created by tyler on 12/11/2023.
//

#ifndef RENDERER_INDEXBUFFER_H
#define RENDERER_INDEXBUFFER_H


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


#endif //RENDERER_INDEXBUFFER_H
