
namespace loopxia
{
    namespace impl
    {
        class RendererImpl;
    }

    class Renderer
    {
    public:
        Renderer();
        ~Renderer();
        void Render();
        void Present();

    private:
        impl::RendererImpl * m_impl;
    };
}