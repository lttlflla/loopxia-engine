#pragma once

#include "loopxia/scene/game_object.h"
#include <memory>

namespace loopxia
{
    class Editor
    {
    public:
        void Render();

        void SetSelection(std::vector<std::shared_ptr<SceneNode>> gameObjects);
    };
}