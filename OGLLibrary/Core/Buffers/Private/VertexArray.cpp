#include <glew.h>

#include "../Public/VertexArray.h"
#include "../Public/VertexBufferLayout.h"


VertexArray::VertexArray()
{
    // Creates a Vertex Array. This allows for Binding VertexBuffer and it's layout to the VAO and only call the Binding of the VAO.
    // For every object, there can be one global VAO or for each object a created VAO. (Recommended by Khronos)
    glGenVertexArrays(1, &rendererId);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1,&rendererId);
}

void VertexArray::Bind() const
{
    glBindVertexArray(rendererId);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();

    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i); //Dont forget this! we need to enable the attribute!

        /*
         *  Index - Where the Attribute will start in the buffer
         *  size - How many values will be processed
         *  type - What value type will be processed (used for the size)
         *  normalized - if we want to convert 255 - 0 to 1.0 - 0.0 (normalizing values
         *  stride - How many bytes (or steps) does it take to go, to the next e.g. vertex position
         *  pointer - offsetof. Pointer to the attribute
         */
        glVertexAttribPointer(i,element.count,element.type,element.normalized,layout.getStride(), (const void*) offset);
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }

    vb.Unbind();
}
