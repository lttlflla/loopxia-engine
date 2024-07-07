#include "loopxia/scene/scene.h"

namespace loopxia
{
    class SceneImpl : public Scene
    {
    public:
        SceneImpl();

        SceneNode* SceneRoot() override;

    private:
        std::unique_ptr<SceneNode> m_root;
    };
}