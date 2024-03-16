#pragma once

#include "loopxia/scene/game_object.h"

namespace loopxia
{
    namespace impl
    {
        class SceneImpl;
    }

    class Scene
    {
    public:
        Scene();
        ~Scene();

        GameObject* SceneRoot();

    protected:

    private:
        impl::SceneImpl* m_impl;

    };
}
