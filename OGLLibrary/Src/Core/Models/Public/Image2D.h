#pragma once
#include <glad/glad.h>
#include <string>


class Image2D
{
public:
    Image2D() : m_RendererId(0), m_Width(0), m_Height(0), m_BPP(0) {}
    Image2D(const int& format, const unsigned int& width, const unsigned int& height,
        const unsigned int& interpolation = GL_LINEAR);
    Image2D(const std::string& file_path, const unsigned int& format);
    ~Image2D();

    void Bind(unsigned int slot = 0) const;
    void BindAsTexture(unsigned int slot = 0) const;
    void Unbind() const;

    [[nodiscard]] int getWidth() const
    {
        return m_Width;
    }

    [[nodiscard]] int getHeight() const
    {
        return m_Height;
    }

private:
    
    unsigned int m_RendererId;
    std::string m_FilePath;
    int m_Width, m_Height, m_BPP; //BBP - bits per pixel
    int m_Format;   
};
