#include "scene_renderer_impl.h"
#include "avatar_impl.h"

namespace loopxia
{
    static void Render(const GameTime& time, std::vector<SceneNode*>& sceneNodes)
    {
        auto sceneNode = *sceneNodes.rbegin();
        sceneNodes.pop_back();

    }

    SceneRendererImpl::SceneRendererImpl() : m_pMeshRenderer(new MeshRendererImpl())
    {
    }

    void SceneRendererImpl::SetScene(Scene* scene)
    {
        m_pScene = scene;
    }
    
    void SceneRendererImpl::PrepareRenderers()
    {
        _PrepareRenderers();
    }

    void SceneRendererImpl::Render(const GameTime& time) 
    {
        _PrepareRenderers();
        auto cam = m_pScene->GetActiveCamera();

        auto projection = cam->GetProjectionMatrix();
        auto view = cam->GetViewMatrix();

        //meshRenderer->Render(g_characterMeshId, projection * view);
       
        // find out which scene node are in the visible area
        // 
        // tranverse through scene and gather all node which render
        m_pMeshRenderer->BeginRender();
       // m_pMeshRenderer->Render();
        for (auto& pair : m_avatarToRenderInstanceMap) {
            m_pMeshRenderer->Render(pair.second, projection * view * pair.first->Transform()->GetMatrix());
        }
        
        m_pMeshRenderer->EndRender();
    }

    void SceneRendererImpl::_PrepareRenderers()
    {
        auto n = m_pScene->SceneRoot();
        // loop through all children and find mesh
        auto avatars = n->AllDescendantByType<Avatar>();

        bool bHasNewMesh = false;
        for (auto& a : avatars) {
            if (auto m = a->GetMesh()) {
                if (!m_avatarToRenderInstanceMap.count(a)) {
                    auto renderInstance = m_pMeshRenderer->AddMesh(m);
                    m_avatarToRenderInstanceMap[a] = renderInstance;
                    bHasNewMesh = true;
                }
            }
        }

        if (bHasNewMesh) {
            m_pMeshRenderer->UpdateBuffer();
        }
    }

    SceneRenderer* CreateSceneRenderer()
    {
        return new SceneRendererImpl();
    }


}