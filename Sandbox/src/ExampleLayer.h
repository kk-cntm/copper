#pragma once

#include "Copper/Layer.h"
#include "Copper/Renderer/Shader.h"
#include "Copper/Renderer/Buffer.h"
#include "Copper/Renderer/VertexArray.h"
#include "Copper/Renderer/OrthoCamera.h"

class ExampleLayer : public Copper::Layer
{
public:
    ExampleLayer();

    virtual void OnEvent(Copper::Event& event) override;
    virtual void OnUpdate() override;
    virtual void OnImGuiUpdate() override;

private:
    std::shared_ptr<Copper::Shader> m_Shader;
    std::shared_ptr<Copper::VertexArray> m_VertexArray;
    std::shared_ptr<Copper::OrthoCamera> m_Camera;
};
