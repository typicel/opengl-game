#include "include/IndexBuffer.h"

IndexBuffer::IndexBuffer(const uint32_t* data, const uint32_t count) {
    glGenBuffers(1, &m_indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(uint32_t), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_indexBufferId);
}

void IndexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_indexBufferId);
}

void IndexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}