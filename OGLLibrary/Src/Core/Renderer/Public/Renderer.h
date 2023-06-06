#pragma once

#include "../../Buffers/Public/VertexArray.h"
#include "../../Buffers/Public/IndexBuffer.h"
#include <glad/glad.h>


class Program;

class Renderer
{
public:
    
    Renderer() = default;
    
    void InitDebugOutput() const;

    static void DrawElements(const VertexArray& vao, const IndexBuffer& ib, const Program& shader, const unsigned int& elementType);
    static void DrawArrays(const VertexArray& vao, const Program& shader, const unsigned int& elementType, const unsigned int& start,
        const unsigned int& count);

    static void GLDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length,
                              const char* message, const void* userParam);

    //Enables blending and sets given factors to calculate the blending function with them
    static void EnableBlending(const GLenum& sFactor, const GLenum& dFactor);
    
    static void EnableLineWidth(const float& width);
    static void EnableDepthTest();
    static void EnablePrimitiveRestart(const unsigned int& index);
    static void SetPointSize(const float& size);
    static void Clear(const float& r, const float& g, const float& b, const float& a);
    static void PolygonMode(const unsigned int& faces, const unsigned int& type);
};
