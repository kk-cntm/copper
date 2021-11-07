#include "Copper/EntryPoint.h"
#include "Copper/Application.h"
#include "Sandbox.h"

Copper::Application* Copper::CreateApplication()
{
    return new Sandbox;
}
