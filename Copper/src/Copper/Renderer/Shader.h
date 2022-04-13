#pragma once

#include "Copper/Core/Core.h"
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
    virtual void SetUniform(const std::string& name, const glm::vec4& vec4) = 0;

    static Ref<Shader> Create(const std::string& filepath);
    static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
};

class COPPER_API ShaderLibrary
{
public:
    void Add(const std::string& name, const Ref<Shader>& shader);
    Ref<Shader> Get(const std::string& name);
    Ref<Shader> Load(const std::string& filepath);
    Ref<Shader> Load(const std::string& name, const std::string& filepath);

private:
    std::unordered_map<std::string, Ref<Shader>> m_Shaders;
};

}
