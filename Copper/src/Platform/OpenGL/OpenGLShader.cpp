#include "OpenGLShader.h"
#include "Copper/Log.h"
#include "glad/glad.h"

namespace Copper
{

OpenGLShader::OpenGLShader(const std::string& filepath)
{
    auto sources = LoadShader(filepath);
    m_ProgramId = CompileProgram(sources);
}

OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
    std::unordered_map<GLenum, std::string> sources;
    sources[GL_VERTEX_SHADER] = vertexSrc;
    sources[GL_FRAGMENT_SHADER] = fragmentSrc;

    m_ProgramId = CompileProgram(sources);
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

GLuint OpenGLShader::CompileProgram(const std::unordered_map<GLenum, std::string>& sources)
{
    static constexpr int maxSupportedShaders = 2;
    CPR_CORE_ASSERT(sources.size() <= maxSupportedShaders, "Unsupported shaders size: {}", sources.size());

    GLuint programId = glCreateProgram();

    // why not std::vector: stack allocation (performance boost)
    std::array<GLuint, maxSupportedShaders> shaders;
    int currentShaderIndex = 0;

    for (auto& [type, src] : sources)
    {
        GLuint id = CompileShader(type, src);

        glAttachShader(programId, id);
        shaders[currentShaderIndex++] = id;
    }

    glLinkProgram(programId);

    GLint isLinked;
    glGetProgramiv(programId, GL_LINK_STATUS, &isLinked);

    if (isLinked == GL_FALSE)
    {
        GLint msgLength;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &msgLength);

        std::vector<GLchar> msg(msgLength);
        glGetProgramInfoLog(programId, msgLength, &msgLength, &msg[0]);

        glDeleteProgram(programId);

        CPR_CORE_ASSERT(false, &msg[0]);
    }

    for (auto id : shaders)
        glDeleteShader(id);

    return programId;
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

static GLenum ConvertShaderStrType(const std::string& type)
{
    if (type == "vertex")
        return GL_VERTEX_SHADER;
    if (type == "fragment" || type == "pixel")
        return GL_FRAGMENT_SHADER;

    return 0;
}

std::unordered_map<GLenum, std::string> OpenGLShader::LoadShader(const std::string& filepath)
{
    std::unordered_map<GLenum, std::string> sources;
    std::ifstream in(filepath, std::ios::in | std::ios::binary);

    if (!in)
        CPR_CORE_ERROR("Failed to open file: {0}", filepath);

    std::string sourceStr;
    in.seekg(0, std::ios::end);
    sourceStr.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&sourceStr[0], sourceStr.size());

    const char* typeToken = "#type";
    size_t typeTokenLen = strlen(typeToken);
    size_t pos = sourceStr.find(typeToken, 0);
    while (pos != std::string::npos)
    {
        size_t eol = sourceStr.find_first_of("\r\n", pos);
        size_t begin = pos + typeTokenLen + 1;
        std::string type = sourceStr.substr(begin, eol - begin);

        CPR_CORE_ASSERT(ConvertShaderStrType(type), "Invalid shader type: {0}", type);

        size_t nextLine = sourceStr.find_first_not_of("\r\n", eol);
        pos = sourceStr.find(typeToken, nextLine);
        sources[ConvertShaderStrType(type)] = sourceStr.substr(nextLine, pos - (nextLine == std::string::npos ? sourceStr.size() - 1 : nextLine));
    }

    return sources;
}

}
