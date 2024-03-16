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

    using Vector3 = glm::dvec3;
    using Vector4 = glm::dvec4;
    using Quaternion = glm::qua<double, glm::defaultp>;

    //class Quaternion : public glm::qua<double, glm::defaultp>
    //{
    //public:
    //    typedef glm::qua<double, glm::defaultp> Base;
    //    // inherit constructors
    //    using Base::Base;

    //    Quaternion Inverse();
    //};

    namespace math
    {
        Vector3 Normalize(const Vector3& v);
        double Length(const Vector3& v);
        Vector3 Abs(const Vector3& v);
        Vector3 Rotate(const Vector3& v, const Quaternion& q);
        Quaternion Inverse(const Quaternion& q);
        void OrthogonalizeAxes(Vector3& xAxis, Vector3& yAxis, Vector3& zAxis);
        
        Quaternion QuaternionIdentity();
        Quaternion QuaternionFrom(const Vector3& a, const Vector3& b);
    };
    
}