#pragma once

#include "Copper/Core.h"
#include "Copper/Log.h"
#include "ShaderData.h"

namespace Copper
{

struct BufferElement
{
    ShaderData::Type Type;
    std::string Name;
    uint32_t Offset;
    uint32_t Size;
    uint32_t Count;
    bool Normalized;

    BufferElement(ShaderData::Type type, const std::string& name, bool normalized = false)
        : Type(type), Name(name), Normalized(normalized),
          Size(ShaderData::GetSize(type)), Count(ShaderData::GetCount(type)),
          Offset(0) {}
};

class COPPER_API BufferLayout
{
public:
    BufferLayout() {}
    BufferLayout(std::initializer_list<BufferElement> elements);

    inline uint32_t GetStride() const { return m_Stride; };

    inline uint32_t Size() const { return m_Elements.size(); }

    inline std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
    inline std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

    inline std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
    inline std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

private:
    void SetupElementsOffset();
    void SetupStride();

    std::vector<BufferElement> m_Elements;
    uint32_t m_Stride;
};

class COPPER_API VertexBuffer
{
public:
    virtual ~VertexBuffer() {}

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual const BufferLayout& GetLayout() const = 0;
    virtual void SetLayout(const BufferLayout& layout) = 0;

    static Ref<VertexBuffer> Create(float* data, uint32_t count);
};

class COPPER_API IndexBuffer
{
public:
    virtual ~IndexBuffer() {}

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual uint32_t GetCount() const = 0;

    static Ref<IndexBuffer> Create(uint32_t* data, uint32_t count);
};

}
