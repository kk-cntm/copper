#pragma once

#include "Copper/Layer.h"
#include "Copper/Renderer/Shader.h"
#include "Copper/Renderer/Buffer.h"
#include "Copper/Renderer/VertexArray.h"
#include "Copper/Renderer/OrthoCamera.h"
#include "Copper/Event/KeyEvent.h"
#include "Copper/Timestep.h"

class ExampleLayer : public Copper::Layer
{
public:
    ExampleLayer();

    virtual void OnEvent(Copper::Event& event) override;
    virtual void OnUpdate(Copper::Timestep ts) override;
    virtual void OnImGuiUpdate() override;

private:
    glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
    float m_CameraMoveSpeed = 0.1f;

    float m_CameraRotation = 0.0f;
    float m_CameraRotationSpeed = 2.0f;

    std::shared_ptr<Copper::Shader> m_Shader;
    std::shared_ptr<Copper::VertexArray> m_VertexArray;
    std::shared_ptr<Copper::OrthoCamera> m_Camera;
};
