#pragma once

#include "Copper/Renderer/RendererAPI.h"

namespace Copper
{

class OpenGLRendererAPI : public RendererAPI
{
public:
    virtual void SetClearColor(const glm::vec4& color) override;
    virtual void Clear() override;
    virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

    inline virtual RendererAPI::API GetAPI() override
    {
        return RendererAPI::API::OpenGL;
    }
};

}
