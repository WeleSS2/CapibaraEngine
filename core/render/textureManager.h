#pragma once

#include <iostream>
#include "raylib.h"
#include <unordered_map>
#include "logs.h"
/*
 * Load and store textures
 * Thread safe singleton 
 * TODO: THread save methods
 * Once loaded texture is keept in memory all time, can be removed only when called directly.
 * Removing texture DO NOT CHECK did there exist any Entity which uses it (TODO safety)
 */
class TextureManager {
public:
    TextureManager() {};

    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    TextureManager(TextureManager&&) = delete;
    TextureManager operator=(const TextureManager&&) = delete;

    static TextureManager* getInstance();

    Texture2D* getTextureById(const std::string& _id) const;

    /*
     * Load texture and return did success
     * If failed -1
     * If success 0
     * If already loaded 1
     */
    int loadTexture(std::string _id);
private:
    std::unordered_map<std::string, Texture2D*> textures;

    std::string gfxPath = "";

    static TextureManager* manager;

    static std::once_flag flag;
};
