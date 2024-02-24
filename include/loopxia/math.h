
#pragma once
#include "vectormath.hpp"

namespace loopxia
{
    namespace math
    {
#ifdef _MSC_VER
        using Vector3 = Vectormath::SSE::Vector3;
        using Vector4 = Vectormath::SSE::Vector4;
        using Point3 = Vectormath::SSE::Point3;
        using Quat = Vectormath::SSE::Quat;
        using Matrix3 = Vectormath::SSE::Matrix3;
        using Matrix4 = Vectormath::SSE::Matrix4;
        using Transform3 = Vectormath::SSE::Transform3;
#else
        using Vector3 = Vectormath::Scalar::Vector3;
        using Vector2 = Vectormath::Scalar::Vector2;
#endif
    }
}