#pragma once

#include "Copper/Core/Core.h"
#include "Copper/Renderer/Shader.h"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

namespace Copper
{

class CPR_API OpenGLShader : public Shader
{
public:
    OpenGLShader(const std::string& filepath);
    OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~OpenGLShader();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    inline virtual void SetMat4(const std::string& name, const glm::mat4& mat4) override
    {
        glUniformMatrix4fv(glGetUniformLocation(m_ProgramId, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat4));
    }

    inline virtual void SetVec3(const std::string& name, const glm::vec3& vec3) override
    {
        glUniform3fv(glGetUniformLocation(m_ProgramId, name.c_str()), 1, glm::value_ptr(vec3));

    }

    inline virtual void SetVec4(const std::string& name, const glm::vec4& vec4) override
    {
        glUniform4fv(glGetUniformLocation(m_ProgramId, name.c_str()), 1, glm::value_ptr(vec4));
    }

    inline virtual void SetInt(const std::string& name, int value) override
    {
        glUniform1i(glGetUniformLocation(m_ProgramId, name.c_str()), value);
    }

private:
    std::unordered_map<GLenum, std::string> LoadShader(const std::string& filepath);
    GLuint CompileProgram(const std::unordered_map<GLenum, std::string>& sources);
    GLuint CompileShader(GLenum type, const std::string& src);

    uint32_t m_ProgramId;
};

}
