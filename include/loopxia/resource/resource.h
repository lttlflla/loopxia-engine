#pragma once

#include <string>
#include <memory>
#include "loopxia/object/object.h"

namespace loopxia
{
    class ResourceGroup;

    // abstract resource class. possible resource, texture, mesh, config, json file
    // a resource can belong to multiple groups
    class Resource : public virtual Object, public std::enable_shared_from_this<Resource>
    {
    public:
        virtual ~Resource() = default;

        virtual std::string ToString() const = 0;

        virtual bool IsLoaded() const = 0;

        // load into memory / gpu device. depending on type of resource
        virtual bool Load() = 0;
        virtual void Unload() = 0;

        virtual void AddToResourceGroup(ResourceGroup* pResourceGroup) = 0;
        virtual void RemoveFromResourceGroup(ResourceGroup* pResourceGroup) = 0;

        virtual void RemoveFromAllResourceGroups() = 0;

        // for resource which is loaded from file
        // it is also possible that a resource is dynamically created in-memory without file
        // in the case that resource is unloaded when it does not has a file path, it will be saved to a temporary path
        virtual std::string FilePath() = 0;
    };
}