#include "TextureManager.hpp"

TextureManager* TextureManager::getManager()
{
    std::call_once(flag, []() { manager = new TextureManager(); });

    return manager;
}

const Texture2D* TextureManager::getTextureById(std::string id)
{
    for (auto& i : textures)
    {
        if (i.second == id)
        {
            return i.first;
        }
    }
}

const int TextureManager::loadTexture(const std::string& path)
{
    Texture2D* texture = new Texture2D();

    *texture = LoadTexture(path.c_str());
    
    if(!IsTextureReady(*texture))
    {
        std::cout << "Error loading texture" << std::endl;
        
        return -1;
    }

    std::cout << path << std::endl;

    textures.emplace(texture, "test");

    return 0;
}

TextureManager* TextureManager::manager = nullptr;
std::once_flag TextureManager::flag;