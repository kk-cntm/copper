#pragma once

namespace Copper
{

class Application
{
public:
    Application() = default;
    virtual ~Application() = default;
    
    int Run();
};

}
