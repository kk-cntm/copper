#pragma once

#include "Buffer.h"
#include "Copper/Core.h"

namespace Copper
{

class VertexArray
{
public:
    virtual ~VertexArray() {}

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) = 0;
    virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) = 0;

    virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

    static VertexArray* Create();
};

}
