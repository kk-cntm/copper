#include "ExampleLayer.h"
#include "Copper/Log.h"
#include "Copper/Application.h"

void ExampleLayer::OnEvent(Copper::Event& event)
{
    CPR_TRACE(event);
}

void ExampleLayer::OnUpdate()
{
    const Copper::Input& input = Copper::Application::Get().GetWindow().GetInput();
    auto [x, y] = input.GetMousePos();
    CPR_INFO("{0}, {1}", x, y);
}
