#pragma once

namespace Copper
{

enum class RenderAPI
{
    None, OpenGL
};

class Renderer
{
public:
    inline static RenderAPI GetAPI() { return s_RenderAPI; }

private:
    static RenderAPI s_RenderAPI;
};

}
