#pragma once

#include "loopxia/event.h"
#include "loopxia/time.h"
#include "loopxia/scene/scene.h"
#include "loopxia/input/keyboard.h"
#include "loopxia/scene/scene_transition.h"

namespace loopxia
{
    // predefined events
    struct WindowDetails
    {
        uint32_t windowId;
    };

    struct KeyEvent
    {
        ScanCode scanCode;
        KeyCode keyCode;
        uint16_t modifiers; // see KeyModifier
    };

    class Game
    {
    public:
        enum class EventType
        {
            NONE,
            WINDOW_CLOSE_REQUEST
        };

        // predefined events
        EventSignal<Event&, WindowDetails&> WindowQuitRequest;
        EventSignal<Event&, WindowDetails&, int, int> WindowResize;
        EventSignal<Event&, KeyEvent&> KeyDown;
        EventSignal<Event&, KeyEvent&> KeyUp;
        EventSignal<GameTime&> GameUpdate;

        virtual ~Game() = default;

        virtual void Init() = 0;
        virtual void Run() = 0;

        virtual Scene* CurrentScene() = 0;
        virtual void SetScene(Scene* pNextScene, SceneTransition* sceneTransition) = 0;

        /*
        * Default keys:
        * Esc - quit
        * 
        */
        virtual void SetKeyboardShortcut(std::vector<KeyCode> keys) = 0;
    };

    Game* CreateGame();
}