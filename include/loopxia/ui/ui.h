#pragma once

#include "loopxia/math.h"
#include <string>

namespace loopxia
{
    namespace impl
    {
        class WindowImpl;
        class UIImpl;
        class LayoutImpl;
    }

    class UI
    {
    public:
        virtual ~UI() {};
        virtual void Show() = 0;
        virtual void Hide() = 0;
        //virtual void SetPosition() = 0;
        // virtual UI* Parent() = 0;
    };

    class Layout
    {
    public:
        virtual void ReadLayout() = 0;
        virtual void DoLayout() = 0;
    };

    class Window : public UI
    {
        friend class impl::WindowImpl;
    public:
        Window(const std::string& title = "");
        ~Window();

        void* GetNativeHandle();

        virtual void Show() override;
        virtual void Hide() override;
        virtual void DetachContext();
        virtual void MakeCurrentContext();

        void Swap();

    protected:
        impl::WindowImpl* m_impl;
    };

    class Button : public UI
    {

    };

    class Image : public UI
    {

    };

    class Label : public UI
    {

    };

    Window* CreateUIWindow(const std::string& title);
}