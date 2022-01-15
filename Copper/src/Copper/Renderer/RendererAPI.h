#pragma once

#include "Copper/Core.h"
#include "glm/glm.hpp"

namespace Copper
{

class VertexArray;

class RendererAPI
{
public:
    enum class API { None, OpenGL };

public:
    static RendererAPI* Create();

    virtual void SetClearColor(const glm::vec4& color) = 0;
    virtual void Clear() = 0;
    virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

    virtual API GetAPI() = 0;
};

}
