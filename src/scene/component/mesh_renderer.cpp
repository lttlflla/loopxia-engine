#include "loopxia/render/mesh_renderer.h"
#include "loopxia/render/shader.h"
#include "loopxia/render/render_buffer.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace loopxia
{
    namespace impl
    {
        // Define vertex shader source code
        const char* vertexShaderSource = R"(#version 330 core
    in vec3 aPos;
    in vec2 uv;
    out vec2 TexCoord;
    uniform mat4 mvp;
    void main() {
       gl_Position = mvp * vec4(aPos, 1.0) ;
       TexCoord = uv;
            })";

        // Define fragment shader source code
        const char* fragmentShaderSource = R"(
            #version 330 core

            in vec2 TexCoord;
            out vec4 FragColor;
            uniform sampler2D textureSampler;

            void main() {
                FragColor =  texture(textureSampler, TexCoord);
//FragColor = vec4(TexCoord.x, TexCoord.y, 1.0, 1.0);
            }
        )";

        class MeshRendererImpl
        {
        public:
            MeshRendererImpl()
            {
                //m_meshShader.Load("#version 140\nin vec3 LVertexPos3D; void main() { gl_Position = vec4( LVertexPos3D.x, LVertexPos3D.y, LVertexPos3D.z, 1 ); }", Shader::ShaderType::VERTEX);
                m_meshShader.Load(vertexShaderSource, Shader::ShaderType::VERTEX);
                //m_meshShader.Load("#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }", Shader::ShaderType::FRAGMENT);
                m_meshShader.Load(fragmentShaderSource, Shader::ShaderType::FRAGMENT);
                m_meshShader.Link();
            }

            void p_LoadTexture(const Mesh* mesh)
            {
                glEnable(GL_DEPTH_TEST);
                glDepthFunc(GL_LESS);
                int width, height, channels;
                unsigned char* image = stbi_load(mesh->TextureFilePath().c_str(), &width, &height, &channels, STBI_rgb_alpha);
                if (!image) {
                    LogError("Failed to load image");
                    return;
                }

                glGenTextures(1, &m_textureID);
                glBindTexture(GL_TEXTURE_2D, m_textureID);

                // Set texture parameters
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                // Upload image data to texture
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
                glGenerateMipmap(GL_TEXTURE_2D);

                // Free image data
                stbi_image_free(image);
            }

            void SetMesh(const Mesh* mesh)
            {
                glGenVertexArrays(1, &VAO);
                glBindVertexArray(VAO);

                //VBO data
                //GLfloat vertexData[] =
                //{
                //    -0.5f, -0.5f, 0,
                //     0.5f, -0.5f, 0,
                //     0.5f,  0.5f, 0,
                //    -0.5f,  0.5f, 0
                //};

                ////IBO data
                //GLuint indexData[] = { 0, 1, 2, 3 };
                //m_numVertices = 4;
                //m_numIndices = 4;
                //m_vertexBuffer.SetData(RenderBufferDataType::VERTEX_BUFFER, (void*)vertexData, 3 * 4 * sizeof(float));
                //m_indexBuffer.SetData(RenderBufferDataType::INDEX_BUFFER, (void*)indexData, 4 * sizeof(int));

                auto& vertices = mesh->Vertices();
                m_numVertices = vertices.size();
                m_vertexBuffer.SetData(RenderBufferDataType::VERTEX_BUFFER, (void*)&vertices[0], 3 * m_numVertices * sizeof(float));

                // Position attribute
                unsigned int positionPos = m_meshShader.GetAttribute("aPos");
                glVertexAttribPointer(positionPos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 /*offset*/);
                glEnableVertexAttribArray(positionPos);

                auto& indices = mesh->Indices();
                m_numIndices = indices.size();
                m_indexBuffer.SetData(RenderBufferDataType::INDEX_BUFFER, (void*)&indices[0], m_numIndices * sizeof(int));

                auto& uvs = mesh->UV();
                m_numUVs = uvs.size();
                m_uvBuffer.SetData(RenderBufferDataType::UV_BUFFER, (void*)&uvs[0], 2 * m_numUVs * sizeof(float));
                m_uvBuffer.Bind();

                // uv attribute
                unsigned int uv_position = m_meshShader.GetAttribute("uv");
                glVertexAttribPointer(uv_position, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0 /*offset*/);
                glEnableVertexAttribArray(uv_position);


                p_LoadTexture(mesh);
            }

            void SetWVP(Matrix4x4 matrix)
            {
                m_wvp = matrix;
            }

            void Render()
            {
                auto e = glGetError();
                // bind the shader program
                m_meshShader.Begin();
                e = glGetError();

                static bool mSet = false;
                // if (!mSet) {
                auto attribute = m_meshShader.GetUniformLocation("mvp");
                glUniformMatrix4fv(attribute, 1, GL_FALSE, glm::value_ptr(m_wvp));
                //}


                //Set vertex data
                //m_vertexBuffer.Bind();
                //auto e = glGetError();
                //auto attribute = 0;// m_meshShader.GetAttribute("LVertexPos2D");
                ////Enable vertex position
                ////glEnableVertexAttribArray(attribute);
                ////glVertexAttribPointer(attribute, 3 /* number of components per generic vertex attribute */, GL_FLOAT, GL_FALSE, 3 * sizeof(float) /* stride, 0 to indicate tightly packed */, NULL);
                //e = glGetError();
                ////Set index data and render
                ////m_indexBuffer.Bind();
                //e = glGetError();
                //glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, NULL);
                //e = glGetError();
                ////Disable vertex position
                //glDisableVertexAttribArray(attribute);
                //e = glGetError();
                ////Unbind program

                glBindVertexArray(VAO);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, m_textureID);
                auto textureLocation = m_meshShader.GetUniformLocation("textureSampler");
                glUniform1i(textureLocation, 0);

                e = glGetError();
                glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, NULL);
                e = glGetError();

                m_meshShader.End();
                e = glGetError();


            }

        private:
            // set up the shader
            Shader m_meshShader;

            RenderBuffer m_vertexBuffer;
            RenderBuffer m_indexBuffer;

            RenderBuffer m_normalBuffer;
            RenderBuffer m_uvBuffer;

            int m_numVertices = 0;
            int m_numIndices = 0;
            int m_numUVs = 0;
            GLuint VAO;

            GLuint m_textureID;

            Matrix4x4 m_wvp;
        };
    }

    MeshRenderer::MeshRenderer()
    {
        m_impl = new impl::MeshRendererImpl();
    }

    MeshRenderer::~MeshRenderer()
    {
        delete m_impl;
    }

    void MeshRenderer::SetMesh(const Mesh* mesh)
    {
        m_impl->SetMesh(mesh);
    }

    void MeshRenderer::SetWVP(Matrix4x4 matrix)
    {
        m_impl->SetWVP(matrix);
    }

    void MeshRenderer::Render()
    {
        m_impl->Render();
    }
}