#include "Copper/Core/Core.h"
#include "Copper/Core/Log.h"
#include "Copper/Renderer/Buffer.h"
#include "Renderer.h"
#include "RendererAPI.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Copper
{

Ref<VertexBuffer> VertexBuffer::Create(float* data, uint32_t count)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLVertexBuffer>(data, count);

    case RendererAPI::API::None:
        CPR_CORE_ASSERT(false, "RendererAPI::API::None is not valid render API");
        return nullptr;
    }

    CPR_CORE_ASSERT(false, "Unhandled RendererAPI::API");
    return nullptr;
}

Ref<IndexBuffer> IndexBuffer::Create(uint32_t* data, uint32_t count)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLIndexBuffer>(data, count);

    case RendererAPI::API::None:
        CPR_CORE_ASSERT(false, "RendererAPI::API::None is not valid render API");
        return nullptr;
    }

    CPR_CORE_ASSERT(false, "Unhandled RenderAPI");
    return nullptr;
}

}
