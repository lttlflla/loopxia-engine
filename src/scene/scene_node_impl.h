#include "loopxia/scene/scene_node.h"
#include "scene/transform_impl.h"

namespace loopxia
{
    class SceneNodeImpl final : public SceneNode
    {
    public:
        SceneNodeImpl(SceneNodeImpl* parent);

        void OnParentChange(MovableObject*, MovableObject*) override;
        loopxia::Transform* Transform() override;

        void AttachComponent(Component* obj) override;
        void DetachComponent(Component* obj) override;
        std::vector<Component*> GetAttachedComponents() override;

        EventConnection SceneNodeImpl::EventListenParentChange(std::function<void(MovableObject*, MovableObject*)> func)

    private:
        SceneNodeImpl* m_parent;
        loopxia::TransformImpl m_transform;
        std::vector<Component*> m_components;
    };

    SceneNode* CreateSceneNode(SceneNode* parent);
}
