#pragma once

#include "loopxia/resource/bone.h"

namespace loopxia
{
    class BoneImpl : public virtual Bone
    {
    public:
        void SetName(const std::string& name) override;
        void SetOffsetMatrix(Matrix4x4 matrix) override;
        std::string Name() override;
        Matrix4x4 OffsetMatrix() override;

    protected:
        Matrix4x4 m_offsetMatrix;
        std::string m_name;
    };
}