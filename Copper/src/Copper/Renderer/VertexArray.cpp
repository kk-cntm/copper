#include "VertexArray.h"
#include "Renderer.h"
#include "Copper/Log.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Copper
{

VertexArray* VertexArray::Create()
{
    switch (Renderer::GetAPI()) {
    case RenderAPI::OpenGL:
        return new OpenGLVertexArray;

    case RenderAPI::None:
        CPR_CORE_ASSERT(false, "RenderAPI::None is not valid render API");
        return nullptr;
    }

    CPR_CORE_ASSERT(false, "Unhandled RenderAPI");
    return nullptr;
}

}
