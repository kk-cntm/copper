#include "Copper/Core/Core.h"
#include "Copper/Core/Log.h"
#include "Copper/Renderer/VertexArray.h"
#include "Copper/Renderer/Renderer.h"
#include "Copper/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Copper
{

Ref<VertexArray> VertexArray::Create()
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLVertexArray>();

    case RendererAPI::API::None:
        CPR_CORE_ASSERT(false, "RendererAPI::API::None is not valid render API");
        return nullptr;
    }

    CPR_CORE_ASSERT(false, "Unhandled RendererAPI::API");
    return nullptr;
}

}

