#pragma once

#include "Copper/Core/Core.h"
#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Copper
{

class COPPER_API OrthoCamera : public Camera
{
public:
    OrthoCamera(float left, float right, float bottom, float top);

    inline virtual const glm::mat4& GetVPMatrix() const override
    {
        return m_ViewProjectMatrix;
    }
    inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
    inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

    void SetPosition(const glm::vec3& position);
    inline const glm::vec3& GetPosition() const { return m_Position; };

    void SetRotation(float rotation);
    inline float GetRotation() const { return m_Rotation; };

    void SetProjection(float left, float right, float bottom, float top);

private:
    void RecalculateViewMatrix();

    float m_Rotation;
    glm::vec3 m_Position;
    glm::mat4 m_ViewMatrix;
    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewProjectMatrix;
};

}
