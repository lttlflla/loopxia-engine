#pragma once

#include "loopxia/scene/scene_node.h"

namespace loopxia
{
    class Scene
    {
    public:
        virtual ~Scene() = default;

        virtual SceneNode* SceneRoot() = 0;
    };

    Scene* CreateScene();
    Scene* LoadScene(const std::string& sceneFilePath);
    void SaveScene(Scene* scene);
}
