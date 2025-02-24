#include "object/transform_impl.h"

namespace loopxia
{
    TransformImpl::TransformImpl(MovableObject* obj) : m_obj(obj)
    {
    }

    // world space position
    inline Vector3 TransformImpl::Position() const
    {
        return m_position;
    }

    // local space position
    inline Vector3 TransformImpl::LocalPosition() const
    {
        return m_localPosition;
    }

    // world space rotation
    inline Quaternion TransformImpl::Rotation() const
    {
        return m_rotation;
    }

    // local space rotation
    inline Quaternion TransformImpl::LocalRotation() const
    {
        return m_localRotation;
    }

    inline void TransformImpl::SetLocalPosition(const Vector3& pos)
    {
        m_localPosition = pos;
        _RecomputeWorldPosition();
    }

    inline void TransformImpl::Move(Vector3 pos)
    {
        m_localPosition += pos;
        _RecomputeWorldPosition();
    }

    // rotate by quaternion (local space)
    inline void TransformImpl::Rotate(Quaternion q)
    {
        m_localRotation *= q;

        // recompute children
        _RecomputeChildrenTransform();
    }

    // rotate by euler angles (local space)
    inline void TransformImpl::Rotate(Vector3 eulerAngle)
    {
        Rotate(Quaternion(eulerAngle));
    }

    inline void TransformImpl::RotateWorldSpace(Vector3 eulerAngle)
    {
        _RecomputeChildrenTransform();
    }

    // rotate around point x
    inline void TransformImpl::RotateAround(Vector3 point, Vector3 axis, float angle)
    {
        _RecomputeChildrenTransform();
    }

    inline TransformImpl* TransformImpl::_ParentTransform()
    {
        auto parent = m_obj->Parent();
        if (!parent) {
            return nullptr;
        }


        return static_cast<TransformImpl*>(parent->Transform());
    }

    inline void TransformImpl::_RecomputeTransform()
    {
        auto parentTransform = _ParentTransform();
        if (!parentTransform) {
            return;
        }

        m_position = parentTransform->Position() + (parentTransform->Rotation() * m_localPosition);
        m_rotation = parentTransform->Rotation() * m_localRotation;

        _RecomputeChildrenTransform();
    }

    void TransformImpl::_RecomputeWorldPosition()
    {
        auto parentTransform = _ParentTransform();
        if (!parentTransform) {
            return;
        }

        m_position = parentTransform->Position() + (parentTransform->Rotation() * m_localPosition);
                    
        _RecomputeChildrenTransform();
    }

    void TransformImpl::_RecomputeChildrenTransform()
    {
        // depth first update
        for (auto& child : m_obj->Children()) {
            static_cast<TransformImpl*>(child->Transform())->_RecomputeTransform();
        }
    }
}