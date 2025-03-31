#include "loopxia/scene/avatar.h"
#include "resource/mesh_impl.h"

namespace loopxia
{
    class AvatarImpl : public Avatar
    {
    public:
        AvatarImpl();

        void SetMesh(RefCountedObject<Mesh> mesh) override;
        RefCountedObject<Mesh> GetMesh() override;

    private:
        // reference to the mesh resource
        // multiple avatar can reference to the same mesh
        std::shared_ptr<MeshImpl> m_mesh;

        // reference to 
    };
}