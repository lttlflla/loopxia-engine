#pragma once

#include "loopxia/scene/scene.h"
#include "loopxia/scene/scene_node.h"
#include "object/transform_impl.h"
#include "object/movable_object_impl.h"

namespace loopxia
{
    template <class T>
    class SceneNodeImpl : public virtual MovableObjectImpl<T>
    {
    public:
        SceneNodeImpl(SceneNode* parent);

        void AttachObject(Object* obj) override;
        void DetachObject(Object* obj) override;

        std::vector<Object*> GetAttachedObjects();

    private:
        std::vector<Object*> m_objects;

        Scene* m_scene;
    };

    SceneNode* CreateSceneNode(SceneNode* parent);
}
