#pragma once

#include "RendererAPI.h"
#include "glm/glm.hpp"

namespace Copper
{

class RenderCommand
{
public:
    // implemented in Platform specific dirs
    static void Init();

    inline static void SetClearColor(const glm::vec4& color)
    {
        s_RendererAPI->SetClearColor(color);
    }

    inline static void Clear()
    {
        s_RendererAPI->Clear();
    }

    static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);

    inline static RendererAPI::API GetAPI() { return s_RendererAPI->GetAPI(); }

private:
    static RendererAPI* s_RendererAPI;
};

}