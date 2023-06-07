#include <glad/glad.h>
#include "../Public/IndexBuffer.h"
#include "../../../Utils/Utils.h"


IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_Count(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    glGenBuffers(1,&m_rendererID);                                              // This initializes a buffer for us. After the initialization, an ID of the buffer is set.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);                                    // Selects the buffer. Defines how we want to use is and takes an ID of the buffer.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int),data, GL_STATIC_DRAW);  // Pass in the data (size in bytes, pointer to the bytes)
}


IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1,&m_rendererID);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
