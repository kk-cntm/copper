#include "Copper/Renderer/RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Copper
{

void RenderCommand::Init()
{
    s_RendererAPI = new OpenGLRendererAPI;
}

}
