#pragma once

#include "Copper/Renderer/VertexArray.h"
#include "Copper/Renderer/ShaderData.h"
#include "Copper/Core/Core.h"
#include "glad/glad.h"

namespace Copper
{

class OpenGLVertexArray : public VertexArray
{
public:
    OpenGLVertexArray();
    virtual ~OpenGLVertexArray();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void AddVertexBuffer(const Ref<VertexBuffer>& buffer) override;
    virtual void SetIndexBuffer(const Ref<IndexBuffer>& buffer) override;

    virtual const Ref<IndexBuffer>& GetIndexBuffer() const override
    {
        return m_IndexBuffer;
    };

private:
    static GLenum GetOpenGLDataType(ShaderData::Type type);

    uint32_t m_VertexArrayId;
    std::vector<Ref<VertexBuffer>> m_VertexBuffers;
    Ref<IndexBuffer> m_IndexBuffer;
};

}
