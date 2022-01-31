#include "cprpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Copper/Core/Log.h"

namespace Copper
{

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
