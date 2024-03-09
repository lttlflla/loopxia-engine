#include "loopxia/object/transform.h"
#include "loopxia/object/gameobject.h"

namespace loopxia
{
    namespace impl
    {
        class TransformImpl
        {
            friend class Transform;
        public:
            TransformImpl(GameObject* obj) : m_obj(obj)
            {
            }

            // world space position
            inline Vector3 Position() const
            {
                return m_position;
            }

            // local space position
            inline Vector3 LocalPosition() const
            {
                return m_localPosition;
            }

            // world space rotation
            inline Quaternion Rotation() const
            {
                return m_rotation;
            }

            // local space rotation
            inline Quaternion LocalRotation() const
            {
                return m_localRotation;
            }

            inline void SetLocalPosition(const Vector3& pos)
            {
                m_localPosition = pos;
                _RecomputeWorldPosition();
            }

            inline void Move(Vector3 pos)
            {
                m_localPosition += pos;
                _RecomputeWorldPosition();
            }

            // rotate by quaternion (local space)
            inline void Rotate(Quaternion q)
            {
                m_localRotation *= q;

                // recompute children
                _RecomputeChildrenTransform();
            }

            // rotate by euler angles (local space)
            inline void Rotate(Vector3 eulerAngle)
            {
                Rotate(Quaternion(eulerAngle));
            }

            inline void RotateWorldSpace(Vector3 eulerAngle)
            {
                _RecomputeChildrenTransform();
            }

            // rotate around point x
            inline void RotateAround(Vector3 point, Vector3 axis, float angle)
            {
                _RecomputeChildrenTransform();
            }

        private:
            inline void _RecomputeTransform()
            {
                auto parent = m_obj->Parent();
                if (!parent) {
                    return;
                }

                m_position = parent->Transform().Position() + (parent->Transform().Rotation() * m_localPosition);
                m_rotation = parent->Transform().Rotation() * m_localRotation;

                _RecomputeChildrenTransform();
            }

            void _RecomputeWorldPosition()
            {
                auto parent = m_obj->Parent();
                if (!parent) {
                    return;
                }

                m_position = parent->Transform().Position() + (parent->Transform().Rotation() * m_localPosition);
                    
                _RecomputeChildrenTransform();
            }

            void _RecomputeChildrenTransform()
            {
                // depth first update
                for (auto& child : m_obj->Children()) {
                    child->Transform().m_impl->_RecomputeTransform();
                }
            }

        private:
            // world space position and rotation. cached for faster computation
            Vector3 m_position;
            Quaternion m_rotation;

            // local space postion and rotation
            Vector3 m_localPosition;
            Quaternion m_localRotation;

            GameObject* m_obj;
        };
    }

    Transform::Transform(GameObject* obj)
    {
        m_impl = new impl::TransformImpl(obj);
    }

    Transform::~Transform()
    {
        delete m_impl;
    }

    // world space position
    Vector3 Transform::Position() const
    {
        return m_impl->Position();
    }

    // local space position
    Vector3 Transform::LocalPositoin() const
    {
        return m_impl->LocalPosition();
    }

    // world space rotation
    Quaternion Transform::Rotation() const
    {
        return m_impl->Rotation();
    }

    // local space rotation
    Quaternion Transform::LocalRotation() const
    {
        return m_impl->LocalRotation();
    }

    void Transform::SetLocalPosition(const Vector3& pos)
    {
        m_impl->SetLocalPosition(pos);
    }

    void Transform::Move(Vector3 pos)
    {
        m_impl->Move(pos);
    }

    void Transform::Rotate(Quaternion q)
    {
        m_impl->Rotate(q);
    }

    // rotate by euler angles
    void Transform::Rotate(Vector3 eulerAngles)
    {
        m_impl->Rotate(eulerAngles);
    }

    void Transform::RotateWorldSpace(Vector3 eulerAngles)
    {
        m_impl->RotateWorldSpace(eulerAngles);
    }

    // rotate around point x
    void Transform::RotateAround(Vector3 point, Vector3 axis, float angle)
    {
        m_impl->RotateAround(point, axis, angle);
    }

    void Transform::_RecomputeTransform()
    {
        m_impl->_RecomputeTransform();
    }
}