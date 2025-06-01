#include "render/mesh_renderer_impl.h"
#include "loopxia/render/shader.h"
#include "loopxia/render/render_buffer.h"
#include <GL/glew.h>


#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define SSBO_INDEX_VERTICES        0
#define SSBO_INDEX_PER_OBJ_DATA    1
#define SSBO_INDEX_MATERIAL_COLORS 2
#define SSBO_INDEX_DIFFUSE_MAPS    3
#define SSBO_INDEX_NORMAL_MAPS     4

#include <chrono>
namespace loopxia
{
    MeshRenderInstanceImpl::MeshRenderInstanceImpl(int instanceId, MeshRendererImpl* pRenderer, std::shared_ptr<Mesh> pMesh) :
        m_instanceId(instanceId)
        , m_pRenderer(pRenderer)
        , m_pMesh(pMesh)
    {
    }

    Matrix4x4 MeshRenderInstanceImpl::GetWorldMatrix()
    {
        return m_worldMatrix;
    }

    void MeshRenderInstanceImpl::SetWorldMatrix(Matrix4x4 m)
    {
        m_worldMatrix = m;
    }

    void MeshRenderInstanceImpl::SetAnimation(AnimationState& state)
    {
        m_animationState = state;
    }

    AnimationState MeshRenderInstanceImpl::GetAnimationState() const
    {
        return m_animationState;
    }

    void MeshRenderInstanceImpl::SetBoneTransformations(const std::vector<Matrix4x4>& boneTransformations)
    {
        m_boneTransformations = boneTransformations;
    }

    void MeshRenderInstanceImpl::EvaluateAnimation()
    {
        if (m_animationState.animationIndex1 < 0) {
            return;
        }

        m_boneTransformations = m_pMesh->GetBoneTransformations(m_animationState.animationIndex1, m_animationState.animTime);
    }

    std::vector<Matrix4x4> MeshRenderInstanceImpl::GetBoneTransformations() const
    {
        return m_boneTransformations;
    }

    std::shared_ptr<Mesh> MeshRenderInstanceImpl::GetMesh()
    {
        return m_pMesh;
    }

    MeshRendererImpl::MeshRendererImpl() :
        //m_staticMeshShader("assets/shaders/static_mesh.vs", "assets/shaders/static_mesh.fs")
        m_animatedMeshShader("assets/shaders/animated_mesh.vs", "assets/shaders/animated_mesh.fs")
    {
        //m_staticMeshShader.SetupShaderBuffers();
        m_animatedMeshShader.SetupShaderBuffers();
    }

