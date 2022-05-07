#include "Renderer.h"
#include "Copper/Core/Core.h"
#include "Copper/Core/Application.h"
#include "Renderer2D.h"

namespace Copper
{

void Renderer::Init()
{
    RenderCommand::Init();
    Renderer2D::Init();
}

Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

void Renderer::BeginScene(const Ref<Camera>& camera)
{
    s_SceneData->ViewProjectMatrix = camera->GetVPMatrix();
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const RenderEntity& entity)
{
    if (entity.texture)
        entity.texture->Bind(0);
    entity.shader->Bind();
    entity.shader->SetMat4("u_ViewProjectionMatrix", s_SceneData->ViewProjectMatrix);
    entity.shader->SetMat4("u_TransformMatrix", entity.transform);
    RenderCommand::DrawIndexed(entity.vertexArray);
}

bool Renderer::OnWindowFbResize(WindowFBResizeEvent& e)
{
    RenderCommand::SetViewport(0, 0, e.GetWidth(), e.GetHeight());
    return false;
}

}
