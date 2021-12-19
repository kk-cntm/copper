#include "Shader.h"
#include "Renderer.h"
#include "cprpch.h"
#include "Log.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Copper
{

Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    switch (Renderer::GetAPI()) {
    case RenderAPI::OpenGL:
        return new OpenGLShader(vertexSrc, fragmentSrc);

    case RenderAPI::None:
        CPR_CORE_ASSERT(false, "RenderAPI::None is not valid render API");
        return nullptr;
    }

    CPR_CORE_ASSERT(false, "Unhandled RenderAPI");
    return nullptr;
}

}
