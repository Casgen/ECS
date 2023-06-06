#include <glad/glad.h>
#include <iostream>

#include "../Public/Shader.h"
#include "../../../Utils/Utils.h"


Shader::Shader(const std::string& filename, unsigned int shaderType, bool& result)
    : filepath(filename), rendererId(0), type(shaderType)
{
    try
    {
        std::string source = Utils::ReadFile(filename);
        result = CompileShader(shaderType, source);
    } catch (std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
        result = false;
    }
}

std::string Shader::GetTypeString() const
{
    switch (type)
    {
        case GL_VERTEX_SHADER: return "Vertex Shader";
        case GL_FRAGMENT_SHADER: return "Fragment Shader";
        case GL_GEOMETRY_SHADER: return "Geometry Shader";
        case GL_TESS_EVALUATION_SHADER: return "Tess Eval Shader";
        case GL_TESS_CONTROL_SHADER: return "Tess Control Shader";
        default: return "Unrecognized";
    }
}

bool Shader::CompileShader(uint32_t type, const std::string& source)
{
    rendererId = glCreateShader(type); // Creates a shader object
    const char* src = source.c_str(); // Code that is converted to a C-style string. 

    glShaderSource(rendererId, 1, &src, nullptr);
    // Takes in generated id of the shader object, the number of shaders, the source
    glCompileShader(rendererId); // Compiles the shader

    int result;
    glGetShaderiv(rendererId, GL_COMPILE_STATUS, &result); //See if the compilation was successful

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(rendererId, GL_INFO_LOG_LENGTH, &length); // if it was unsuccessful, get the error message
        char* message = (char*)alloca(length * sizeof(char));
        //This creates an array with alloca() C-function, which ensures stack allocation

        glGetShaderInfoLog(rendererId, length, &length, message);


        std::cout << "Failed to compile ";

        switch (type)
        {
        case GL_VERTEX_SHADER: std::cout << "Vertex";
            break;
        case GL_FRAGMENT_SHADER: std::cout << "Fragment";
            break;
        case GL_GEOMETRY_SHADER: std::cout << "Geometry";
            break;
        }

        std::cout << " Shader!" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(rendererId);
        return false;
    }

    return true;
}


