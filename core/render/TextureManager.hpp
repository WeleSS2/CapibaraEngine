#pragma once

#include "Texture.hpp"
#include <unordered_map>

class TextureManager {
public:
    static TextureManager* getManager();

    const Texture2D* getTextureById(std::string id);
    
    const int loadTexture(const std::string& path);
protected:
    TextureManager() {};

    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;
private:
    std::unordered_map<Texture2D*, std::string> textures;

    static TextureManager* manager;

    static std::once_flag flag;
};
