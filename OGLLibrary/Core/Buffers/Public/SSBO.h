#pragma once

class SSBO
{

    unsigned int m_RendererId = 0;
    
public:

    SSBO() = default;
    SSBO(const void* data, const unsigned int& size);

    void Bind() const;
    void Unbind() const;
    void BindBase(const unsigned int& Binding) const;
};
