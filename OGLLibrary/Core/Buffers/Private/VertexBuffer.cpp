#include <glew.h>
#include "../public//VertexBuffer.h"


VertexBuffer::VertexBuffer(const void* data, unsigned int size)
    : m_Size(size)
{
    glGenBuffers(1,&m_rendererID);                                              // This initializes a buffer for us. After the initialization, an ID of the buffer is set.
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);                                // Selects the buffer. Defines how we want to use is and takes an ID of the buffer.
    glBufferData(GL_ARRAY_BUFFER,size,data, GL_STATIC_DRAW);                    // Pass in the data (size in bytes, pointer to the bytes)
}

VertexBuffer::VertexBuffer(const void* data, unsigned size, unsigned drawType)
    : m_Size(size)
{
    glGenBuffers(1,&m_rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ARRAY_BUFFER,size,data, drawType);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1,&m_rendererID);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
