#pragma once

#include "VertexArray.h"
#include "RendererAPI.h"
#include "RenderCommand.h"
#include "glm/glm.hpp"

namespace Copper
{

class Renderer
{
public:
    static void BeginScene();
    static void EndScene();

    static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

    inline static RendererAPI::API GetAPI() { return RenderCommand::GetAPI(); }
};

}
