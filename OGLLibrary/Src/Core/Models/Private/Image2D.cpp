#include "../Public/Image2D.h"
#include <stb_image/stb_image.h>
#include <glad/glad.h>

Image2D::Image2D(const std::string& file_path, const unsigned int& format)
    : m_FilePath(file_path), m_Format(format)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char* localBuffer = stbi_load(file_path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    glGenTextures(1, &m_RendererId);
    glBindTexture(GL_TEXTURE_2D, m_RendererId);

    //What kind of interpolation is applied when a texture on the viewport is represented with a smaller number of pixels than originally
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    //What kind of interpolation is applied when a texture on the viewport is represented with a bigger number of pixels than originally
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /*
     * Set a parameter to tell OpenGL if the texture should be clamped, repeated, repeated and mirrored, etc.
     * This parameter HAS TO BE SET! OTHERWISE IT WON'T WORK AND THE TEXTURE IS BLACK!
     */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0,GL_RGBA,GL_UNSIGNED_BYTE, localBuffer);
    glBindImageTexture(0, m_RendererId, 0, GL_FALSE, 0, GL_READ_WRITE, m_Format);

    if (localBuffer)
        stbi_image_free(localBuffer);
}

Image2D::Image2D(const int& format, const unsigned int& width, const unsigned int& height, const unsigned int& interpolation)
    : m_Width(width), m_Height(height), m_Format(format), m_BPP(0)
{
    stbi_set_flip_vertically_on_load(true);

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &m_RendererId);
    glBindTexture(GL_TEXTURE_2D, m_RendererId);

    //What kind of interpolation is applied when a texture on the viewport is represented with a smaller number of pixels than originally
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, interpolation);

    //What kind of interpolation is applied when a texture on the viewport is represented with a bigger number of pixels than originally
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, interpolation);

    /*
     * Set a parameter to tell OpenGL if the texture should be clamped, repeated, repeated and mirrored, etc.
     * This parameter HAS TO BE SET! OTHERWISE IT WON'T WORK AND THE TEXTURE IS BLACK!
     */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0,GL_RGBA,GL_UNSIGNED_BYTE, nullptr);
    glBindImageTexture(0, m_RendererId, 0, GL_FALSE, 0, GL_READ_WRITE, m_Format);
}

Image2D::~Image2D()
{
    glDeleteTextures(1, &m_RendererId);
}

void Image2D::Bind(unsigned int slot) const
{
    //Here the slot is passed in only as a plain number. You can not use GL_TEXTURE0 (Works as a Binding number)
    glBindImageTexture(slot, m_RendererId, 0, GL_FALSE, 0, GL_READ_WRITE, m_Format);
}

void Image2D::BindAsTexture(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererId);
}

void Image2D::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
