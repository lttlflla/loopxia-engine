#include "loopxia/scene/scene.h"
#include "scene_renderer_impl.h"

namespace loopxia
{
    class SceneImpl : public Scene
    {
    public:
        SceneImpl();

        SceneNode* SceneRoot() override;
        void Render(const GameTime& gameTime) override;

        void SetActiveCamera(Camera* camera) override;
        Camera* GetActiveCamera() override;

    private:
        std::unique_ptr<SceneNode> m_root;
        Camera* m_pCamera = nullptr;

        std::unique_ptr<SceneRendererImpl> m_sceneRenderer;
    };
}