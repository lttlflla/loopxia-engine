#include "loopxia/game/game.h"
#include "loopxia/ui/ui.h"
#include "windows.h"
#include <SDL.h>
#include <GL/glew.h>
#include <gl/GL.h>
#include <thread>
#include "loopxia/loopxia.h"
//#include <GL/glew.h>

using namespace loopxia;

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

            glEnable(GL_DEBUG_OUTPUT);
            glDebugMessageCallback([](GLenum, GLenum, GLuint, GLenum severity, GLsizei, const GLchar* message, const void*) {
                LogError( std::format("OpenGL: {}", (std::string)message));
                }, nullptr);
            auto  resizeFunc = [this](Event& evt, WindowDetails& details, int w, int h) -> bool {
                _resize(w, h);
                return true;
            };

            m_windowResizeEventConnection = WindowResize.connect(resizeFunc);

            auto  closeWindowFunc = [this](Event& evt, WindowDetails& details) -> bool {
                m_bCloseWindow = true;
                m_renderThread->join();
                m_renderThread.reset();
                return true;
            };

            m_windowQuitEventConnection = WindowQuitRequest.connect(closeWindowFunc);
        }

        void Run() override
        {
            m_pWindow->DetachContext();
            if (!m_renderThread) {
                m_renderThread.reset(new std::thread([this] {

#ifdef WIN32
                    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
#endif
                    _renderLoop();
                    }));
            }

            while (!m_bCloseWindow) {
                while (_PollEvent()) {
                }
                SDL_Delay(10);
            }
        }

        Scene* CurrentScene() override
        {
            return m_scene;
        }

        void SetScene(Scene* pNextScene, SceneTransition* sceneTransition) override
        {
            m_scene = pNextScene;
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
            bool ret = SDL_PollEvent(&sdlEvt);
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

            return ret;
        }

        void _Update(GameTime& gameTime)
        {
            GameUpdate.Signal(gameTime);
        }

        void _renderLoop()
        {
            m_pWindow->MakeCurrentContext();

            while (!m_bCloseWindow) {
                auto timeNow = std::chrono::high_resolution_clock::now();
                int doubleBuffer;
                SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &doubleBuffer);

                if (m_lastUpdateTime == std::chrono::steady_clock::time_point()) {
                    // "time_point is uninitialized (epoch)"
                    m_lastUpdateTime = timeNow;
                }

                auto elapsed = timeNow - m_lastUpdateTime;

                GameTime time(elapsed, timeNow);
                if (time.ElapsedTimeMilliseconds() > (1000 / 60)) {
                    m_lastUpdateTime = timeNow;
                    _Update(time);
                }

                if (m_lastRenderTime == std::chrono::steady_clock::time_point()) {
                    // "time_point is uninitialized (epoch)"
                    m_lastRenderTime = timeNow;
                }

                auto elapsedRenderTime = timeNow - m_lastRenderTime;
                GameTime elapsedRenderGameTime(elapsedRenderTime, timeNow);
                if (elapsedRenderGameTime.ElapsedTimeMilliseconds() >= (1000 / 90)) {

                    //Clear color buffer
                    glClearColor(0, 0, 0, 1);
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    if (!m_scene) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(33));
                        continue;
                    }

                    auto root = m_scene->SceneRoot();

                    // cull visible
                    // render visible
                    m_scene->Render(time);


                    //auto start = std::chrono::high_resolution_clock::now();
                    if (m_pWindow) {
                        m_pWindow->Swap();
                    }
                    
                    m_lastRenderTime = std::chrono::high_resolution_clock::now();

                    //auto end = std::chrono::high_resolution_clock::now();
                    // Compute duration in milliseconds
                    /*std::chrono::duration<double, std::milli> duration = end - start;
                    
                    if (duration.count() > 100 || elapsedRenderGameTime.ElapsedTimeMilliseconds() > 100) {
                        int a = 0;
                        int b = a;
                    }
                    LogInfo(std::format("time lapsed {} swap took: {}", elapsedRenderGameTime.ElapsedTimeMilliseconds(), duration.count()));*/
                } else {
                    int waitTime = (1000 / 90) - elapsedRenderGameTime.ElapsedTimeMilliseconds();
                    std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
                    //LogInfo(std::format("sleep_for {}", waitTime));
                }

                
            }
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
        // dedicated thread for rendering
        std::unique_ptr<std::thread> m_renderThread;

        bool m_bCloseWindow = false;
        Window* m_pWindow = nullptr;
        std::chrono::time_point<std::chrono::steady_clock> m_lastUpdateTime;
        std::chrono::time_point<std::chrono::steady_clock> m_lastRenderTime;
            
        Scene* m_scene = nullptr;

        EventConnection m_windowQuitEventConnection;
        EventConnection m_windowResizeEventConnection;
    };

    Game* CreateGame()
    {
        return new GameImpl;
    }
}