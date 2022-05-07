#include "Copper/Core/Core.h"
#include "Copper/Core/Log.h"
#include "Copper/Renderer/Texture.h"
#include "Platform/OpenGL/OpenGLTexture.h"
#include "Copper/Renderer/Renderer.h"
#include "Copper/Renderer/RendererAPI.h"

namespace Copper
{

Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLTexture2D>(width, height);

    case RendererAPI::API::None:
        CPR_CORE_ASSERT(false, "RendererAPI::API::None is not valid render API");
        return nullptr;
    }

    CPR_CORE_ASSERT(false, "Unsupported Renderer API");
    return nullptr;
}

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
