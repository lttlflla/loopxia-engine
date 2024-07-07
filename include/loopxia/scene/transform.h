#pragma once

#include "loopxia/math.h"

namespace loopxia
{
    // forward declaration
    class SceneNode;

    class Transform
    {
    public:
        virtual ~Transform() = default;

        // world space position
        virtual Vector3 Position() const = 0;

        // local space position
        virtual Vector3 LocalPosition() const = 0;

        // world space rotation
        virtual Quaternion Rotation() const = 0;

        // local space rotation
        virtual Quaternion LocalRotation() const = 0;

        virtual void SetLocalPosition(const Vector3& pos) = 0;

        virtual void Move(Vector3 pos) = 0;

        // rotate by quaternion, local space
        virtual void Rotate(Quaternion q) = 0;

        // rotate by euler angles, local space
        virtual void Rotate(Vector3 eulerAngle) = 0;

        /// <summary>
        /// Rotation reference to world space
        /// </summary>
        /// <param name="eulerAngle"></param>
        virtual void RotateWorldSpace(Vector3 eulerAngle) = 0;

        // rotate around point x
        virtual void RotateAround(Vector3 point, Vector3 axis, float angle) = 0;
    };
}