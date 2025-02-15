#include "loopxia/scene/scene_node.h"
#include "object/transform_impl.h"
#include "object/movable_object_impl.h"

namespace loopxia
{
    class SceneNodeImpl final : public virtual SceneNode, public virtual MovableObjectImpl
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

        SceneNodeImpl(SceneNodeImpl* parent);

        void AttachObject(MovableObject* obj) override;
        void DetachObject(MovableObject* obj) override;

        SceneNode* Parent();
        void SetParent(SceneNode* parent);
        std::unordered_set<SceneNode*> SceneNodeChildren();
        std::vector<MovableObject*> GetAttachedObjects();

    private:
        SceneNodeImpl* m_parent;
        std::vector<MovableObject*> m_objects;
    };

    SceneNode* CreateSceneNode(SceneNode* parent);
}