    void MeshRendererImpl::p_LoadTexture(const std::shared_ptr<Mesh> mesh, MeshRenderSetup* setup)
    {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        int width, height, channels;
        std::string imageFilePath = mesh->GetMaterial()->GetTextureFilePath();
        unsigned char* image = stbi_load(imageFilePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);
        if (!image) {
            LogError("Failed to load image {}", imageFilePath);
            return;
        }

        glGenTextures(1, &setup->m_textureID);
        glBindTexture(GL_TEXTURE_2D, setup->m_textureID);

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

    void MeshRendererImpl::p_InitInstancing(const std::shared_ptr<Mesh> mesh, MeshRenderSetup* setup, int maxInstances)
    {
        //setup->m_maxNumInstances = maxInstances > 0 ? maxInstances : 1;

        //glGenBuffers(1, &setup->m_instanceVBO);
        //glBindBuffer(GL_ARRAY_BUFFER, setup->m_instanceVBO);
        //glBufferData(GL_ARRAY_BUFFER, setup->m_maxNumInstances * sizeof(glm::mat4), instanceMatrices, GL_STATIC_DRAW);
        //
        //std::size_t vec4Size = sizeof(glm::vec4);
        //for (int i = 0; i < setup->m_maxNumInstances; ++i) {
        //    glEnableVertexAttribArray(2 + i);
        //    glVertexAttribPointer(2 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(i * vec4Size));
        //    glVertexAttribDivisor(2 + i, 1); // Advance once per instance
        //}
    }
    
    void MeshRendererImpl::p_RenderIndirect()
    {

    }

    MeshRenderInstance* MeshRendererImpl::AddMesh(const std::shared_ptr<Mesh> mesh)
    {
        if (mesh->Vertices().empty()) {
            return nullptr;
        }

        MeshRenderSetup* setup = nullptr;
        auto it = m_meshToSetupMap.find(mesh);
        if (it != m_meshToSetupMap.end()) {
            // existing setup
            setup = &it->second;
        } else {
            // new mesh
            setup = &m_meshToSetupMap[mesh];

            p_LoadTexture(mesh, setup);

            auto& indices = mesh->Indices();
            setup->m_numIndices = (uint32_t)indices.size();
            setup->m_baseIndex = (int)m_indices.size();
            m_indices.insert(m_indices.end(), indices.begin(), indices.end());

            auto& vertices = mesh->Vertices();
            setup->m_numVertices = (uint32_t)vertices.size();
            setup->m_baseVertex = (int)m_vertices.size();
            m_vertices.insert(m_vertices.end(), vertices.begin(), vertices.end());

            auto& uvs = mesh->UV();
            m_uvs.insert(m_uvs.end(), uvs.begin(), uvs.end());

            auto& normals = mesh->Normals();
            m_normals.insert(m_normals.end(), normals.begin(), normals.end());

            // bone data
            auto& boneWeights = mesh->BoneWeights();
            m_boneWeightByVertex.insert(m_boneWeightByVertex.end(), boneWeights.begin(), boneWeights.end());
        }

        auto instanceId = (int)setup->m_instances.size();
        auto newInstance = new MeshRenderInstanceImpl(instanceId, this, mesh);

        setup->m_instances.push_back(newInstance);

        return newInstance;
    }

    void MeshRendererImpl::RemoveMesh(MeshRenderInstance* meshInstance)
    {
        auto it = m_meshToSetupMap.find(meshInstance->GetMesh());
        if (it == m_meshToSetupMap.end()) {
            return;
        }

        auto& instancesVec = it->second.m_instances;
        auto itVec = std::find(instancesVec.begin(), instancesVec.end(), meshInstance);
        if (itVec != instancesVec.end()) {
            // found entry and erase
            instancesVec.erase(itVec);
        }
    }

    void MeshRendererImpl::Render(MeshRenderInstance* instance, Matrix4x4 vpMatrix)
    {
       // auto mvp = vpMatrix * instance->GetWorldMatrix();
        m_animatedMeshShader.SetWVP(vpMatrix);
        
        auto pMesh = instance->GetMesh();
        if(auto it = m_meshToSetupMap.find(pMesh);
            it != m_meshToSetupMap.end()) {
            auto& setup = it->second;
            auto start = std::chrono::high_resolution_clock::now();
            m_animatedMeshShader.SetTextureId(setup.m_textureID);
            
            auto animState = instance->GetAnimationState();
            animState.animationIndex1 = 0;
            animState.animTime += 0.03;
            instance->SetAnimation(animState);

            instance->EvaluateAnimation();
            
            auto boneTransformation = instance->GetBoneTransformations();
            m_animatedMeshShader.SetBoneTransformations(boneTransformation);

            glDrawElementsBaseVertex(GL_TRIANGLES,
                setup.m_numIndices,
                GL_UNSIGNED_INT,
                (void*)(sizeof(unsigned int) * setup.m_baseIndex),
                setup.m_baseVertex);

            auto end = std::chrono::high_resolution_clock::now();
            // Compute duration in milliseconds
            std::chrono::duration<double, std::milli> duration = end - start;
            if (duration.count() > 100) {
                int a = 0;
                int b = a;
            }
            //LogInfo(std::format("render {}", duration.count()));
        }
    }

    void MeshRendererImpl::BeginRender()
    {
        // bind the shader program
        m_animatedMeshShader.BeginRender();
    }

    void MeshRendererImpl::EndRender()
    {
        m_animatedMeshShader.EndRender();
    }

    void MeshRendererImpl::Init()
    {
        if (m_bInitialized) {
            return;
        }

        // setup SSBOs
        // SSBO Shader Storage Buffer Object
        // 
        // draw commands SSBO
        //p_InitDrawCommandsBuffer();
        //p_UpdateDrawCommandsBuffer();
        //
        //// per object SSBO
        //p_InitPerObjectBuffer();
        //p_UpdatePerObjectBuffer();

        m_bInitialized = true;
    }
    
    void MeshRendererImpl::UpdateBuffer()
    {
        //IBO data
        m_animatedMeshShader.BeginRender();

        m_animatedMeshShader.GetIndexBuffer()->SetData((void*)m_indices.data(), m_indices.size() * sizeof(int));
        m_animatedMeshShader.GetVertexBuffer()->SetData((void*)m_vertices.data(), m_vertices.size() * 3 * sizeof(float));
        m_animatedMeshShader.GetUVBuffer()->SetData((void*)m_uvs.data(), m_uvs.size() * 2 * sizeof(float));
        m_animatedMeshShader.GetNormalBuffer()->SetData((void*)m_normals.data(), m_normals.size() * 3 * sizeof(float));
        m_animatedMeshShader.GetBoneBuffer()->SetData((void*)m_boneWeightByVertex.data(), m_boneWeightByVertex.size() * sizeof(VertexBoneData));

        m_animatedMeshShader.EndRender();
    }

    MeshRenderer* CreateMeshRenderer()
    {
        return new MeshRendererImpl();
    }
}