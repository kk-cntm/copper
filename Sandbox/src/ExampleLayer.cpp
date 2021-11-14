#include "ExampleLayer.h"
#include "Copper/Log.h"

void ExampleLayer::OnEvent(Copper::Event& event)
{
    CPR_TRACE(event);
}

void ExampleLayer::OnUpdate()
{
    CPR_INFO("ExampleLayer::OnUpdate");
}
