#pragma once

#include "loopxia/object/mesh_object.h"
#include "movable_object_impl.h"

namespace loopxia
{
    class MeshImpl : public virtual Mesh, public virtual MovableObjectImpl
    {
    public:
        void OnParentChange(MovableObject* oldParent, MovableObject* newParent) final
        {
            MovableObjectImpl::OnParentChange(oldParent, newParent);
        }

        loopxia::Transform* Transform() final
        {
            return MovableObjectImpl::Transform();
        }

        EventConnection EventListenParentChange(std::function<bool(MovableObject*, MovableObject*)> func) final
        {
            return MovableObjectImpl::EventListenParentChange(func);
        }

        bool LoadFromFile(const std::string& filePath);

        const std::vector<Vector3>& Vertices() const override;
        const std::vector<Vector3>& Normals() const override;
        const std::vector<Vector2>& UV() const override;
        const std::vector<int>& Indices() const override;
        Material* GetMaterial() const override;

    private:
        std::vector<Vector3> m_vertices;
        std::vector<Vector3> m_normals;
        std::vector<Vector2> m_uvs;
        std::vector<int> m_indices;
        Material* m_material;
    };
}