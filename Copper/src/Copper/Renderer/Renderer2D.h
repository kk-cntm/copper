#pragma once

#include "OrthoCamera.h"
#include "Texture.h"

#include <glm/glm.hpp>

namespace Copper
{

class COPPER_API Renderer2D
{
public:
    static void Init();
    static void Shutdown();

    static void BeginScene(const Ref<OrthoCamera>& camera);
    static void EndScene();

    // primitives
    static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
    static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);
    static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture>& tex);
    static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture>& tex);
};

} // namespace Copper
