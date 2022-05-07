#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

namespace Copper
{

struct Renderer2DStorage
{
    Ref<VertexArray> VertexArray;
    Ref<Shader> TextureShader;
    Ref<Texture> WhiteTexture;
};

Renderer2DStorage* storage;

void Renderer2D::Init()
{
    storage = new Renderer2DStorage;

    storage->TextureShader = Shader::Create("assets/Texture.glsl");
    storage->WhiteTexture = Texture2D::Create(1, 1);

    uint32_t whiteData = 0xFFFFFFFF;
    storage->WhiteTexture->SetData(&whiteData, sizeof(whiteData));

    float vertices[] = { -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                         0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.5f,  0.5f,  0.0f, 1.0f, 1.0f };

    auto vertexBuffer = Copper::VertexBuffer::Create(vertices, sizeof(vertices) / sizeof(float));

    Copper::BufferLayout layout = { { Copper::ShaderData::Type::Float3, "a_Position" },
                                    { Copper::ShaderData::Type::Float2, "a_TexPos" } };

    vertexBuffer->SetLayout(layout);

    uint32_t indices[] = { 0, 1, 2, 0, 2, 3 };
    auto indexBuffer = Copper::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

    storage->VertexArray = Copper::VertexArray::Create();

    storage->VertexArray->AddVertexBuffer(vertexBuffer);
    storage->VertexArray->SetIndexBuffer(indexBuffer);

    storage->TextureShader->Bind();
    storage->TextureShader->SetInt("u_Tex1", 0);
}

void Renderer2D::Shutdown() { delete storage; }

void Renderer2D::BeginScene(const Ref<Copper::OrthoCamera>& camera)
{
    storage->TextureShader->Bind();
    storage->TextureShader->SetMat4("u_ViewProjectionMatrix", camera->GetVPMatrix());
}

void Renderer2D::EndScene() {}

void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
{
    DrawQuad({ pos.x, pos.y, 0.0f }, size, color);
}

void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
{
    storage->TextureShader->Bind();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
                          * /* rotation */ glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    storage->TextureShader->SetMat4("u_TransformMatrix", transform);
    storage->TextureShader->SetVec4("u_Color", color);

    storage->WhiteTexture->Bind(0);

    RenderCommand::DrawIndexed(storage->VertexArray);
}

void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const Ref<Texture>& tex)
{
    DrawQuad({ pos.x, pos.y, 0.0f }, size, tex);
}

void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture>& tex)
{
    storage->TextureShader->Bind();

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
                          * /* rotation */ glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    storage->TextureShader->SetMat4("u_TransformMatrix", transform);
    storage->TextureShader->SetVec4("u_Color", glm::vec4(1.0f));

    tex->Bind(0);

    RenderCommand::DrawIndexed(storage->VertexArray);
}

} // namespace Copper
