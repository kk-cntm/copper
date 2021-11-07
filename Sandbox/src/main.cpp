#include "Sandbox.h"
#include "Copper/Log.h"

int main()
{
    Copper::Log::Init();
    
    CPR_WARN("Initialized app");
    CPR_CORE_INFO("Var a = {0}", 5);
    
    Sandbox* sandbox = new Sandbox;
    
    return sandbox->Run();
}
