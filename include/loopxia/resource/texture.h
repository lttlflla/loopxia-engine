#pragma once

#include <string>
#include "loopxia/resource/resource.h"

namespace loopxia
{
    class Texture : public Resource, public InstanceTracker<Texture>
    {
    public:
        virtual void SetMipMapLevels(int n) = 0;

        // height and width of base mip map level
        virtual int Height() = 0;
        virtual int Width() = 0;
    };
}