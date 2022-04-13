#pragma once

#include "Copper/Core/Layer.h"
#include "Copper/Core/Timestep.h"
#include "Copper/Core/Core.h"
#include "Copper/Renderer/Shader.h"
#include "Copper/Renderer/Buffer.h"
#include "Copper/Renderer/VertexArray.h"
#include "Copper/Renderer/Texture.h"
#include "Copper/OrthoCameraController.h"
#include "Copper/Event/KeyEvent.h"

class Sandbox2D : public Copper::Layer
{
public:
 Sandbox2D();

    virtual void OnEvent(Copper::Event& event) override;
    virtual void OnUpdate(Copper::Timestep ts) override;
    virtual void OnImGuiUpdate() override;

private:
    Copper::Ref<Copper::OrthoCameraController> m_CameraController;

    Copper::ShaderLibrary m_ShaderLibrary;
    Copper::Ref<Copper::Shader> m_FlatColorShader;
    Copper::Ref<Copper::VertexArray> m_VertexArray;

    glm::vec4 m_Color = { 0.0f, 0.0f, 0.0f, 1.0f };
};
