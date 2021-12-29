#include "RenderCommand.h"
#include "VertexArray.h"
#include "RendererAPI.h"

namespace Copper
{

void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
{
    vertexArray->Bind();
    s_RendererAPI->DrawIndexed(vertexArray);
}

RendererAPI* RenderCommand::s_RendererAPI = nullptr;

}
