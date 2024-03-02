#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
//#include <glm/gtx/quaternion.hpp>

namespace loopxia
{
    namespace math
    {
        using Vector3 = glm::dvec3;
        using Quaternion = glm::qua<double, glm::defaultp>;
    }
}