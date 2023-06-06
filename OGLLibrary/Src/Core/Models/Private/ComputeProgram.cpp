#include "../Public/ComputeProgram.h"

#include <glad/glad.h>
#include <iostream>

#include "../../../Utils/Utils.h"

ComputeProgram::ComputeProgram(const std::string& shaderPath)
{
    m_RendererId = glCreateProgram();
    
    bool compSuccess = false;
    
    Shader computeShader = Shader(shaderPath + ".comp",GL_COMPUTE_SHADER, compSuccess);
    ASSERT(compSuccess);
    if (compSuccess)
    {
        glAttachShader(m_RendererId,computeShader.getId()); // Attach the shader to the program.
        std::cout << "Compute shader.....................OK" << std::endl;
    } else
    {
        std::cout << "Compute Shader.....................ERROR" << std::endl;
    }
    
    glLinkProgram(m_RendererId); // Link this program with shaders to the pipeline.
    glValidateProgram(m_RendererId); // Validates our code of the program

    if (compSuccess) glDeleteShader(computeShader.getId());

    std::cout << "--------------------------------------------------------" << std::endl;
}
