#pragma once

#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
//#include <glm/gtx/quaternion.hpp>

namespace loopxia
{
    //class Vector3 : public glm::dvec3
    //{
    //public:
    //    typedef glm::dvec3 glmBaseType;
    //    // inherit constructors
    //    using glmBaseType::glmBaseType;

    //    inline void Normalize();
    //    inline double Length();
    //};

    using Vector2 = glm::vec2;
    using Vector3 = glm::vec3;
    using Vector4 = glm::vec4;
    using Quaternion = glm::qua<float, glm::defaultp>;
    using Matrix4x4 = glm::mat4x4;

    //class Quaternion : public glm::qua<double, glm::defaultp>
    //{
    //public:
    //    typedef glm::qua<double, glm::defaultp> Base;
    //    // inherit constructors
    //    using Base::Base;

    //    Quaternion Inverse();
    //};

    struct Plane
    {
        Vector3 pos;
        Vector3 n;

        bool operator==(const Plane& p2) const;
    };

    namespace math
    {
        Vector3 Normalize(const Vector3& v);
        double Length(const Vector3& v);
        float Dot(const Vector3& v1, const Vector3& v2);
        Vector3 Abs(const Vector3& v);
        Vector3 Rotate(const Vector3& v, const Quaternion& q);
        Quaternion Inverse(const Quaternion& q);
        void OrthogonalizeAxes(Vector3& xAxis, Vector3& yAxis, Vector3& zAxis);
        
        Quaternion QuaternionIdentity();
        Quaternion QuaternionFrom(const Vector3& a, const Vector3& b);
    };
    
}