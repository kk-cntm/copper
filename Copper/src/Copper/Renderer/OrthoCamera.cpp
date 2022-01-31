#include "OrthoCamera.h"

namespace Copper
{

OrthoCamera::OrthoCamera(float left, float right, float bottom, float top)
    : m_ViewMatrix(1.0f),
      m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
      m_ViewProjectMatrix(1.0f),
      m_Position(0.0f),
      m_Rotation(0.0f)
{
    RecalculateViewMatrix();
}

void OrthoCamera::SetPosition(const glm::vec3& position)
{
    m_Position = position;
    RecalculateViewMatrix();
}

void OrthoCamera::SetRotation(float rotation)
{
    m_Rotation = rotation;
    RecalculateViewMatrix();
}

void OrthoCamera::SetProjection(float left, float right, float bottom, float top)
{
    m_ProjectionMatrix = glm::ortho(left, right, bottom, top);
    m_ViewProjectMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

void OrthoCamera::RecalculateViewMatrix()
{
    glm::mat4 transform(1.0f);
    transform = glm::translate(transform, m_Position);
    transform = glm::rotate(transform, glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

    m_ViewMatrix = glm::inverse(transform);
    m_ViewProjectMatrix = m_ProjectionMatrix * m_ViewMatrix;
}

}
