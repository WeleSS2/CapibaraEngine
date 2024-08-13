#include "textureManager.h"
#include "logs.h"
#include <filesystem>

TextureManager* TextureManager::manager = nullptr;
std::once_flag TextureManager::flag;

const TextureManager* TextureManager::getInstance()
{
    std::call_once(flag, []() 
        { 
            manager = new TextureManager(); 
        }
    );
    return manager;
}

Texture2D* TextureManager::getTextureById(const std::string& _id) const
{
    for (auto& i : textures)
    {
        if (i.first == _id)
        {
            return i.second;
        }
    }

    return nullptr;
}

const int TextureManager::loadTexture(const std::string& _id)
{
    if (gfxPath == "")
    {
        gfxPath = std::filesystem::current_path().string() + "\\gfx\\";
    
        if (std::filesystem::exists(gfxPath) == false)
        {
            ERRORLOG("Critical error - Failed to load gfx path - ", gfxPath.c_str());

            return -1;
        }
    }

    if (getTextureById(_id) != nullptr)
    {
        return 1;
    }

    Texture2D* texture = new Texture2D();

    std::string path2 = gfxPath + _id;

    *texture = LoadTexture(path2.c_str());

    std::filesystem::path p(path2.c_str());
    
    if(!IsTextureReady(*texture))
    {
        ERRORLOG("Critical error - Failed to load texture - ", path2.c_str());
        
        return -1;
    }

    std::cout << p.filename().string() << " \n";

    textures.emplace(std::make_pair(p.filename().string(), texture));

    return 0;
}