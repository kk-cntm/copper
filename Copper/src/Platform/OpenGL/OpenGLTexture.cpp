#include "OpenGLTexture.h"
#include "Copper/Log.h"

#include "stb_image.h"
#include "glad/glad.h"

namespace Copper
{

OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
{
    stbi_set_flip_vertically_on_load(true);
    int width, height, channels;
    stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    stbi_set_flip_vertically_on_load(false);
    CPR_CORE_ASSERT(data, "Failed to load texture " + path);

    m_Width = width;
    m_Height = height;

    auto [internalFormat, dataFormat] = getFormat(channels);

    glGenTextures(1, &m_TextureId);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

std::tuple<GLenum, GLenum> OpenGLTexture2D::getFormat(int channels)
{
    GLenum internalFormat = 0;
    GLenum dataFormat = 0;
    if (channels == 4)
    {
        internalFormat = GL_RGBA8;
        dataFormat = GL_RGBA;
    }
    else if (channels == 3)
    {
        internalFormat = GL_RGB8;
        dataFormat = GL_RGB;
    }

    CPR_CORE_ASSERT(internalFormat & dataFormat, "Unsupported format");

    return { internalFormat, dataFormat };
}

OpenGLTexture2D::~OpenGLTexture2D()
{
    glDeleteTextures(1, &m_TextureId);
}

void OpenGLTexture2D::Bind(uint32_t unit)
{
    glActiveTexture(unit);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);
}

}
