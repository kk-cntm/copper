#pragma once

#include "Copper/Renderer/Buffer.h"

namespace Copper
{

class OpenGLVertexBuffer : public VertexBuffer
{
public:
    OpenGLVertexBuffer(float* data, uint32_t count);
    virtual ~OpenGLVertexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    inline virtual const BufferLayout& GetLayout() const override
    {
        return m_Layout;
    }

    inline virtual void SetLayout(const BufferLayout& layout) override
    {
        m_Layout = layout;
    }

private:
    uint32_t m_BufferId;
    BufferLayout m_Layout;
};

class OpenGLIndexBuffer : public IndexBuffer
{
public:
    OpenGLIndexBuffer(uint32_t* data, uint32_t count);
    virtual ~OpenGLIndexBuffer();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual uint32_t GetCount() const override;

private:
    uint32_t m_BufferId;
    uint32_t m_Count;
};

}
