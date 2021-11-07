#pragma once

namespace Copper
{

class Application
{
public:
    Application() = default;
    virtual ~Application() = default;
    
    virtual int Run();
};

// to be implemented by client
Application* CreateApplication();

}
