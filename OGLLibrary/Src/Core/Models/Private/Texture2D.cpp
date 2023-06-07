#include <glad/glad.h>
#include "../Public/Texture2D.h"
#include <stb_image.h>

Texture2D::Texture2D(const std::string& filePath)
    : m_FilePath(filePath) ,m_Width(0), m_Height(0), m_BPP(0)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char* localBuffer = stbi_load(filePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);
    
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

    glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA8,m_Width,m_Height,0,GL_RGBA,GL_UNSIGNED_BYTE, localBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (localBuffer)
        stbi_image_free(localBuffer);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &m_RendererId);
}

void Texture2D::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_RendererId);
}

void Texture2D::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
