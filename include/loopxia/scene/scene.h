#pragma once

#include "loopxia/scene/scene_node.h"
#include "loopxia/object/camera.h"
#include "loopxia/time.h"

namespace loopxia
{
    class Scene
    {
    public:
        virtual ~Scene() = default;

        virtual SceneNode* SceneRoot() = 0;
        virtual void Render(const GameTime& gameTime) = 0;
        virtual void SetActiveCamera(Camera* camera) = 0;
        virtual Camera* GetActiveCamera() = 0;
    };

    Scene* CreateScene();
    Scene* LoadScene(const std::string& sceneFilePath);
    void SaveScene(Scene* scene);
}
