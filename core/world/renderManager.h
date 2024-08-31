#pragma once

#include <iostream>
#include <vector>
#include "flecs.h"
#include "renderObject.h"

class cRenderManager
{
public:
    cRenderManager(flecs::world* _world);
    ~cRenderManager();

    cRenderManager(const cRenderManager&) = delete;
    cRenderManager& operator=(const cRenderManager&) = delete;

    static cRenderManager* getInstance();

    void render(flecs::entity_view _entity) const;

    void cameraMove(flecs::entity _entity, cCamera* _camera) const;

private:
    void renderColorRectangle(flecs::entity_view _entity) const;

    void renderTexture(flecs::entity_view _entity) const;

    void renderText(flecs::entity_view _entity) const;

    void pauser() const;

    static cRenderManager* instance_;

    static std::once_flag flag_;

    static flecs::world* world_; 
};