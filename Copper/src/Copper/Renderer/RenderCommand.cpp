#include "Copper/Core.h"
#include "RenderCommand.h"
#include "VertexArray.h"
#include "RendererAPI.h"

namespace Copper
{

void RenderCommand::DrawIndexed(const Ref<VertexArray>& vertexArray)
{
    vertexArray->Bind();
    s_RendererAPI->DrawIndexed(vertexArray);
}

RendererAPI* RenderCommand::s_RendererAPI = nullptr;

}
