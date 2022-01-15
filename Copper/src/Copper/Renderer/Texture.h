#pragma once

#include "Copper/Core.h"

namespace Copper
{

class Texture
{
public:
    virtual ~Texture() = default;

    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;

    virtual void Bind(uint32_t unit) = 0;
};

class COPPER_API Texture2D : public Texture
{
public:
    virtual ~Texture2D() = default;

    static Ref<Texture2D> Create(const std::string& path);
};

}
