#pragma once

namespace Copper
{

class Shader
{
public:
    virtual ~Shader() {}

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
};

}
