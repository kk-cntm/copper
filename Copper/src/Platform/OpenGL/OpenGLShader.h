#pragma once

#include "Copper/Core.h"
#include "Copper/Renderer/Shader.h"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

namespace Copper
{

class CPR_API OpenGLShader : public Shader
{
public:
    OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~OpenGLShader();

    virtual void Bind() const override;
    virtual void Unbind() const override;

    inline virtual void SetUniform(const std::string& name, const glm::mat4& mat4) override
    {
        glUniformMatrix4fv(glGetUniformLocation(m_ProgramId, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat4));
    }

private:
    GLuint CompileShader(GLenum type, const std::string& src);

    uint32_t m_ProgramId;
};

}
