#pragma once

#include "Copper/Renderer/Texture.h"
#include "glad/glad.h"

namespace Copper
{

class OpenGLTexture2D : public Texture2D
{
public:
    OpenGLTexture2D(const std::string& path);
    ~OpenGLTexture2D();

    inline virtual uint32_t GetWidth() const override { return m_Width; };
    inline  virtual uint32_t GetHeight() const override { return m_Height; };

    virtual void Bind(uint32_t unit) override;

private:
    std::tuple<GLenum, GLenum> getFormat(int channels);

    uint32_t m_Width;
    uint32_t m_Height;
    uint32_t m_TextureId;
};

}
