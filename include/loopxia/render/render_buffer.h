#include "loopxia/math.h"

namespace loopxia
{
    namespace impl
    {
        class ShaderImpl;
        class RenderBufferImpl;
    }

    enum class RenderBufferDataType
    {
        VERTEX_BUFFER,
        INDEX_BUFFER
    };

    class RenderBuffer
    {
        friend class ShaderImpl;
    public:
        RenderBuffer();
        ~RenderBuffer();

        void SetData(RenderBufferDataType dataType, void* data, size_t dataSize);
        void Bind();

    protected:
        impl::RenderBufferImpl* m_impl;
    };
}