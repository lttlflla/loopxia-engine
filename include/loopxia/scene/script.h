#pragma once

#include "loopxia/object/object.h"
#include "loopxia/time.h"
#include <chrono>
#include <vector>

namespace loopxia
{
    namespace impl
    {
        class ScriptActionImpl;
        class ScriptImpl;
    }

    class ScriptAction
    {
    public:
        ScriptAction();

        void Update(GameTime gameTime);

    protected:
        impl::ScriptActionImpl* m_impl;
    };

    class Script : public Object
    {
    public:
        void ScriptRun(GameTime gameTime);

    protected:
        impl::ScriptImpl* m_impl;
    };
}