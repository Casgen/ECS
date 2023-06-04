#include "../public//UniformBufferObject.h"

#include <stdexcept>

#include "../public//VertexBufferLayout.h"


UniformBufferObject::UniformBufferObject(const unsigned& _size) : size(_size)
{
    glGenBuffers(1, &rendererId);
    glBindBuffer(GL_UNIFORM_BUFFER,rendererId);
    glBufferData(GL_UNIFORM_BUFFER, _size, NULL, GL_STATIC_DRAW);
}

UniformBufferObject::~UniformBufferObject()
{
    glDeleteBuffers(1,&rendererId);
}

void UniformBufferObject::Bind() const
{
    glBindBuffer(GL_UNIFORM_BUFFER, rendererId);
}

void UniformBufferObject::BindBase(const unsigned int& index) const
{
    glBindBufferBase(GL_UNIFORM_BUFFER, index, rendererId);
}

void UniformBufferObject::BindRange(const unsigned int& index, const unsigned int& size, const unsigned int& offset) const
{
    /*
     *  Bind a range within a buffer object to an indexed buffer target
     *  target - UBO -> GL_UNIFORM_BUFFER
     *  index - on which Binding index should it be applied (layout (std140, Binding = 0))
     *  buffer - an id of the generated buffer
     *  offset - defines starting point in bytes from where the buffer should be read (I think????)
     *  size - how is the UBO big in bytes
     */
    glBindBufferRange(GL_UNIFORM_BUFFER, index, rendererId, offset, size);
}

void UniformBufferObject::Unbind() const
{
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBufferObject::setUniform(const std::string& name, const void* value) const
{
    try
    {
        const UniformBufferVariable var = uniformMap.find(name)->second;
        glBufferSubData(GL_UNIFORM_BUFFER,var.offset,var.size, value);
    } catch (std::out_of_range& e)
    {
        throw std::runtime_error("Runtime Error: Couldn't find a uniform variable \'" + name + "\' in the map!\n" + e.what());
    }
}


