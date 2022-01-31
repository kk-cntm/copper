#include "Copper/Core/EntryPoint.h"
#include "Copper/Core/Application.h"
#include "Sandbox.h"

Copper::Application* Copper::CreateApplication()
{
    return new Sandbox;
}
