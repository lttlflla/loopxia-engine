#include "resource/bone_impl.h"

namespace loopxia
{
    void BoneImpl::SetName(const std::string& name)
    {
        m_name = name;
    }

    void BoneImpl::SetOffsetMatrix(Matrix4x4 matrix)
    {
        m_offsetMatrix = matrix;
    }

    std::string BoneImpl::Name()
    {
        return m_name;
    }

    Matrix4x4 BoneImpl::OffsetMatrix()
    {
        return m_offsetMatrix;
    }
}