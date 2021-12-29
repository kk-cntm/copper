#include "Shader.h"
#include "Renderer.h"
#include "RendererAPI.h"
#include "cprpch.h"
#include "Log.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Copper
{

Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::OpenGL:
        return new OpenGLShader(vertexSrc, fragmentSrc);

    case RendererAPI::API::None:
        CPR_CORE_ASSERT(false, "RendererAPI::API::None is not valid render API");
        return nullptr;
    }

    CPR_CORE_ASSERT(false, "Unhandled RendererAPI::API");
    return nullptr;
}

}
