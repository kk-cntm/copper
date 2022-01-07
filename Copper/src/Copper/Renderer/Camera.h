#pragma once

#include "glm/glm.hpp"

namespace Copper
{

class Camera
{
public:
    virtual const glm::mat4& GetVPMatrix() const = 0;
};

}
