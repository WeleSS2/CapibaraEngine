#include "TextureManager.hpp"
#include "Logs.hpp"
#include <filesystem>

TextureManager* TextureManager::manager = nullptr;
std::once_flag TextureManager::flag;

TextureManager* TextureManager::getManager()
{
    std::call_once(flag, []() 
        { 
            manager = new TextureManager(); 
        }
    );
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

const int TextureManager::loadTexture(const std::string& name)
{
    if (gfxPath == "")
    {
        gfxPath = std::filesystem::current_path().string() + "\\gfx\\";
    
        if (std::filesystem::exists(gfxPath) == false)
        {
            ERRORLOG("Critical error - Failed to load gfx path - ", gfxPath);

            return -1;
        }
    }

    Texture2D* texture = new Texture2D();

    std::string path2 = gfxPath + name;

    *texture = LoadTexture(path2.c_str());

    std::filesystem::path p(path2.c_str());
    
    if(!IsTextureReady(*texture))
    {
        ERRORLOG("Critical error - Failed to load texture - ", path2);
        
        return -1;
    }

    std::cout << p.filename().string() << " \n";

    textures.emplace(texture, p.filename().string());

    return 0;
}