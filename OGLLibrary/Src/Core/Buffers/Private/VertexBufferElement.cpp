#include <glad/glad.h>

#include "../Public/VertexBufferElement.h"
#include "../../../Utils/Utils.h"

unsigned int VertexBufferElement::getSizeOfType(unsigned int type)
{
    switch (type)
    {
    case GL_FLOAT: return 4;
    case GL_UNSIGNED_INT: return 4;
    case GL_UNSIGNED_BYTE: return 1;
    }
    ASSERT(false);
    return 0;
}
