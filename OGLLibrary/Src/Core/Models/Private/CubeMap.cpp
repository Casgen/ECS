#include "../Public/CubeMap.h"

#include <glad/glad.h>
#include <ios>
#include <iostream>

#include <stb_image/stb_image.h>

CubeMap::CubeMap(const std::string& dirPath)
{
    glGenTextures(1, &m_rendererId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_rendererId);

    std::string faces[6] = {
        "right",
        "left",
        "top",
        "bottom",
        "front",
        "back"
    };

    int width, height, numOfChannels;
    unsigned char* data;
    stbi_set_flip_vertically_on_load(false);
    for (unsigned int i = 0; i < 6; i++)
    {
        const std::string filePath = dirPath + "/" + faces[i] + ".jpg";
        
        data = stbi_load(filePath.c_str(),&width, &height,&numOfChannels, 0);

        if (!data)
        {
            std::cout << "Failed to load a texture at path: " << filePath << std::endl;
            stbi_image_free(data);
            continue;
        }
        
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}


void CubeMap::Bind(const unsigned int& slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_rendererId);
}

void CubeMap::Unbind() const
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
