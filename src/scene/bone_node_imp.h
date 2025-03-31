#include "resource/bone_impl.h
#include "loopxia/scene/bone_node.h"

namespace loopxia
{
    class BoneNodeImpl : public BoneNode
    {
    public:
        BoneNodeImpl();

    private:
        // reference to the bone info
        BoneImpl* m_bone;

    };
}