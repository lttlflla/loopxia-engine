#pragma once

#include "loopxia/object/object.h"
#include "loopxia/object/script.h"
#include "loopxia/time.h"

#include <vector>

namespace loopxia
{
    class ScriptableObject : Object
    {
    public:
        void Update(GameTime gameTime);
    };
}