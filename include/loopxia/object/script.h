#include "loopxia/object/object.h"
#include <chrono>
#include <vector>

namespace loopxia
{
    class Script : Object
    {
        protected std::vector<ScriptAction> _scriptActions;
        public void ScriptRun(GameTime gameTime)
        {
            foreach(var script in _scriptActions)
            {
                script.Update(gameTime);
            }
        }
    }
}