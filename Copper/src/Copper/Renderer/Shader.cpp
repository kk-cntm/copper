#include "Shader.h"

namespace Copper
{

static std::string GetFileName(const std::string& filepath)
{
    int lastSlashPos = filepath.find_last_of("/\\");
    int lastDotPos = filepath.find_last_of(".");

    int begin = lastSlashPos == std::string::npos ? 0 : lastSlashPos + 1;
    int end = lastDotPos == std::string::npos ? filepath.size() : lastDotPos;

    return filepath.substr(begin, end - begin);
}

Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
{
    return Load(GetFileName(filepath), filepath);
}

Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
{
    Ref<Shader> shader = Shader::Create(filepath);
    Add(name, shader);
    return shader;
}

Ref<Shader> ShaderLibrary::Get(const std::string& name)
{
    CPR_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Invalid shader name: {0}", name);
    return m_Shaders.at(name);
}

void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
{
    CPR_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Already exist: {0}", name);
    m_Shaders[name] = shader;
}

}
