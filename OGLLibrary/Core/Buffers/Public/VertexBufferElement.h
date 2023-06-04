#pragma once

struct VertexBufferElement
{
    unsigned int count;
    unsigned int type;
    unsigned char normalized;

    //This seems a bit unnecessary...could be done better
    static unsigned int getSizeOfType(unsigned int type);
};
