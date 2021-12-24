#pragma once

#include "Copper/Renderer/VertexArray.h"
#include "Copper/Renderer/ShaderData.h"
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

    virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) override;
    virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) override;

    virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override
    {
        return m_IndexBuffer;
    };

private:
    static GLenum GetOpenGLDataType(ShaderData::Type type);

    uint32_t m_VertexArrayId;
    std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
};

}
