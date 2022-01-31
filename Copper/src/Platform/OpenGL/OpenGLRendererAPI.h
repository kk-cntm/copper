#pragma once

#include "Copper/Renderer/RendererAPI.h"
#include "Copper/Core.h"

namespace Copper
{

class OpenGLRendererAPI : public RendererAPI
{
public:
    OpenGLRendererAPI();

    virtual void SetClearColor(const glm::vec4& color) override;
    virtual void Clear() override;
    virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
    virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;

    inline virtual RendererAPI::API GetAPI() override
    {
        return RendererAPI::API::OpenGL;
    }
};

}
