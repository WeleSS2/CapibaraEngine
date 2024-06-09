#include "TextureManager.hpp"
#include <filesystem>

TextureManager* TextureManager::getManager()
{
    std::call_once(flag, []() { manager = new TextureManager(); });

    return manager;
}

Texture2D* TextureManager::getTextureById(std::string id)
{
    for (auto& i : textures)
    {
        if (i.second == id)
        {
            return i.first;
        }
    }

    return nullptr;
}

const int TextureManager::loadTexture(const std::string& path)
{
    Texture2D* texture = new Texture2D();

    std::string path2 = "gfx\\" + path;

    *texture = LoadTexture(path2.c_str());

    std::filesystem::path p(path2.c_str());
    
    if(!IsTextureReady(*texture))
    {
        std::cout << "Error loading texture - " << path2 << std::endl;
        
        return -1;
    }

    std::cout << p.filename().string() << " \n";

    textures.emplace(texture, p.filename().string());

    return 0;
}

TextureManager* TextureManager::manager = nullptr;
std::once_flag TextureManager::flag;