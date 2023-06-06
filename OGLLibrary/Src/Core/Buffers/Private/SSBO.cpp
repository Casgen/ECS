#include "../Public/SSBO.h"

#include <glad/glad.h>

SSBO::SSBO(const void* data, const unsigned& size)
{
    glGenBuffers(1,&m_RendererId);                                              // This initializes a buffer for us. After the initialization, an ID of the buffer is set.
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_RendererId);                                // Selects the buffer. Defines how we want to use is and takes an ID of the buffer.
    glBufferData(GL_SHADER_STORAGE_BUFFER,size,data, GL_DYNAMIC_COPY);                    // Pass in the data (size in bytes, pointer to the bytes)
}

void SSBO::Bind() const
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_RendererId);
}

void SSBO::Unbind() const
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void SSBO::BindBase(const unsigned int& Binding) const
{
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, Binding, m_RendererId); 
}
