#pragma once

#include <string>

namespace loopxia
{
    namespace impl
    {
        class ShaderImpl;
    }

    class Shader
    {

    public:
        enum class ShaderType
        {
            kVertex,
            kFragment
        };

        Shader();
        ~Shader();

        void LoadFromFile(const std::string& shaderFile, ShaderType type);
        void Load(const std::string& shaderSource, ShaderType type);
        void Link();

        void Begin();
        void End();

        void SetVertexPointer(const std::string& attribute, uint8_t size /* size of time */,
            int type /* data type, float or int */,
            bool normalized /* whether to normalize data */,
            int stride,
            const void* pointer);

        int GetAttribute(const std::string& attribute);
        int GetUniformLocation(const std::string& attributeName);

    protected:
        impl::ShaderImpl* m_impl;
    };
}