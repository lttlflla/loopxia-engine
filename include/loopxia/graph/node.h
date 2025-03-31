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
                auto descentants = c->AllDescendantByType();
                childrensOfType.insert(descentants.begin(), descentants.end());
            }
            return childrensOfType;
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
