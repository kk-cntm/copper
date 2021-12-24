#include "OpenGLBuffer.h"
#include "glad/glad.h"

namespace Copper
{

OpenGLVertexBuffer::OpenGLVertexBuffer(float* data, uint32_t count)
{
    glGenBuffers(1, &m_BufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, data, GL_STATIC_DRAW);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &m_BufferId);
}

void OpenGLVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
}

void OpenGLVertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* data, uint32_t count)
    : m_Count(count)
{
    glGenBuffers(1, &m_BufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * count, data, GL_STATIC_DRAW);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &m_BufferId);
}

void OpenGLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
}

void OpenGLIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t OpenGLIndexBuffer::GetCount() const
{
    return m_Count;
}

}
