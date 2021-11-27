#include "ExampleLayer.h"
#include "Copper/Log.h"
#include "Copper/Application.h"

void ExampleLayer::OnEvent(Copper::Event& event)
{
    CPR_TRACE(event);
}

void ExampleLayer::OnUpdate()
{
    auto input = Copper::Application::Get().GetWindow().GetInput();
    CPR_INFO("{0}, {1}", input->GetMousePos().first, input->GetMousePos().second);
}
