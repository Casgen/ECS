#pragma once

#include <cstddef>

struct VertexBuffer
{
    size_t m_Size = 0;
    size_t m_VertexSize = 0;
    unsigned int m_rendererID = 0;

    VertexBuffer();

    /** 
     *  @param data - raw data being passed (positions, colors, textures, normals,...)
     *  @param size - size of the data in bytes
     */
    VertexBuffer(const void* data, unsigned int size);
    
    /** 
     *  @param data - raw data being passed (positions, colors, textures, normals,...)
     *  @param size - size of the data in bytes
     *  @param drawType - indicates how frequently is the buffer data changing.
     */
    VertexBuffer(const void* data, unsigned int size, unsigned int drawType);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
    
};
