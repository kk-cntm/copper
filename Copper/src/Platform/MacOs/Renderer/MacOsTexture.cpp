#include "Copper/Core/Core.h"
#include "Copper/Core/Log.h"
#include "Copper/Renderer/Texture.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "Renderer.h"
#include "RendererAPI.h"

namespace Copper
{

Ref<Texture2D> Texture2D::Create(const std::string& path)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLTexture2D>(path);

    case RendererAPI::API::None:
        CPR_CORE_ASSERT(false, "RendererAPI::API::None is not valid render API");
        return nullptr;
    }

    CPR_CORE_ASSERT(false, "Unsupported Renderer API");
    return nullptr;
}

}
