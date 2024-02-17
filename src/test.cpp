// loopxia-engine.cpp : Defines the entry point for the application.
//

#include "loopxia.h"
//#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;
using namespace loopxia;

int main()
{
    cout << "Hello CMake." << endl;

    //if (!glfwInit()) {
    //    // write to file failed
    //}
    //auto winId = glfwCreateWindow(620, 620, "test", NULL, NULL);

    //glfwSetWindowPos(winId, 0, 0);

    //glfwMakeContextCurrent(context.wind);

    auto pWindow = ui::CreateUIWindow("test");
    
    event::RunEvent();

    //bool bCloseWindow = false;
    //// App loop
    //while (!bCloseWindow)
    //{
    //    // Process input events
    //    SDL_Event evt;
    //    while (SDL_PollEvent(&evt)) {
    //        switch (evt.type) {
    //            
    //        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:

    //            bCloseWindow = true;
    //            break;

    //        }

    //    }
    //    // Draw using OpenGL 
    //    // NOTE: It's up to the user to load required extensions and manage OpenGL state and drawing
    //    //glClearColor(0, 0, 0, 1);
    //    //glClear(GL_COLOR_BUFFER_BIT);
    //    SDL_GL_SwapWindow(window);
    //}

    // Deinitialize OpenGL context and window
   // SDL_GL_DeleteContext(glcontext);

    // Deinitialize SDL internal global state
    //SDL_Quit();
    return 0;
}
