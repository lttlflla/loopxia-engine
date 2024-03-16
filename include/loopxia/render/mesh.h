#include <string>

namespace loopxia
{
	namespace impl
	{
		class MeshImpl;
	}

	class Mesh
	{
	public:
		void LoadFromFile(const std::string& filePath);

	private:
		impl::MeshImpl* m_impl;
	};
}