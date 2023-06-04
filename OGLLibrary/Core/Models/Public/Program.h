#pragma once
#include <fwd.hpp>
#include <unordered_map>
#include <xstring>

#include "Shader.h" //It is used...IDE IS LYING


class Program
{
    
public:

    Program(const std::string& shaderName);
    Program() : m_RendererId(0) {}
    ~Program();

    [[nodiscard]] unsigned int getId() const { return m_RendererId;}
    
    int GetUniformLocation(const std::string& uName);

    void Bind() const;
    void Unbind() const;

    // ---------------- GL uniform setters ----------------
    virtual void SetUniformVec4f(const std::string& name, const glm::vec4& vector);
    virtual void SetUniformVec3f(const std::string& name, const glm::vec3& vector);
    virtual void SetUniformVec2f(const std::string& name, const glm::vec2& vector);
    virtual void SetUniform1f(const std::string& name, const float& num);
    virtual void SetUniformVec2i(const std::string& name, const glm::ivec2& vector);
    virtual void SetUniform1i(const std::string& name, const int& num);
    virtual void SetUniform1ui(const std::string& name, const unsigned int& num);
    virtual void SetUniformMat4fv(const std::string& name, const glm::mat4& mat4);
    virtual void SetUniformMat3(const std::string& name, const glm::mat3& mat4);
    
protected:
    unsigned int m_RendererId;
    std::unordered_map<std::string, int> uniformLocationsCache;
};
