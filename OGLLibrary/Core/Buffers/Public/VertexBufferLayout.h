#pragma once
#include <vector>
#include <glew.h>
#include "VertexBufferElement.h"


class VertexBufferLayout
{
    std::vector<VertexBufferElement> elements;
    unsigned int stride;
public:
    VertexBufferLayout() : stride(0)
    {
    };

    template <typename T>
    void push(unsigned int count)
    {
    }

    template <>
    void push<float>(unsigned int count)
    {
        elements.push_back(VertexBufferElement{count, GL_FLOAT, GL_FALSE});
        stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
    }

    template <>
    void push<unsigned int>(unsigned int count)
    {
        elements.push_back(VertexBufferElement{count, GL_UNSIGNED_INT, GL_FALSE});
        stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
    }

    template <>
    void push<unsigned char>(unsigned int count)
    {
        elements.push_back(VertexBufferElement{count, GL_UNSIGNED_BYTE, GL_TRUE});
        stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
    }

    [[nodiscard]] unsigned int getStride() const { return stride; }

    [[nodiscard]] std::vector<VertexBufferElement> getElements() const
    {
        return elements;
    }
};
