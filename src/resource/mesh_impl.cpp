#include "resource/mesh_impl.h"
#include "resource/material_impl.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "loopxia/log.h"
#include <filesystem>

namespace loopxia
{
    MeshImpl::~MeshImpl()
    {
        delete m_pMaterial;
    }

    void MeshImpl::SetVectices(std::vector<Vector3>& vertices)
    {
        m_vertices = vertices;
    }

    void MeshImpl::SetNormals(std::vector<Vector3>& normals)
    {
        m_normals = normals;
    }

    void MeshImpl::SetUV(std::vector<Vector2>& uvs)
    {
        m_uvs = uvs;
    }

    void MeshImpl::SetIndices(std::vector<int>& indices)
    {
        m_indices = indices;
    }

    const std::vector<Vector3>& MeshImpl::Vertices() const
    {
        return m_vertices;
    }

    const std::vector<Vector3>& MeshImpl::Normals() const
    {
        return m_normals;
    }

    const std::vector<Vector2>& MeshImpl::UV() const
    {
        return m_uvs;
    }

    const std::vector<int>& MeshImpl::Indices() const
    {
        return m_indices;
    }

    Material* MeshImpl::GetMaterial() const
    {
        return m_pMaterial;
    }


    bool MeshImpl::LoadFromFile(const std::string& filePathStr)
    {
        m_vertices.clear();
        m_normals.clear();
        m_indices.clear();

        std::filesystem::path filePath(filePathStr);

        // Create an instance of the importer
        Assimp::Importer importer;

        // Specify the post-processing steps to apply during import
        unsigned int flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices;

        // Load the mesh using Assimp
        const aiScene* scene = importer.ReadFile(filePathStr, flags);

        // Check if the scene was loaded successfully
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            LogError(std::string("Error loading mesh: ") + importer.GetErrorString());
            return false;
        }

        // Assume there is only one mesh in the scene for simplicity
        const aiMesh* mesh = scene->mMeshes[0];

        // Access vertex data
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            auto& aV = mesh->mVertices[i];
            Vector3 v = { aV.x, aV.y, aV.z };
            m_vertices.push_back(v);

            auto& aN = mesh->mNormals[i];
            Vector3 n = { aN.x, aN.y, aN.z };
            m_normals.push_back(n);

            auto& aUV = mesh->mTextureCoords[0][i]; // Assuming there's only one texture coordinate set
            Vector2 uv = { aUV.x, aUV.y };
            m_uvs.push_back(uv);

            // Do something with the vertex, normal, and UV data
        }

        // Iterate through each face (triangle) in the mesh
        for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {
            const aiFace& face = mesh->mFaces[j];

            for (unsigned int k = 0; k < face.mNumIndices; ++k) {
                m_indices.push_back(face.mIndices[k]);
            }

        }
        
        // Access material data
        if (mesh->mMaterialIndex >= 0) {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            aiString texturePath;
            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS) {
                // Load the texture using the texture path
                LogInfo(std::string("Diffuse texture path: ") + texturePath.C_Str());
                m_pMaterial = (MaterialImpl*)CreateMaterialFromTextureFilePath(filePath.parent_path().generic_string() + "/" + texturePath.C_Str());
            }
        }

        // load bone data
        if (mesh->HasBones()) {
            m_boneWeights.resize(m_vertices.size());
            for (int i = 0; i < mesh->mNumBones; i++) {
                auto bone = mesh->mBones[i];
                for (int w = 0; w < bone->mNumWeights; w++) {
                    auto vertexId = bone->mWeights[w].mVertexId;

                    BoneWeight bw;
                    bw.boneId = i;
                    bw.boneWeight = bone->mWeights[w].mWeight;
                    m_boneWeights[vertexId].push_back(bw);
                }
            }
        }

        return true;
    }


    Mesh* MeshLoadFromFile(const std::string& filePath)
    {
        auto pMesh = new MeshImpl();
        pMesh->LoadFromFile(filePath);
        return pMesh;
    }
}