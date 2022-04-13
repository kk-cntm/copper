#include "Sandbox.h"
#include "Sandbox2D.h"

Sandbox::Sandbox()
{
    PushLayer(new Sandbox2D);
}
