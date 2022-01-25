#pragma once

#include "Copper/Core.h"
#include "glm/glm.hpp"

namespace Copper
{

class COPPER_API Shader
{
public:
    virtual ~Shader() {}

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void SetUniform(const std::string& name, const glm::mat4& mat4) = 0;

    static Ref<Shader> Create(const std::string& filepath);
    static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
};

}
