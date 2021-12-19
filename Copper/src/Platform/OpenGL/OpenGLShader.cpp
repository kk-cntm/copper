#include "OpenGLShader.h"
#include "Copper/Log.h"
#include "glad/glad.h"

namespace Copper
{

OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    GLuint vertexId = CompileShader(GL_VERTEX_SHADER, vertexSrc);
    GLuint fragmentId = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    m_ProgramId = glCreateProgram();
    glAttachShader(m_ProgramId, vertexId);
    glAttachShader(m_ProgramId, fragmentId);
    glLinkProgram(m_ProgramId);

    GLint isLinked;
    glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &isLinked);

    if (isLinked == GL_FALSE)
    {
        GLint msgLength;
        glGetProgramiv(m_ProgramId, GL_INFO_LOG_LENGTH, &msgLength);

        std::vector<GLchar> msg(msgLength);
        glGetProgramInfoLog(m_ProgramId, msgLength, &msgLength, &msg[0]);

        glDeleteProgram(m_ProgramId);

        CPR_CORE_ASSERT(false, &msg[0]);
    }
}

OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(m_ProgramId);
}

void OpenGLShader::Bind() const
{
    glUseProgram(m_ProgramId);
}

void OpenGLShader::Unbind() const
{
    glUseProgram(0);
}

GLuint OpenGLShader::CompileShader(GLenum type, const std::string& src)
{
    GLuint id = glCreateShader(type);

    const GLchar* parsedSrc = static_cast<const GLchar*>(src.c_str());
    glShaderSource(id, 1, &parsedSrc, nullptr);
    glCompileShader(id);

    GLint isCompiled;
    glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);

    if (isCompiled == GL_FALSE)
    {
        GLint msgLength;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &msgLength);

        std::vector<GLchar> msg(msgLength);
        glGetShaderInfoLog(id, msgLength, &msgLength, &msg[0]);

        glDeleteShader(id);

        CPR_CORE_ASSERT(false, &msg[0]);
    }

    return id;
}

}
