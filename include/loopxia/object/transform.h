#pragma once

#include "loopxia/math.h"

using namespace loopxia::math;

namespace loopxia
{
    namespace impl
    {
        class TransformImpl;
        class GameObjectImpl;
    }

    // forward declaration
    class GameObject;

    class Transform
    {
        friend class impl::TransformImpl;
        friend class impl::GameObjectImpl;

    public:
        Transform(GameObject* obj);
        ~Transform();

        // world space position
        Vector3 Position() const;

        // local space position
        Vector3 LocalPositoin() const;

        // world space rotation
        Quaternion Rotation() const;

        // local space rotation
        Quaternion LocalRotation() const;

        void SetLocalPosition(const Vector3& pos);

        void Move(Vector3 pos);

        // rotate by quaternion, local space
        void Rotate(Quaternion q);

        // rotate by euler angles, local space
        void Rotate(Vector3 eulerAngle);

        /// <summary>
        /// Rotation reference to world space
        /// </summary>
        /// <param name="eulerAngle"></param>
        void RotateWorldSpace(Vector3 eulerAngle);

        // rotate around point x
        void RotateAround(Vector3 point, Vector3 axis, float angle);

    protected:
        void _RecomputeTransform();

    protected:
        impl::TransformImpl* m_impl;
    };
}