#pragma once

namespace loopxia
{
    class SceneTransition
    {
    public:
        // whether transition is completed
        virtual bool IsCompleted() = 0;

        // start transition
        virtual void Start() = 0;
    };
}