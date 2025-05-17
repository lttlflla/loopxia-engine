#include "mesh_loader_impl.h"
#include "mesh_impl.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem>

namespace loopxia
{
    void LoadMesh(std::shared_ptr<MeshImpl> pMesh)
    {
    }

    bool MeshLoader::LoadResource(std::shared_ptr<Resource> resource)
    {
        auto pMeshResource = std::dynamic_pointer_cast<MeshImpl>(resource);
        if (!pMeshResource) {
            return false;
        }

        auto& vertices = pMeshResource->m_vertices;
        auto& normals = pMeshResource->m_normals;
        auto& indices = pMeshResource->m_indices;
        auto& uvs = pMeshResource->m_uvs;

        auto filePathStr = resource->FilePath();
        std::filesystem::path filePath(filePathStr);

        // Create an instance of the importer
        Assimp::Importer importer;

        // Specify the post-processing steps to apply during import
        unsigned int flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices;

        // Load the mesh using Assimp
        const aiScene* scene = importer.ReadFile(filePath.string(), flags);

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
            vertices.push_back(v);

            auto& aN = mesh->mNormals[i];
            Vector3 n = { aN.x, aN.y, aN.z };
            normals.push_back(n);

            auto& aUV = mesh->mTextureCoords[0][i]; // Assuming there's only one texture coordinate set
            Vector2 uv = { aUV.x, aUV.y };
            uvs.push_back(uv);

            // Do something with the vertex, normal, and UV data
        }

        // Iterate through each face (triangle) in the mesh
        for (unsigned int j = 0; j < mesh->mNumFaces; ++j) {
            const aiFace& face = mesh->mFaces[j];

            for (unsigned int k = 0; k < face.mNumIndices; ++k) {
                indices.push_back(face.mIndices[k]);
            }

        }

        // Access material data
        if (mesh->mMaterialIndex >= 0) {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            aiString texturePath;
            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS) {
                // Load the texture using the texture path
                LogInfo(std::string("Diffuse texture path: ") + texturePath.C_Str());

                //auto pMaterial = std::make_shared<MaterialImpl>(filePath.parent_path().generic_string() + "/" + texturePath.C_Str(), material->GetName().C_Str());
                auto pMaterial = pMeshResource->GetMaterial();
                pMaterial->SetTextureFilePath(0, filePath.parent_path().generic_string() + "/" + texturePath.C_Str());
            }
        }

        auto& boneWeights = pMeshResource->m_boneWeights;
        auto& bones = pMeshResource->m_bones;

        // load bone data
        if (mesh->HasBones()) {
            bones.resize(mesh->mNumBones);
            boneWeights.resize(vertices.size());
            for (unsigned int i = 0; i < mesh->mNumBones; i++) {
                auto assimpBone = mesh->mBones[i];

                auto& targetBone = bones[i];

                targetBone.SetName(assimpBone->mName.C_Str());
                Matrix4x4 m44;
                for (int mIndex = 0; mIndex < 16; mIndex++) {
                    m44[mIndex / 4][mIndex % 4] = assimpBone->mOffsetMatrix[mIndex / 4][mIndex % 4];
                }
                
                targetBone.SetOffsetMatrix(m44);

                for (unsigned int w = 0; w < assimpBone->mNumWeights; w++) {
                    auto vertexId = assimpBone->mWeights[w].mVertexId;

                    BoneWeight bw;
                    bw.boneId = i;
                    bw.boneWeight = assimpBone->mWeights[w].mWeight;
                    boneWeights[vertexId].push_back(bw);
                }
            }
        }

        return true;
    }
}
