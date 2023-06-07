#pragma once
#include <vector>
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
    void push(unsigned int count);


    [[nodiscard]] unsigned int getStride() const;

    [[nodiscard]] std::vector<VertexBufferElement> getElements() const;

    std::vector<VertexBufferElement> VertexBufferLayoutgetElements() const;
};
