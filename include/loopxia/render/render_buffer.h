#pragma once

#include "loopxia/math.h"
#include <GL/glew.h>

namespace loopxia
{
    namespace impl
    {
        class ShaderImpl;
        class RenderBufferImpl;
    }

    enum class RenderBufferDataType
    {
        kVertexBuffer,
        kIndexBuffer,
        kUVBuffer,
        kNormalBuffer,
        kBoneIdBuffer,
        kBoneWeightBuffer
    };

    class RenderBuffer
    {
        friend class ShaderImpl;
    public:
        RenderBuffer(GLuint bufferId, RenderBufferDataType dataType);
        ~RenderBuffer();

        void SetData(void* data, size_t dataSize);
        void Bind();

    protected:
        impl::RenderBufferImpl* m_impl;
    };
}