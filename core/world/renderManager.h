#pragma once

#include <iostream>
#include <vector>
#include "flecs.h"

class cRenderManager
{
public:
    cRenderManager(flecs::world* _world);
    ~cRenderManager();

    cRenderManager(const cRenderManager&) = delete;
    cRenderManager& operator=(const cRenderManager&) = delete;

    static cRenderManager* getInstance();

    void render(flecs::entity_view _entity) const;

private:
    void renderColorRectangle(flecs::entity_view _entity) const;

    void renderTexture(flecs::entity_view _entity) const;

    void renderText(flecs::entity_view _entity) const;

    static cRenderManager* instance_;

    static std::once_flag flag_;

    static flecs::world* world_; 
};