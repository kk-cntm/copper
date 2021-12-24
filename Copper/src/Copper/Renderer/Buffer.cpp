#include "cprpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Copper/Log.h"

namespace Copper
{

VertexBuffer* VertexBuffer::Create(float* data, uint32_t count)
{
    switch (Renderer::GetAPI()) {
    case RenderAPI::OpenGL:
        return new OpenGLVertexBuffer(data, count);

    case RenderAPI::None:
        CPR_CORE_ASSERT(false, "RenderAPI::None is not valid render API");
        return nullptr;
    }

    CPR_CORE_ASSERT(false, "Unhandled RenderAPI");
    return nullptr;
}

IndexBuffer* IndexBuffer::Create(uint32_t* data, uint32_t count)
{
    switch (Renderer::GetAPI()) {
    case RenderAPI::OpenGL:
        return new OpenGLIndexBuffer(data, count);

    case RenderAPI::None:
        CPR_CORE_ASSERT(false, "RenderAPI::None is not valid render API");
        return nullptr;
    }

    CPR_CORE_ASSERT(false, "Unhandled RenderAPI");
    return nullptr;
}

BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements)
    : m_Elements(elements), m_Stride(0)
{
    SetupElementsOffset();
    SetupStride();
}

void BufferLayout::SetupElementsOffset()
{
    uint32_t offset = 0;
    for (auto& element : m_Elements)
    {
        element.Offset = offset;
        offset += element.Size;
    }
}

void BufferLayout::SetupStride()
{
    for (auto& element : m_Elements)
        m_Stride += element.Size;
}

}
