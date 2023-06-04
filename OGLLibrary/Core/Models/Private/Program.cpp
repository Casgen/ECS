#include <glew.h>
#include <iostream>

#include "../public/Program.h"

#include <gtc/type_ptr.hpp>

#include "../../../Utils/Utils.h"

#define INIT_SHADER(shaderVar, shaderSuccess, shaderPath, shaderType) \
    shaderVar = Shader(shaderPath,shaderType, shaderSuccess); \
    if (shaderSuccess) \
    { \
        glAttachShader(m_RendererId,(shaderVar).getId()); \
        std::cout << (shaderVar).GetTypeString() + ".....................OK" << std::endl; \
    } else \
    { \
        std::cout << (shaderVar).GetTypeString() + ".....................ERROR" << std::endl; \
    }

Program::Program(const std::string& shaderPath)
{
    m_RendererId = glCreateProgram();

    bool vertSuccess, fragSuccess, geomSuccess, teseSuccess, tescSuccess = false;
    Shader vertShader, fragShader, geomShader, teseShader, tescShader;

    INIT_SHADER(vertShader, vertSuccess, shaderPath + ".vert", GL_VERTEX_SHADER)
    ASSERT(vertSuccess);
    
    INIT_SHADER(fragShader, fragSuccess, shaderPath + ".frag", GL_FRAGMENT_SHADER)
    ASSERT(fragSuccess);
    
    INIT_SHADER(geomShader, geomSuccess, shaderPath + ".geom", GL_GEOMETRY_SHADER)
    INIT_SHADER(teseShader, teseSuccess, shaderPath + ".tese", GL_TESS_EVALUATION_SHADER)

    if (teseSuccess)
    {
        INIT_SHADER(tescShader, tescSuccess, shaderPath + ".tesc", GL_TESS_CONTROL_SHADER)
    }

    glLinkProgram(m_RendererId); // Link this program with shaders to the pipeline.
    glValidateProgram(m_RendererId); // Validates our code of the program

    if (vertSuccess) glDeleteShader(vertShader.getId());
    if (fragSuccess) glDeleteShader(fragShader.getId());
    if (geomSuccess) glDeleteShader(geomShader.getId());
    if (tescSuccess) glDeleteShader(tescShader.getId());
    if (teseSuccess) glDeleteShader(teseShader.getId());

    std::cout << "--------------------------------------------------------" << std::endl;
}


Program::~Program()
{
    glDeleteProgram(m_RendererId);
}

int Program::GetUniformLocation(const std::string& uName)
{
    if (uniformLocationsCache.find(uName) != uniformLocationsCache.end())
        return uniformLocationsCache[uName];

    int location = glGetUniformLocation(m_RendererId, uName.c_str());

    /*
     * If the uniform in the shader is unused, it can be stripped from the shader when it compiles.
     * That's why we need to check if it's not equal to -1.
     */
    if (location == -1)
        std::cout << "Warning: uniform '" << uName << "\' doesn\'t exist!";

    uniformLocationsCache[uName] = location;
    return location;
}

void Program::Bind() const
{
    // Binds the program
    glUseProgram(m_RendererId);
}

void Program::Unbind() const
{
    // Unbinds the program
    glUseProgram(0);
}

void Program::SetUniformVec4f(const std::string& name, const glm::vec4& vector)
{
    glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}

void Program::SetUniformVec3f(const std::string& name, const glm::vec3& vector)
{
    glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z);
}

void Program::SetUniformVec2f(const std::string& name, const glm::vec2& vector)
{
    glUniform2f(GetUniformLocation(name), vector.x, vector.y);
}

void Program::SetUniformVec2i(const std::string& name, const glm::ivec2& vector)
{
    glUniform2i(GetUniformLocation(name), vector.x, vector.y);
}

void Program::SetUniform1f(const std::string& name, const float& num)
{
    const int location = GetUniformLocation(name);
    glUniform1f(location, num);
}

void Program::SetUniform1i(const std::string& name, const int& num)
{
    glUniform1i(GetUniformLocation(name), num);
}

void Program::SetUniform1ui(const std::string& name, const unsigned int& num)
{
    glUniform1ui(GetUniformLocation(name), num);
}

void Program::SetUniformMat4fv(const std::string& name, const glm::mat4& mat4)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, false, glm::value_ptr(mat4));
}

void Program::SetUniformMat3(const std::string& name, const glm::mat3& mat4)
{
    glUniformMatrix3fv(GetUniformLocation(name), 1, false, glm::value_ptr(mat4));
}
