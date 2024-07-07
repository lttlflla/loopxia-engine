#include "loopxia/game/game.h"
#include "loopxia/ui/ui.h"
#include "windows.h"
#include <SDL.h>
#include <GL/glew.h>
#include <gl/GL.h>
//#include <GL/glew.h>

using namespace loopxia;
using namespace loopxia::event;

namespace loopxia
{
    class GameImpl : public Game
    {
    public:
        GameImpl()
        {
        }

        ~GameImpl()
        {
        }

        void Init() override
        {
            m_pWindow = CreateUIWindow("Loopxia Game Engine");


            GLenum glewError = glewInit();
            if (glewError != GLEW_OK)
            {
                LogError(std::format("Error initializing GLEW! {}\n", (char*)glewGetErrorString(glewError)));
            }

            auto  resizeFunc = [this](Event& evt, WindowDetails& details, int w, int h) -> bool {
                _resize(w, h);
                return true;
            };

            WindowResize.connect(resizeFunc);

            auto  closeWindowFunc = [this](Event& evt, WindowDetails& details) -> bool {
                m_bCloseWindow = true;
                return true;
            };

            WindowQuitRequest.connect(closeWindowFunc);
        }

        void Run() override
        {
            while (!m_bCloseWindow) {
                while (_PollEvent()) {
                }

                _render();

                if (m_pWindow) {
                    m_pWindow->Swap();
                }
            }
        }

        Scene* CurrentScene() override
        {
            return m_scene;
        }

        void SetScene(Scene* pNextScene, SceneTransition* sceneTransition) override
        {

        }

        void SetKeyboardShortcut(std::vector<KeyCode> keys) override
        {

        }
    private:
        bool _PollEvent()
        {
            Event evt;
            evt.timestamp = std::chrono::steady_clock::now();

            // convert sdl event to loopxia event
            SDL_Event sdlEvt;
            SDL_PollEvent(&sdlEvt);
            switch (sdlEvt.type) {
            case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            {
                WindowDetails details;
                details.windowId = sdlEvt.window.windowID;
                WindowQuitRequest.Signal(evt, details);
                return true;
            }

            case SDL_EVENT_WINDOW_RESIZED:
            {
                WindowDetails details;
                details.windowId = sdlEvt.window.windowID;
                WindowResize.Signal(evt, details, sdlEvt.window.data1, sdlEvt.window.data2);
                return true;
            }

            case SDL_EVENT_KEY_DOWN:
            {
                KeyEvent e;
                e.scanCode = (ScanCode)sdlEvt.key.keysym.scancode;
                e.modifiers = sdlEvt.key.keysym.mod;
                e.keyCode = (KeyCode)sdlEvt.key.keysym.sym;
                KeyDown.Signal(evt, e);
                return true;
            }

            case SDL_EVENT_KEY_UP:
            {
                KeyEvent e;
                e.scanCode = (ScanCode)sdlEvt.key.keysym.scancode;
                e.modifiers = sdlEvt.key.keysym.mod;
                e.keyCode = (KeyCode)sdlEvt.key.keysym.sym;
                KeyUp.Signal(evt, e);
                return true;
            }
            }

            return false;
        }

        void _Update()
        {
            auto timeNow = std::chrono::steady_clock::now();
            auto elapsed = timeNow - m_lastUpdateTime;
            m_lastUpdateTime = timeNow;

            GameTime time;
            time.timestamp = timeNow;
            time.elapsedTimeMs = elapsed;

            GameUpdate.Signal(time);
        }

        void _render()
        {
            //Clear color buffer
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            _Update();

            if (!m_scene) {
                return;
            }

            auto root = m_scene->SceneRoot();

            // cull visible
            // render visible

        }

        void _resize(int width, int height)
        {
            if (height <= 0)    height = 1;

            glViewport(0, 0, (GLsizei)width, (GLsizei)height);

            //glMatrixMode(GL_PROJECTION);
            // glLoadIdentity();
            //gluPerspective(60.0f, float(width) / float(height), 1.0f, 100.0f);

            //glMatrixMode(GL_MODELVIEW);
            //glLoadIdentity();
        }

    private:
        bool m_bCloseWindow = false;
        Window* m_pWindow = nullptr;
        std::chrono::time_point<std::chrono::steady_clock> m_lastUpdateTime;
            
        Scene* m_scene = nullptr;
    };

    Game* CreateGame()
    {
        return new GameImpl;
    }
}