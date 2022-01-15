#pragma once

#include "RendererAPI.h"
#include "glm/glm.hpp"

namespace Copper
{

class COPPER_API RenderCommand
{
public:
    static void Init();

    inline static void SetClearColor(const glm::vec4& color)
    {
        s_RendererAPI->SetClearColor(color);
    }

    inline static void Clear()
    {
        s_RendererAPI->Clear();
    }

    static void DrawIndexed(const Ref<VertexArray>& vertexArray);

    inline static RendererAPI::API GetAPI() { return s_RendererAPI->GetAPI(); }

private:
    static RendererAPI* s_RendererAPI;
};

}
