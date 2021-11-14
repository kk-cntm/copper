#pragma once

#include "Copper/Layer.h"

class ExampleLayer : public Copper::Layer
{
public:
    ExampleLayer()
        : Copper::Layer("ExampleLayer") {};

    void OnEvent(Copper::Event& event) override;
    void OnUpdate() override;
};
