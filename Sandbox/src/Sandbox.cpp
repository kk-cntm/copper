#include "Sandbox.h"
#include "ExampleLayer.h"
#include "Copper/Debug/DebugLayer.h"

Sandbox::Sandbox()
{
    PushLayer(new ExampleLayer);
    PushOverlaye(new Copper::DebugLayer());
}
