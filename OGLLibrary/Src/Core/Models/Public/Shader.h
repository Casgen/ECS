#pragma once
#include <cstdint>
#include <string>

class Shader
{
    std::string filepath;
    unsigned int rendererId = 0;
    unsigned int type = 0;
    
public:

    Shader() = default;
    
    Shader(const std::string& filename, unsigned int shaderType, bool& result);

    [[nodiscard]] unsigned int getId() const {return rendererId;}

    [[nodiscard]] std::string GetTypeString() const;

private:
    bool CompileShader(uint32_t type, const std::string& source);
};
