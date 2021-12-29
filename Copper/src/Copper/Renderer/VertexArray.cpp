#include "VertexArray.h"
#include "Renderer.h"
#include "RendererAPI.h"
#include "Copper/Log.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Copper
{

VertexArray* VertexArray::Create()
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return new OpenGLVertexArray;

    case RendererAPI::API::None:
        CPR_CORE_ASSERT(false, "RendererAPI::API::None is not valid render API");
        return nullptr;
    }

    CPR_CORE_ASSERT(false, "Unhandled RendererAPI::API");
    return nullptr;
}

}
