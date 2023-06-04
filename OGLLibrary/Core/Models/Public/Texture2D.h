#pragma once
#include <string>

class Texture2D
{
    unsigned int m_RendererId;
    std::string m_FilePath;
    int m_Width, m_Height, m_BPP; //BBP - bits per pixel
    
public:

    Texture2D() : m_RendererId(0), m_Width(0), m_Height(0), m_BPP(0) {}
    Texture2D(const std::string& filePath);
    ~Texture2D();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    [[nodiscard]] int GetWidth() const
    {
        return m_Width;
    }

    [[nodiscard]] int GetHeight() const
    {
        return m_Height;
    }
};
