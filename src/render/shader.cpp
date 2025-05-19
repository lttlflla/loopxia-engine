#include "loopxia/render/shader.h"
#include "loopxia/log.h"
#include <format>
#include <string>
#include <fstream>
#include <streambuf>

#include <GL/glew.h> // opengl extension
#include <SDL3/SDL_opengl.h>

namespace loopxia
{
    namespace impl
    {
        void printProgramLog(GLuint program)
        {
            //Make sure name is shader
            if (!glIsProgram(program)) {
                LogError(std::format("Name {} is not a program\n", program));
            }

            //Program log length
            int infoLogLength = 0;
            int maxLength = infoLogLength;

            //Get info string length
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            //Allocate string
            char* infoLog = new char[maxLength];

            //Get info log
            glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
            if (infoLogLength > 0) {
                //Print Log
                LogError(std::format("{}\n", infoLog));
            }

            //Deallocate string
            delete[] infoLog;
        }

        void printShaderLog(GLuint shader)
        {
            //Make sure name is shader
            if (!glIsShader(shader)) {
                LogError(std::format("printShaderLog. {} is not a valid shader", shader));
                return;
            }

            //Shader log length
            int infoLogLength = 0;
            int maxLength = infoLogLength;

            //Get info string length
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            //Allocate string
            char* infoLog = new char[maxLength];

            //Get info log
            glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
            if (infoLogLength > 0) {
                //Print Log
                LogError(std::format("Shader message {} {}", shader, infoLog));
            }

            //Deallocate string
            delete[] infoLog;
        }

        class ShaderImpl
        {
        public:
            ShaderImpl()
            {
                m_programID = glCreateProgram();

                m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
            }

            ~ShaderImpl()
            {
                if (glIsProgram(m_programID)) {
                    glDeleteProgram(m_programID);
                }

                if (glIsShader(m_vertexShader)) {
                    glDeleteShader(m_vertexShader);
                }

                if (glIsShader(m_fragmentShader)) {
                    glDeleteShader(m_fragmentShader);
                }
            }

            void Begin()
            {
                if (m_currentProgramID != m_programID) {
                    glUseProgram(m_programID);
                    m_currentProgramID = m_programID;
                }
            }

            void End()
            {
                //glUseProgram(NULL);
            }

            void Load(const std::string& source, Shader::ShaderType type)
            {
                //Set vertex source
                const GLchar* sourcePtr[] = {source.c_str()};
                GLint sourceLength[] = { source.size() };
                GLint shaderId;
                switch (type) {
                case Shader::ShaderType::kFragment:
                    shaderId = m_fragmentShader;
                    break;
                case Shader::ShaderType::kVertex:
                    shaderId = m_vertexShader;
                    break;
                }

                glShaderSource(shaderId, 1, sourcePtr, sourceLength);

                //Compile vertex source
                glCompileShader(shaderId);

                //Check vertex shader for errors
                GLint vShaderCompiled = GL_FALSE;
                glGetShaderiv(shaderId, GL_COMPILE_STATUS, &vShaderCompiled);
                if (vShaderCompiled != GL_TRUE) {
                    auto errMsg = std::format("Failed to compile vertex shader {}!\n", shaderId);
                    LogError(errMsg);
                    printShaderLog(shaderId);
                    return;
                }

                glAttachShader(m_programID, shaderId);
            }
            
            void Link()
            {
                //Link program
                glLinkProgram(m_programID);

                //Check for errors
                GLint programSuccess = GL_TRUE;
                glGetProgramiv(m_programID, GL_LINK_STATUS, &programSuccess);
                if (programSuccess != GL_TRUE) {
                    LogError(std::format("Error linking program {}!", m_programID));
                    printProgramLog(m_programID);
                }
            }
            
            void SetVertexPointer(const std::string& attribute, uint8_t size /* size of time */,
                int type /* data type, float or int */,
                bool normalized /* whether to normalize data */,
                int stride,
                const void* pointer)
            {

            }

            int GetAttribute(const std::string& attribute)
            {
                return glGetAttribLocation(m_programID, attribute.c_str());
            }

            int GetUniformLocation(const std::string& attributeName)
            {
                return glGetUniformLocation(m_programID, attributeName.c_str());

            }
        protected:
            GLuint m_programID = 0;
            GLuint m_fragmentShader = 0;
            GLuint m_vertexShader = 0;

            static GLuint m_currentProgramID;
        };
        
        GLuint ShaderImpl::m_currentProgramID = -1;
    }

    Shader::Shader()
    {
        m_impl = new impl::ShaderImpl();
    }

    Shader::~Shader()
    {
        delete m_impl;
    }

    void Shader::Begin()
    {
        m_impl->Begin();
    }

    void Shader::End()
    {
        m_impl->End();
    }

    void Shader::LoadFromFile(const std::string& shaderFile, ShaderType type)
    {
        std::ifstream t(shaderFile);
        
        if (t.fail()) {
            LogError(std::format("[Shader::LoadFromFile] failed: {}", shaderFile));
            return;
        }

        std::string str((std::istreambuf_iterator<char>(t)),
            std::istreambuf_iterator<char>());
        Load(str, type);
    }

    void Shader::Load(const std::string& source, Shader::ShaderType type) 
    {
        m_impl->Load(source, type);
    }

    void Shader::Link()
    {
        m_impl->Link();
    }

    void Shader::SetVertexPointer(const std::string& attribute, uint8_t size /* size of time */,
        int type /* data type, float or int */,
        bool normalized /* whether to normalize data */,
        int stride,
        const void* pointer)
    {

    }


    int Shader::GetAttribute(const std::string& attribute)
    {
        return m_impl->GetAttribute(attribute);
    }


    int Shader::GetUniformLocation(const std::string& attributeName)
    {
        return m_impl->GetUniformLocation(attributeName);
    }
}