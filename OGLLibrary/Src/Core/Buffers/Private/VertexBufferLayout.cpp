#include "../Public/VertexBufferLayout.h"
#include "glad/glad.h"


template <>
void VertexBufferLayout::push<float>(unsigned int count)
{
  elements.push_back(VertexBufferElement{count, GL_FLOAT, GL_FALSE});
  stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
}

template <>
void VertexBufferLayout::push<unsigned int>(unsigned int count)
{
  elements.push_back(VertexBufferElement{count, GL_UNSIGNED_INT, GL_FALSE});
  stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count;
}

template <>
void VertexBufferLayout::push<unsigned char>(unsigned int count)
{
  elements.push_back(VertexBufferElement{count, GL_UNSIGNED_BYTE, GL_TRUE});
  stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count;
}

unsigned int VertexBufferLayout::getStride() const { return stride; }

std::vector<VertexBufferElement> VertexBufferLayout::VertexBufferLayoutgetElements() const
{
  return elements;
}

template void VertexBufferLayout::push<float>(unsigned int count);
template void VertexBufferLayout::push<unsigned int>(unsigned int count);
template void VertexBufferLayout::push<unsigned char>(unsigned int count);
