#include <glew.h> //Here must be GLEW included all the way up here before including other header files
#include <iostream>
#include "../public/Renderer.h"

#include "../../Models/Public/Program.h"
#include "../../Buffers//Public/VertexArray.h"


void Renderer::InitDebugOutput() const
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugOutput, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
}

void Renderer::GLDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message,
                   const void* userParam)
{
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " << message << std::endl;

    switch (source)
    {
    case GL_DEBUG_SOURCE_API: std::cout << "Source: API";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM: std::cout << "Source: Window System";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY: std::cout << "Source: Third Party";
        break;
    case GL_DEBUG_SOURCE_APPLICATION: std::cout << "Source: Application";
        break;
    case GL_DEBUG_SOURCE_OTHER: std::cout << "Source: Other";
        break;
    }
    std::cout << std::endl;

    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR: std::cout << "Type: Error";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: std::cout << "Type: Undefined Behaviour";
        break;
    case GL_DEBUG_TYPE_PORTABILITY: std::cout << "Type: Portability";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE: std::cout << "Type: Performance";
        break;
    case GL_DEBUG_TYPE_MARKER: std::cout << "Type: Marker";
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP: std::cout << "Type: Push Group";
        break;
    case GL_DEBUG_TYPE_POP_GROUP: std::cout << "Type: Pop Group";
        break;
    case GL_DEBUG_TYPE_OTHER: std::cout << "Type: Other";
        break;
    }
    std::cout << std::endl;

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH: std::cout << "Severity: high";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM: std::cout << "Severity: medium";
        break;
    case GL_DEBUG_SEVERITY_LOW: std::cout << "Severity: low";
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification";
        break;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

void Renderer::DrawElements(const VertexArray& vao, const IndexBuffer& ib, const Program& shader, const unsigned int& elementType)
{
    shader.Bind();
    vao.Bind();
    ib.Bind();

    glDrawElements(elementType,ib.getCount(),GL_UNSIGNED_INT,nullptr);
}

void Renderer::DrawArrays(const VertexArray& vao, const Program& shader, const unsigned& elementType,
    const unsigned& start, const unsigned& count)
{
    shader.Bind();
    vao.Bind();

    glDrawArrays(elementType, start, count);
}

void Renderer::EnableBlending(const GLenum& sFactor, const GLenum& dFactor)
{
    glEnable(GL_BLEND);

    //One (Red) Channel equation: (Rsrc * Asrc) + (Rdst * (1 - Asrc))
    glBlendFunc(sFactor, dFactor);
}

void Renderer::EnableLineWidth(const float& width)
{
    //Lets OpenGL set a line width that is bigger than 1.f
    glEnable(GL_LINE_WIDTH);
    glLineWidth(width);
}

void Renderer::EnableDepthTest()
{
    //Enables Z-Buffer Depth testing
    glEnable(GL_DEPTH_TEST);
}

void Renderer::EnablePrimitiveRestart(const unsigned int& index)
{
    // Used for Triangle strip. Sets an index for telling OpenGL when to reset the Triangle Strip primitives.
    // With this no degenerate triangles are being created and it's easier for implementation.
    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(index);
}

void Renderer::SetPointSize(const float& size)
{
    glPointSize(size);
}

void Renderer::Clear(const float& r, const float& g, const float& b, const float& a)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(r, g, b, a);
}

void Renderer::PolygonMode(const unsigned& faces, const unsigned& type)
{
    glPolygonMode(faces, type);
}
