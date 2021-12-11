#pragma once

namespace Copper
{

class GraphicContext
{
public:
    virtual ~GraphicContext() {}

    virtual void SwapBuffer() = 0;
};

}
