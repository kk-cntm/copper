#pragma once

#include "Copper/Layer.h"

class ExampleLayer : public Copper::Layer
{
public:
    ExampleLayer()
        : Copper::Layer("ExampleLayer") {};

    virtual void OnEvent(Copper::Event& event) override;
    virtual void OnUpdate() override;
    virtual void OnImGuiUpdate() override;
};
