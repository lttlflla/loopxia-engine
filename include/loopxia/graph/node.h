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

        virtual void SetParent(T* parent)
        {
            if (m_parent) {
                m_parent->RemoveChild(Downcast());
            }

            m_parent = parent;

            if (parent) {
                m_parent->AddChild(Downcast());
            }
        }

        std::unordered_set<T*> Children()
        {
            return m_children;
        }
        
        template<typename C>
        std::vector<C*> ChildrenByType()
        {
            std::vector<C*> childrensOfType;
            for (auto& c : m_children) {
                if (auto cc = dynamic_cast<C*>(c)) {
                    childrensOfType.push_back(cc);
                }
            }
            return childrensOfType;
        }

        template<typename C>
        std::vector<C*> AllDescendantByType()
        {
            std::vector<C*> childrensOfType;
            for (auto& c : m_children) {
                if (auto cc = dynamic_cast<C*>(c)) {
                    childrensOfType.push_back(cc);
                }
                auto descendants = c->AllDescendantByType<C>();
                childrensOfType.insert(childrensOfType.end(), descendants.begin(), descendants.end());
            }
            return childrensOfType;
        }

    protected:
        T* Downcast()
        {
            return static_cast<T*>(this);
        }

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
