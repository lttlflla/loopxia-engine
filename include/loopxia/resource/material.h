
namespace loopxia
{
    class Material
    {
    public:
        virtual std::string GetTextureFilePath(int index) = 0;
    };

    Material* CreateMaterialFromTextureFilePath(const std::string& textureFilePath);
    Material* CreateMaterialFromMaterialFile(const std::string& materialFilePath);
}

