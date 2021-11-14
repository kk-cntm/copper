#include "Sandbox.h"
#include "ExampleLayer.h"

Sandbox::Sandbox()
{
    PushLayer(new ExampleLayer);
}
