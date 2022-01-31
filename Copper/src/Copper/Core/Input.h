#pragma once

namespace Copper
{

class Input
{
public:
    virtual ~Input() {};
    virtual bool IsKeyPressed(int key) const = 0;
    virtual bool IsMouseButtonPressed(int button) const = 0;
    virtual std::pair<float, float> GetMousePos() const = 0;
};

}
