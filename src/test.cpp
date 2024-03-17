// loopxia-engine.cpp : Defines the entry point for the application.
//

#include "loopxia/loopxia.h"
//#include <GLFW/glfw3.h>
#include "loopxia/render/shader.h"
#include "loopxia/render/render_buffer.h"
#include <GL/glew.h>
#include <iostream>
#include "loopxia/resource/mesh.h"

using namespace std;
using namespace loopxia;
using namespace loopxia::event;


loopxia::Shader* gShader;
loopxia::Window* gWindow;
RenderBuffer gVertexBuffer;
RenderBuffer gIndexBuffer;

GLint gVertexPos2DLocation = -1;
GLuint gVBO = 0;
GLuint gIBO = 0;

void render()
{
    //Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    //Render quad
    // bind the shader program
    gShader->Begin();

    auto attribute = gShader->GetAttribute("LVertexPos2D");
    //Enable vertex position
    glEnableVertexAttribArray(attribute);

    //Set vertex data
    gVertexBuffer.Bind();
    
    glVertexAttribPointer(attribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

    //Set index data and render
    gIndexBuffer.Bind();
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

    //Disable vertex position
    glDisableVertexAttribArray(attribute);

    //Unbind program
    gShader->End();
}


void RunEventPoller()
{
    // Process input events
    bool bCloseWindow = false;

    auto  f = [&bCloseWindow](Event& evt, WindowDetails& details) -> bool {
        bCloseWindow = true;
        return true;
    };

    event::WindowQuitRequest.connect(f);

    while (!bCloseWindow)
    {
        while (event::PollEvent()) {
            LogError("");
        }

        render();

        if (gWindow) {
            gWindow->Swap();
        }
    }

}

void PrintRenderers()
{
    auto numRenderDrivers = SDL_GetNumRenderDrivers();
    LogDebug("Renderer List");
    for (int i = 0; i < numRenderDrivers; ++i) {
        LogDebug(std::format("{}. {}", i, SDL_GetRenderDriver(i)));
    }
}

void resize(int width, int height)
{
    if (height <= 0)    height = 1;

    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(60.0f, float(width) / float(height), 1.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void initVertices()
{
    //VBO data
    GLfloat vertexData[] =
    {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    //IBO data
    GLuint indexData[] = { 0, 1, 2, 3 };

    //Create VBO
    glGenBuffers(1, &gVBO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

    //Create IBO
    glGenBuffers(1, &gIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
}

void InitGLEW()
{
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK)
    {
        LogError(std::format("Error initializing GLEW! {}\n", (char*)glewGetErrorString(glewError)));
    }
    
}

int main()
{
    PrintRenderers();

    InitEngine();
    //if (!glfwInit()) {
    //    // write to file failed
    //}
    //auto winId = glfwCreateWindow(620, 620, "test", NULL, NULL);

    //glfwSetWindowPos(winId, 0, 0);

    //glfwMakeContextCurrent(context.wind);

    gWindow = CreateUIWindow("test");
    
    auto  f = [](Event& evt, WindowDetails& details, int w, int h) -> bool {
        resize(w, h);
        return true;
        };

    event::WindowResize.connect(f);

    InitGLEW();
    initVertices();

    gShader = new Shader();
    gShader->Load("#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }", Shader::ShaderType::FRAGMENT);
    gShader->Load("#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }", Shader::ShaderType::VERTEX);
    gShader->Link();

    //VBO data
    GLfloat vertexData[] =
    {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    //IBO data
    GLuint indexData[] = { 0, 1, 2, 3 };
    
    gVertexBuffer.SetData(RenderBufferDataType::VERTEX_BUFFER, vertexData, 2 * 4 * sizeof(GLfloat));

    gIndexBuffer.SetData(RenderBufferDataType::INDEX_BUFFER, indexData, 4 * sizeof(GLuint));

    RunEventPoller();
    
    ShutdownEngine();
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
