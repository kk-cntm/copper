#pragma once

#include "Copper/Core.h"
#include "Copper/Renderer/Shader.h"
#include "glad/glad.h"

namespace Copper
{

class CPR_API OpenGLShader : public Shader
{
public:
    OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~OpenGLShader();

    virtual void Bind() const;
    virtual void Unbind() const;

private:
    GLuint CompileShader(GLenum type, const std::string& src);

    uint32_t m_ProgramId;
};

}
