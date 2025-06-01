#pragma once

#include "loopxia/resource/bone.h"

namespace loopxia
{
    class BoneImpl : public virtual Bone
    {
        friend class MeshLoader;
        friend class MeshSaver;

    public:
        void SetName(const std::string& name) override;
        void SetOffsetMatrix(Matrix4x4 matrix) override;
        std::string Name() override;
        Matrix4x4 OffsetMatrix() override;
        std::vector<Bone*> Children() override;

    protected:
        Matrix4x4 m_offsetMatrix;
        std::string m_name;

        BoneImpl* m_parent = nullptr;
        std::vector<BoneImpl*> m_children;
    };
}