#pragma once

#include "loopxia/object/object.h"
#include <unordered_set>

namespace loopxia
{
    template<class T>
    class Node
    {
        typedef Node<T> NodeClass;
    public:
        Node()
        {
        }

        virtual ~Node()
        {
        }

        T* Parent()
        {
            return m_parent;
        }

        void SetParent(T* parent)
        {
            if (m_parent) {
                m_parent->RemoveChild(this);
            }

            auto oldParent = m_parent;
            m_parent = parent;
            m_parent->AddChild(this);

            T::OnParentChange(oldParent, parent);
        }

        std::unordered_set<T*> Children()
        {
            return m_children;
        }

    protected:
        void AddChild(T* obj)
        {
            m_children.insert(obj);
        }

        void RemoveChild(T* obj)
        {
            m_children.erase(obj);
        }

    private:
        T* m_parent = nullptr;
        std::unordered_set<T*> m_children;
    };
}
