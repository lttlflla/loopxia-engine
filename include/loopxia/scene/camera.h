#include "loopxia/scene/node.h"

namespace loopxia
{
    namespace impl
    {
        class CameraImpl;
    }

    class Camera : public Node
    {
    public:
        void LookAt();

    private:
        impl::CameraImpl* m_impl;
    };
}