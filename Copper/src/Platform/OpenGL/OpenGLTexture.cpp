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

    glGenTextures(1, &m_TextureId);
    glBindTexture(GL_TEXTURE_2D, m_TextureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
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
