#include "loopxia_math.h"
#include <string>

namespace loopxia
{
    namespace ui
    {
        class UI
        {
        public:
            virtual void Show() = 0;
            virtual void Hide() = 0;
            virtual void SetPosition() = 0;
            virtual UI* Parent() = 0;
        };

        class Layout
        {
        public:
            virtual void ReadLayout() = 0;
            virtual void Layout() = 0;
        };

        class Window : public UI
        {

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



        void Init();

        Window* CreateWindow(const std::string& title);
        
    }
}