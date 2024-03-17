#include "loopxia/render/mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "loopxia/log.h"

namespace loopxia
{
	bool Mesh::LoadFromFile(const std::string& filePath) 
	{
        // Create an instance of the importer
        Assimp::Importer importer;

        // Specify the post-processing steps to apply during import
        unsigned int flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices;

        // Load the mesh using Assimp
        const aiScene* scene = importer.ReadFile(filePath, flags);

        // Check if the scene was loaded successfully
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            LogError(std::string("Error loading mesh: ") + importer.GetErrorString());
            return -1;
        }

        // Assume there is only one mesh in the scene for simplicity
        const aiMesh* mesh = scene->mMeshes[0];

        // Access vertex data
        for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
            aiVector3D vertex = mesh->mVertices[i];
            aiVector3D normal = mesh->mNormals[i];
            aiVector3D uv = mesh->mTextureCoords[0][i]; // Assuming there's only one texture coordinate set
            // Do something with the vertex, normal, and UV data
        }

        // Access material data
        if (mesh->mMaterialIndex >= 0) {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            aiString texturePath;
            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS) {
                // Load the texture using the texture path
                LogInfo(std::string("Diffuse texture path: ") + texturePath.C_Str());
            }
        }

        return true;
	}
}