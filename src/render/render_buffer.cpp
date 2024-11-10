#include "loopxia/render/render_buffer.h"

#include <GL/glew.h> // opengl extension
#include "SDL_opengl.h"

namespace loopxia
{
    namespace impl
    {
        class RenderBufferImpl
        {
            friend class ShaderImpl;
            //    Buffer Binding Target	Purpose
            //    GL_ARRAY_BUFFER	Vertex attributes
            //    GL_ATOMIC_COUNTER_BUFFER	Atomic counter storage
            //    GL_COPY_READ_BUFFER	Buffer copy source
            //    GL_COPY_WRITE_BUFFER	Buffer copy destination
            //    GL_DISPATCH_INDIRECT_BUFFER	Indirect compute dispatch commands
            //    GL_DRAW_INDIRECT_BUFFER	Indirect command arguments
            //    GL_ELEMENT_ARRAY_BUFFER	Vertex array indices
            //    GL_PIXEL_PACK_BUFFER	Pixel read target
            //    GL_PIXEL_UNPACK_BUFFER	Texture data source
            //    GL_QUERY_BUFFER	Query result buffer
            //    GL_SHADER_STORAGE_BUFFER	Read - write storage for shaders
            //    GL_TEXTURE_BUFFER	Texture data buffer
            //    GL_TRANSFORM_FEEDBACK_BUFFER	Transform feedback buffer
            //    GL_UNIFORM_BUFFER	Uniform block storage

        public:

            ~RenderBufferImpl()
            {
                if (m_bGenerated) {
                    glDeleteBuffers(1, &m_bufferId);
                }
            }

            void SetData(RenderBufferDataType dataType, void* data, size_t dataSize)
            {
                if (m_bGenerated) {
                    glDeleteBuffers(1, &m_bufferId);
                }
                
                glGenBuffers(1, &m_bufferId);

                switch (dataType) {
                case RenderBufferDataType::kIndexBuffer:
                    m_glDataType = GL_ELEMENT_ARRAY_BUFFER;
                    break; 
                case RenderBufferDataType::kVertexBuffer:
                case RenderBufferDataType::kUVBuffer:
                    m_glDataType = GL_ARRAY_BUFFER;
                    break;
                }

                glBindBuffer(m_glDataType, m_bufferId);
                auto e = glGetError();
                glBufferData(m_glDataType, dataSize, data, GL_STATIC_DRAW);
                e = glGetError();

                m_bGenerated = true;
            }

            void Bind()
            {
                glBindBuffer(m_glDataType, m_bufferId);
            }

        private:
            GLuint m_bufferId = 0;
            bool m_bGenerated = false;
            int m_glDataType = 0;
        };
    }

    RenderBuffer::RenderBuffer()
    {
        m_impl = new impl::RenderBufferImpl;
    }

    RenderBuffer::~RenderBuffer()
    {
        delete m_impl;
    }

    void RenderBuffer::SetData(RenderBufferDataType dataType, void* data, size_t dataSize)
    {
        m_impl->SetData(dataType, data, dataSize);
    }

    void RenderBuffer::Bind()
    {
        m_impl->Bind();
    }
}