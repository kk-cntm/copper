#include "OpenGLVertexArray.h"
#include "Copper/Core/Log.h"
#include "glad/glad.h"

namespace Copper
{

OpenGLVertexArray::OpenGLVertexArray()
{
    glGenVertexArrays(1, &m_VertexArrayId);
    glBindVertexArray(m_VertexArrayId);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
    glDeleteVertexArrays(1, &m_VertexArrayId);
}

void OpenGLVertexArray::Bind() const
{
    glBindVertexArray(m_VertexArrayId);
}

void OpenGLVertexArray::Unbind() const
{
    glBindVertexArray(0);
}

void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& buffer)
{
    CPR_CORE_ASSERT(buffer->GetLayout().Size(), "Should set layout before adding buffer to vertex array");

    glBindVertexArray(m_VertexArrayId);
    buffer->Bind();

    uint32_t index = 0;
    for (const auto& element : buffer->GetLayout())
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
            index,
            element.Count,
            GetOpenGLDataType(element.Type),
            element.Normalized ? GL_TRUE : GL_FALSE,
            buffer->GetLayout().GetStride(),
            reinterpret_cast<const void*>(element.Offset));
        ++index;
    }

    m_VertexBuffers.push_back(buffer);
}

void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& buffer)
{
    glBindVertexArray(m_VertexArrayId);
    buffer->Bind();

    m_IndexBuffer = buffer;
}

GLenum OpenGLVertexArray::GetOpenGLDataType(ShaderData::Type type)
{
    switch (type) {
    case ShaderData::Type::Float:    return GL_FLOAT;
    case ShaderData::Type::Float2:   return GL_FLOAT;
    case ShaderData::Type::Float3:   return GL_FLOAT;
    case ShaderData::Type::Float4:   return GL_FLOAT;
    case ShaderData::Type::Int:      return GL_INT;
    case ShaderData::Type::Int2:     return GL_INT;
    case ShaderData::Type::Int3:     return GL_INT;
    case ShaderData::Type::Int4:     return GL_INT;
    case ShaderData::Type::Mat3:     return GL_FLOAT;
    case ShaderData::Type::Mat4:     return GL_FLOAT;
    case ShaderData::Type::Bool:     return GL_BOOL;
    }

    CPR_CORE_ASSERT(false, "Unhandled ShaderData::Type");
    return GL_NONE;
}

}
