#pragma once
#include <string>

class CubeMap
{
    unsigned int m_rendererId = 0;
    
public:
    /**
     * Creates a cube map texture with 6 different faces (Top, Bottom, Left, Front, Right, Back. ONLY SUPPORTS JPG!
     * 
     * @param dirPath - Directory path to the cubemap textures. A naming convention has to followed in order to load
     * the individual textures for the skybox. each texture img has to be named by the face, which texture represents.
     * for ex. top.jpg, right.jpg etc.
     */
    CubeMap(const std::string& dirPath);

    void Bind(const unsigned int& slot = 0) const;
    void Unbind() const;
};
