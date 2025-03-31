#pragma once

#include <string>
#include "loopxia/object/object.h"
#include "resource_group.h"

namespace loopxia
{
    // abstract resource class. possible resource, texture, mesh, config, json file
    // a resource can belong to multiple groups
    class Resource : public Object
    {
    public:
        virtual ~Resource() = default;

        virtual std::string ToString() = 0;
        virtual bool IsLoaded() = 0;
        virtual void Unload() = 0;

        virtual void AddToResourceGroup(ResourceGroup* pResourceGroup) = 0;
        virtual void RemoveFromResourceGroup(ResourceGroup* pResourceGroup) = 0;

        virtual void RemoveFromAllResourceGroups() = 0;
    };
}