#pragma once

#include "VertexArray.h"
#include "RendererAPI.h"
#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"
#include "glm/glm.hpp"

namespace Copper
{

struct RenderEntity
{
    std::shared_ptr<VertexArray> vertexArray;
    std::shared_ptr<Shader> shader;
};

class Renderer
{
public:
    static void BeginScene(const std::shared_ptr<Camera>& camera);
    static void EndScene();

    static void Submit(const RenderEntity& entity);

    inline static RendererAPI::API GetAPI() { return RenderCommand::GetAPI(); }

private:
    struct SceneData
    {
        glm::mat4 ViewProjectMatrix;
    };

    static SceneData* s_SceneData;
};

}
