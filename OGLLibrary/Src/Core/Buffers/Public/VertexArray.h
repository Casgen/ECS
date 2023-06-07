#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
    unsigned int rendererId;
    
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;
    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};
