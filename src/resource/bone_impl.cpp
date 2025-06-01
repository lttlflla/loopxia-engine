#include "resource/bone_impl.h"
#include <algorithm>
#include <iterator>

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

    std::vector<Bone*> BoneImpl::Children()
    {
        std::vector<Bone*> bones;

        bones.reserve(m_children.size());  // Optional, improves performance
        std::transform(m_children.begin(), m_children.end(), std::back_inserter(bones),
            [](BoneImpl* impl) -> Bone* {
                return impl;  // Implicit upcast to Bone*
            });

        return bones;
    }
}