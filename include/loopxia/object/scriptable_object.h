#include "loopxia/object/object.h"
#include "loopxia/object/script.h"
#include "loopxia/time.h"

#include <vector>

namespace loopxia
{
    class ScriptableObject : Object
    {
    public:
        virtual void Update(GameTime gameTime) = 0;

    protected: 
        std::vector<Script> _scripts;
    }

}