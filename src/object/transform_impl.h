#pragma once

#include "loopxia/object/transform.h"
#include "loopxia/object/movable_object.h"

namespace loopxia
{
    class TransformImpl final : public Transform
    {
        template <typename T>
        friend class MovableObjectImpl;

    public:
        TransformImpl(MovableObject* obj);

        // world space position
        inline Vector3 Position() const override;

        // local space position
        inline Vector3 LocalPosition() const override;
        // world space rotation
        inline Quaternion Rotation() const override;

        // local space rotation
        inline Quaternion LocalRotation() const override;

        inline void SetLocalPosition(const Vector3& pos) override;

        inline void Move(Vector3 pos) override;

        // rotate by quaternion (local space)
        inline void Rotate(Quaternion q) override;

        // rotate by euler angles (local space)
        inline void Rotate(Vector3 eulerAngle) override;

        inline void RotateWorldSpace(Vector3 eulerAngle) override;

        // rotate around point x
        inline void RotateAround(Vector3 point, Vector3 axis, float angle) override;

        inline Matrix4x4 GetMatrix() override;

    private:
        inline void _RecomputeTransform();
        void _RecomputeWorldPosition();
        void _RecomputeChildrenTransform();
        inline TransformImpl* _ParentTransform();

    private:
        // world space position and rotation. cached for faster computation
        Vector3 m_position;
        Quaternion m_rotation;

        // local space postion and rotation
        Vector3 m_localPosition;
        Quaternion m_localRotation;

        MovableObject* m_obj;
    };
}