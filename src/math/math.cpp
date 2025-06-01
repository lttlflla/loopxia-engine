#include "loopxia/math.h"
#include <glm/gtx/vector_angle.hpp>

namespace loopxia
{
    bool Plane::operator==(const Plane& p2) const
    {
        
        return math::Normalize(p2.n) == n && math::Dot(pos - p2.pos, p2.n) == 0;
    }

    namespace math
    {
        Vector3 Normalize(const Vector3& v)
        {
            return glm::normalize(v);
        }

        float Dot(const Vector3& v1, const Vector3& v2)
        {
            return glm::dot<3, float, glm::qualifier::highp>(v1, v2);
        }

        double Length(const Vector3& v)
        {
            return glm::length(v);
        }

        Vector3 Abs(const Vector3& v)
        {
            return glm::abs(v);
        }

        Vector3 Rotate(const Vector3& v, const Quaternion& q)
        {
            // Convert the vector to a quaternion
            Quaternion vectorQuaternion(0, v);

            // Multiply the quaternion representing the vector by the rotation quaternion
            auto rotatedVector = q * vectorQuaternion * glm::conjugate(q);

            // Extract the rotated vector from the resulting quaternion
            return Vector3(rotatedVector.x, rotatedVector.y, rotatedVector.z);
        }

        Quaternion Inverse(const Quaternion& q)
        {
            return glm::inverse(q);
        }

        Vector3 Orthogonalize(const Vector3& a, const Vector3& b) {
            return a - glm::dot(a, b) * b;
        }

        // Function to orthogonalize three axes
        void OrthogonalizeAxes(Vector3& xAxis, Vector3& yAxis, Vector3& zAxis) {
            // Normalize the first axis
            xAxis = Normalize(xAxis);

            // Make the second axis orthogonal to the first
            yAxis = Orthogonalize(yAxis, xAxis);
            yAxis = Normalize(yAxis);

            // Make the third axis orthogonal to the first two
            zAxis = Orthogonalize(zAxis, xAxis);
            zAxis = Orthogonalize(zAxis, yAxis);
            zAxis = Normalize(zAxis);
        }

        Quaternion QuaternionIdentity()
        {
            return Quaternion(1.0, 0.0, 0.0, 0.0);
        }

        Quaternion QuaternionFrom(const Vector3& a, const Vector3& b) {
            glm::vec3 axis = glm::cross(a, b);
            float angle = glm::angle(a, b);
            return glm::angleAxis(angle, glm::normalize(axis));
        }

        Matrix4x4 Inverse(const Matrix4x4& m)
        {
            return glm::inverse(m);
        }
    }
}