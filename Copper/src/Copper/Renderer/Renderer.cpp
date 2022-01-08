#include "Renderer.h"

namespace Copper
{

Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

void Renderer::BeginScene(const std::shared_ptr<Camera>& camera)
{
    s_SceneData->ViewProjectMatrix = camera->GetVPMatrix();
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const RenderEntity& entity)
{
    entity.shader->Bind();
    entity.shader->SetUniform("u_ViewProjectionMatrix", s_SceneData->ViewProjectMatrix);
    entity.shader->SetUniform("u_TransformMatrix", entity.transform);
    RenderCommand::DrawIndexed(entity.vertexArray);
}

}
