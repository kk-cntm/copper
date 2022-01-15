#include "Copper/Core.h"
#include "Copper/Renderer/Shader.h"
#include "Copper/Renderer/Renderer.h"
#include "Copper/Renderer/RendererAPI.h"
#include "Copper/Log.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Copper
{

Ref<Shader> Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);

    case RendererAPI::API::None:
        CPR_CORE_ASSERT(false, "RendererAPI::API::None is not valid render API");
        return nullptr;
    }

    CPR_CORE_ASSERT(false, "Unhandled RendererAPI::API");
    return nullptr;
}

}
